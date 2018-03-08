package Util;

import android.util.Log;

/**
 * Created by isaiah on 01/03/18.
 */

public class MotorOutputs {

    public enum Motor {
        FL, FR, FV, BL, BR, BV
    }

    int scalingFactor = 2^16 - 1;

    /** Motor outputs go from 0 to 5
        motorOutputs[0] = frontLeft;
        motorOutputs[0] = frontRight;
        motorOutputs[0] = frontVert;
        motorOutputs[0] = backLeft;
        motorOutputs[0] = backRight;
        motorOutputs[0] = backVert;


        0-1 scale for doubles, 0 - 2^16-1 for nominal
    */

    public double[] motorOutputs;

    public MotorOutputs() {
        this.motorOutputs = new double[6];
    }

    public MotorOutputs(double[] m) {
        if(m.length == 6) {
            this.motorOutputs = m;
        } else {
            this.motorOutputs = new double[6];
            Log.d("ERROR", "the motor Outputs specified was not the right size (6)");
        }
    }

    public int get(MotorOutputs.Motor motor) {
        return (int)(getNormalized(motor) * scalingFactor);
    }

    public double getNormalized(MotorOutputs.Motor motor) {
        return constrainInput(this.motorOutputs[motor.ordinal()]);
    }

    public double constrainInput(double input) {
        if(input < 0) {
            return 0;
        } else if(input > 1) {
            return 1;
        } else {
            return input;
        }
    }

}