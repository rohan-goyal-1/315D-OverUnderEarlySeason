#include "globals.h"

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
    return abs(input) < width ? 0 : input;
}

int sign (double a) {
    return a < 0 ? -1 : 1;
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