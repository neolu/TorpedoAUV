package Autonomy.Localization;

import org.ejml.simple.SimpleMatrix;
import org.ros.message.Time;
import org.ros.rosjava_geometry.Quaternion;
import org.ros.rosjava_geometry.Transform;
import org.ros.rosjava_geometry.Vector3;

import java.util.ArrayList;

import Autonomy.MyQuaternion;
import geometry_msgs.Twist;


/**
 * Created by meskupie on 07/03/18.
 */

public class Localization {

    // Constants
    final private int SIZE_STATES = 12;
    final private int SIZE_INPUTS = 6;

    // Initialization
    private boolean spread_particles = true;
    private boolean pose_locked = false;

    // Pose
    private Transform pose = new Transform(new Vector3(0, 0, 0), new Quaternion(0, 0, 0, 1));
    private double pose_fitness = 0;
    private Twist pose_twist;

    // Sensor transforms
    private boolean ready_initial_pose = false;
    private int imu_data_count = 0;
    private double imu_initial_yaw;
    private Transform transform_imu = new Transform(new Vector3(0, 0, 0), new Quaternion(0, 1, 0, 0));
    private double camera_transform_x = 0.240;
    private double camera_transform_z = 0.0043;
    private Transform camera_transform_front = new Transform(new Vector3( camera_transform_x,0,camera_transform_z),new Quaternion(0,0,0,1));
    private Transform camera_transform_rear  = new Transform(new Vector3(-camera_transform_x,0,camera_transform_z),new Quaternion(0,1,0,0));

    // State machine
    private boolean ready_localization;
    private boolean ready_A = false;
    private boolean ready_B = false;
    private boolean ready_map = false;

    private boolean ready_thrust = false;
    private boolean ready_imu = false;
    private boolean ready_depth = false;
    private boolean ready_camera_front = false;
    private boolean ready_camera_rear = false;

    // Data
    private SimpleMatrix data_thrust;
    private Quaternion data_imu;
    private double data_depth;

    // Particle Filter
    ParticleCloud particles;
    private SimpleMatrix param_A_mat = new SimpleMatrix(SIZE_STATES, SIZE_STATES);
    private SimpleMatrix param_B_mat = new SimpleMatrix(SIZE_STATES, SIZE_INPUTS);

    // Data fitting
    private MapTarget[] param_map;
    private CameraTarget[] data_camera_targets_front;
    private CameraTarget[] data_camera_targets_rear;
    private CameraTarget[] data_camera_targets_all;
    Vector3[] fitting_points_target;
    Vector3[] fitting_points_map;



    public Localization() {}

    public Boolean attemptUpdate(Time call_time) {
        // Check what sensor data is ready
        boolean ready_sensors = (ready_imu&&true);
        // Check if we should run
        if (ready_localization && ready_sensors) {
            pose = transform_imu.multiply(new Transform(new Vector3(0, 0, 0), data_imu));
            ready_imu = false;
            // TODO: add other resets
            return true;
        }
        return false;
    }

    public Boolean attmptUpdateTwo(Time call_time){

        // build complete camera set

        // match corespondences



        return true;
    }

    public void matchCorrespondences(Transform pose){
        ArrayList<Vector3> points_target_list = new ArrayList<>();
        ArrayList<Vector3> points_map_list = new ArrayList<>();
        for(int i = 0; i < data_camera_targets_all.length; i++){
            double best_score = 0.5; // Score threshold that has to be beet
            // Best correspondence
            boolean found_option = false;
            Vector3 best_map = new Vector3(0,0,0);
            Vector3 best_target = new Vector3(0,0,0);
            // Calculate a geometry related to the camera target
            Transform target_inertial_trans = pose.multiply(data_camera_targets_all[i].getTargetTransform());
            Quaternion target_inertial_quat = target_inertial_trans.getRotationAndScale();
            Vector3 target_inertial_vect = target_inertial_trans.getTranslation();
            Transform unit_vector_trans = new Transform(new Vector3(1,0,0),new Quaternion(0,0,0,1));
            // Calculate a unit direction vector of the inertial camera laser
            Vector3 target_unit_vect = new Transform(new Vector3(0,0,0),target_inertial_quat).multiply(unit_vector_trans).getTranslation();
            for(int j = 0; j < param_map.length; j++){
                if(data_camera_targets_all[i].getTargetId() == param_map[j].getTargetId()){ // colours are the same
                    Vector3 map_test_point = param_map[j].getPoint().subtract(target_inertial_vect);
                    double scale = map_test_point.dotProduct(target_unit_vect)/target_unit_vect.dotProduct(target_unit_vect);
                    if(scale > 0){
                        Vector3 camera_test_point = target_unit_vect.scale(scale);
                        double score = camera_test_point.subtract(map_test_point).getMagnitudeSquared();
                        if(score < best_score){
                            best_score = score;
                            found_option = true;
                            best_map = map_test_point;
                            best_target = camera_test_point;
                        }
                    }
                }
            }
            if(found_option){
                points_map_list.add(best_map);
                points_target_list.add(best_target);
            }
        }
        fitting_points_map = points_map_list.toArray(new Vector3[0]);
        fitting_points_target = points_target_list.toArray(new Vector3[0]);
    }


