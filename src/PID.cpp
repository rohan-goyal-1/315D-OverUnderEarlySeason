#include "globals.h"

PID::PID(double kp, double ki, double kd, double starti, double settle_error, double settle_time, double timeout) :
    kp(kp),
    ki(ki),
    kd(kd),
    starti(starti),
    settle_error(settle_error),
    settle_time(settle_time),
    timeout(timeout)
{}

PID::PID(double kp, double ki, double kd, double starti) :
    kp(kp),
    ki(ki),
    kd(kd),
    starti(starti)
{}

void PID::start() {
    start_time = pros::millis();
}

double PID::compute(double error) {
    // Increment accumulated error for I term if error less than threshold: done to prevent the I from growing large
    if (abs(error) < starti) 
        accum_error += error;

    // If the robot crossed the desired value, reset accumulated error to 0
    if (sign(error) != sign(prev_error))
        accum_error = 0;

    // Calculate the output based on current error, accumulated error, and previous error
    double output = (kp * error) + (ki * accum_error) + (kd * (error - prev_error) ); 

    // If current error less than settle error, increment settle time; otherwise, reset the settle time.
    if (abs(error) <= settle_error) {
        time_settled += 5;
    }
    else {
        time_settled = 0;
    }
    
    prev_error = error;

    // Increment running time
    time_running += 5;

    return output;
}

// Method to check if exit conditions are met: timeout and settle time
bool PID::is_settled() {
    return (time_running >= timeout && timeout > 0) || (time_settled >= settle_time);
}
