#pragma once

#include "globals.h"

class Odom {
    private:
        double forw_tracker_distance;
        double side_tracker_distance;
        double forw_tracker_pos;
        double side_tracker_pos;
    public:
        Position pos;
        Odom(Position start, double forwDist, double sideDist, double forwPos, double sidePos);
        void update(double forwPos, double sidePos, double new_heading);
};