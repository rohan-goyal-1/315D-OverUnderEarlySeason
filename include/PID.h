#pragma once

#include "globals.h"

class PID {
    private:
        double error;
        double kp;
        double ki;
        double kd;
        double starti;
        double settle_error;
        double settle_time;
        double timeout;

        double start_time;
        double settled_start_time = -1;
        double accum_error = 0;
        double prev_error = 0;
        double time_settled = 0;
        double time_running = 0;

    public:
        PID(double kp, double ki, double kd, double starti, double settle_error, double settle_time, double timeout);
        PID(double kp, double ki, double kd, double starti);

        double compute(double error);
        void start(void);
        bool is_settled(void);
};
