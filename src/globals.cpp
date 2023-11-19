#include "globals.h"

double reduce_0_to_360(double angle) {
    while (angle < 0 || angle >= 360)  {
        if (angle < 0) angle += 360;
        if (angle >= 360) angle -= 360;
    }
    return angle;
}

double reduce_neg_180_to_180(double angle) {
    while (angle < -180 || angle >= 180) {
        if (angle < -180) angle += 360;
        if (angle >= 180) angle -= 360;
    }
    return angle;
}

double relative_neg_180_to_180(double angle) {
    if (angle < 0) 
        return -(angle + 180);
    return angle;
}

double reduce_neg_90_to_90(double angle) {
    while (angle < -90 || angle >= 90) {
        if (angle < -90) angle += 180;
        if (angle >= 90) angle -= 180;
    }
    return angle;
}

double to_rad(double angle_deg) {
    return angle_deg / (180.0/PI);
}

double to_deg(double angle_rad) {
    return angle_rad * (180.0/PI);
}

double clamp(double input, double min, double max) {
    if (input > max) return max;
    if (input < min) return min;
    return input;
}

double to_volt(double pct) {
    return pct / 100.0 * 12000.0;
}

double deadband(double input, double width) {
    if (abs(input) < width)
        return 0;
    return input;
}

int sign (double a) {
    if (a < 0) return -1;
    return 1;
}

double reduceDiff (double desired, double curr) {
    double delta = desired - curr;
    if (delta > 180.0) {
        delta -= 360.0;
    }
    else if (delta < -180.0) {
        delta += 360.0;
    }
    return delta;
}