    public boolean setInitialOrientation() {
        if(ready_imu) {
            double ewma_rate = 0.05;
            double imu_yaw = new MyQuaternion(data_imu).getYaw();
            if (imu_data_count == 0) {
                imu_initial_yaw = imu_yaw;
                ready_initial_pose = false;
            } else {
                imu_initial_yaw = ewma_rate * imu_yaw + (1 - ewma_rate) * imu_initial_yaw;
                if (imu_data_count > 20) {
                    ready_initial_pose = true;
                } else {
                    ready_initial_pose = false;
                }
            }
            transform_imu = new Transform(new Vector3(0, 0, 0), MyQuaternion.createFromEuler(180, 0, imu_initial_yaw).invert());
            imu_data_count++;
            ready_imu = false;
            return true;
        }
        return false;
    }

    public boolean resetInitialOrientation() {
        imu_initial_yaw = 0;
        imu_data_count = 0;
        ready_initial_pose = false;
        return !ready_initial_pose;
    }

    private boolean myIsReady(){return(ready_A && ready_B && ready_map);}

    // Mutator
    public boolean setImuData(Quaternion _data_imu) {
        data_imu = _data_imu;
        ready_imu = true;
        return ready_imu;
    }

    public boolean setDepthData(double _data_depth) {
        data_depth = _data_depth;
        ready_depth = true;
        return ready_depth;
    }

    public boolean setThrusterData(SimpleMatrix _data_thrust) {
        data_thrust = _data_thrust;
        ready_thrust = true;
        return ready_thrust;
    }

    public boolean setCameraTargetsFront(CameraTarget[] _data_camera_targets) {
        data_camera_targets_front = _data_camera_targets;
        for(int i = 0; i < data_camera_targets_front.length; i++){
            data_camera_targets_front[i].setFrame(camera_transform_front);}
        ready_camera_front = true;
        return ready_camera_front;
    }

    public boolean setCameraTargetsRear(CameraTarget[] _data_camera_targets) {
        data_camera_targets_rear = _data_camera_targets;
        for(int i = 0; i < data_camera_targets_rear.length; i++){
            data_camera_targets_rear[i].setFrame(camera_transform_rear);}
        ready_camera_rear = true;
        return ready_camera_rear;
    }

    public boolean setMapData(MapTarget[] _data_map_targets) {
        param_map = _data_map_targets;
        ready_map = true;
        ready_localization = myIsReady();
        return ready_map;
    }

    public boolean setAData(SimpleMatrix A) {
        param_A_mat = A;
        ready_A = true;
        ready_localization = myIsReady();
        return ready_A;
    }

    public boolean setBData(SimpleMatrix B) {
        param_B_mat = B;
        ready_B = true;
        ready_localization = myIsReady();
        return ready_B;
    }

    // Accessors
    public boolean isReady(){return ready_localization;}
    public boolean isLocked(){return ready_initial_pose;}
    public Transform getPose() {return pose;}
    public double getFitness() {return pose_fitness;}
    public Twist getTwist() {return pose_twist;}
    public int[] getAShape() {return new int[]{SIZE_INPUTS, SIZE_INPUTS};}
    public int[] getBShape() {return new int[]{SIZE_STATES, SIZE_INPUTS};}
}