#include "globals.h"

PID::PID(double error, double kp, double ki, double kd, double starti, double settle_error, double settle_time, double timeout) :
    error(error),
    kp(kp),
    ki(ki),
    kd(kd),
    starti(starti),
    settle_error(settle_error),
    settle_time(settle_time),
    timeout(timeout)
{}

PID::PID(double error, double kp, double ki, double kd, double starti) :
    error(error),
    kp(kp),
    ki(ki),
    kd(kd),
    starti(starti),
    settle_error(settle_error),
    settle_time(settle_time),
    timeout(timeout)
{}

void PID::start() {
    start_time = pros::millis();
}

double PID::compute(double error) {
    if (abs(error) < starti) 
        accum_error += error;

    if ( (error > 0 && prev_error < 0) || (error < 0 && prev_error > 0) )
        accum_error = 0;

    double output = (kp * error) + (ki * accum_error) + (kd * (error - prev_error) ); 

    if (abs(error) <= settle_error) {
        if (settled_start_time == -1)
            settled_start_time = pros::millis();
        else
            time_settled = pros::millis() - settled_start_time;
    }
    else {
        settled_start_time = -1;
        time_settled = 0;
    }

    time_running = pros::millis() - start_time;

    return output;
}

bool PID::is_settled() {
    return (time_running >= timeout && timeout > 0) || (time_settled >= settle_time);
}
