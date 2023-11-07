#include "globals.h"

Odom::Odom(Position start, double forwDist, double sideDist, double forwPos, double sidePos) :
    pos(Position(start.x, start.y, start.heading)),
    forw_tracker_distance(forwDist),
    side_tracker_distance(sideDist),
    forw_tracker_pos(forwPos),
    side_tracker_pos(sidePos)
{}

void Odom::update(double forwPos, double sidePos, double new_heading) {
    double forward_delta = forwPos - forw_tracker_pos;
    double side_delta = sidePos - side_tracker_pos;

    forw_tracker_pos = forwPos;
    side_tracker_pos = sidePos;

    double new_heading_rad = to_rad(new_heading);
    double prev_heading_rad = to_rad(pos.heading);
    double heading_delta_rad = new_heading_rad - prev_heading_rad;
    pos.heading = new_heading;

    double local_x_pos;
    double local_y_pos;
    if (heading_delta_rad == 0) {
        local_x_pos = side_delta;
        local_y_pos = forward_delta;
    }
    else {
        local_x_pos = 2 * sin(heading_delta_rad / 2) * ((side_delta / heading_delta_rad) + side_tracker_distance); 
        local_y_pos = 2 * sin(heading_delta_rad / 2) * ((forward_delta / heading_delta_rad) + forw_tracker_distance);
    }
    // double avgHeading = prev_heading_rad + heading_delta_rad / 2;
    // pos.x += local_y_pos * sin(avgHeading);
    // pos.y += local_y_pos * cos(avgHeading);
    // pos.x += local_x_pos * -cos(avgHeading);
    // pos.y += local_x_pos * sin(avgHeading);
    double local_polar_angle;
    double local_polar_length;
    if (local_x_pos == 0 && local_y_pos == 0){
        local_polar_angle = 0;
        local_polar_length = 0;
    } 
    else {
        local_polar_angle = atan2(local_y_pos, local_x_pos); 
        local_polar_length = sqrt(pow(local_x_pos, 2) + pow(local_y_pos, 2)); 
    }

    double global_polar_angle = local_polar_angle - prev_heading_rad - (heading_delta_rad / 2);

    double x_delta = local_polar_length * cos(global_polar_angle); 
    double y_delta = local_polar_length * sin(global_polar_angle);

    pos.x += x_delta;
    pos.y += y_delta;
}