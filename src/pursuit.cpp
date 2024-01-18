#include "globals.h"

int findClosest (Position pose, std::vector<Position> path) {
    int closestPoint;
    double closestDist = INT_MAX;
    double dist;

    // loop through all path points
    for (int i = 0; i < path.size(); i++) {
        dist = pose.distance(path.at(i));
        if (dist < closestDist) { // new closest point
            closestDist = dist;
            closestPoint = i;
        }
    }

    return closestPoint;
}

double circleIntersect (Position p1, Position p2, Position pose, double lookaheadDist) {
    Position d = p2 - p1;
    Position f = p1 - pose;
    double a = d * d;
    double b = 2 * (f * d);
    double c = (f * f) - lookaheadDist * lookaheadDist;
    double discriminant = b * b - 4 * a * c;

    if (discriminant >= 0) {
        discriminant = sqrt(discriminant);
        double t1 = (-b - discriminant) / (2 * a);
        double t2 = (-b + discriminant) / (2 * a);

        if (t2 >= 0 && t2 <= 1) return t2;
        else if (t1 >= 0 && t1 <= 1) return t1;
    }

    return -1;
}

Position lookaheadPoint (Position lastLookahead, Position pose, std::vector<Position> path, double lookaheadDist) {
    for (int i = path.size() - 1; i > lastLookahead.heading; i--) {
        Position lastPathPosition = path.at(i - 1);
        Position currentPathPosition = path.at(i);

        double t = circleIntersect(lastPathPosition, currentPathPosition, pose, lookaheadDist);

        if (t != -1) {
            Position lookahead = lastPathPosition.lerp(currentPathPosition, t);
            lookahead.heading = i;
            return lookahead;
        }
    }

    return lastLookahead;
}

double findLookaheadCurvature (Position pose, double heading, Position lookahead) {
    double side = sign(sin(heading) * (lookahead.x - pose.x) - cos(heading) * (lookahead.y - pose.y));
    double a = -tan(heading);
    double c = tan(heading) * pose.x - pose.y;
    double x = fabs(a * lookahead.x + lookahead.y + c) / sqrt((a * a) + 1);
    double d = hypot(lookahead.x - pose.x, lookahead.y - pose.y);

    return side * ((2 * x) / (d * d));
}

void Drive::follow (vector<Position> pathPoints, int timeout, double lookahead, bool async, bool forwards, double maxSpeed) {
    if (!mutex.take(10)) return;
    if (async) {
        pros::Task task([&]() { follow(pathPoints, timeout, lookahead, false, forwards, maxSpeed); });
        mutex.give();
        pros::delay(10);
        return;
    }

    Position pose = this->getPosition(true);
    Position lastPosition = pose;
    Position lookaheadPosition(0, 0, 0);
    Position lastLookahead = pathPoints.at(0);
    lastLookahead.heading = 0;
    double curvature;
    double targetVel;
    double prevLeftVel = 0;
    double prevRightVel = 0;
    int closestPoint;
    double leftInput = 0;
    double rightInput = 0;
    int compState = pros::competition::get_status();
    distTravelled = 0;

    // loop until the robot is within the end tolerance
    for (int i = 0; i < timeout / 10 && pros::competition::get_status() == compState; i++) {
        // get the current position of the robot
        pose = this->getPosition(true);
        if (!forwards) pose.heading -= PI;

        // update completion vars
        distTravelled += pose.distance(lastPosition);
        lastPosition = pose;

        // find the closest point on the path to the robot
        closestPoint = findClosest(pose, pathPoints);
        // if the robot is at the end of the path, then stop
        if (pathPoints.at(closestPoint).heading == 0) break;

        // find the lookahead point
        lookaheadPosition = lookaheadPoint(lastLookahead, pose, pathPoints, lookahead);
        lastLookahead = lookaheadPosition; // update last lookahead position

        // get the curvature of the arc between the robot and the lookahead point
        double curvatureHeading = PI / 2 - pose.heading;
        curvature = findLookaheadCurvature(pose, curvatureHeading, lookaheadPosition);

        // get the target velocity of the robot
        targetVel = pathPoints.at(closestPoint).heading;

        // calculate target left and right velocities
        double targetLeftVel = targetVel * (2 + curvature * trackWidth) / 2;
        double targetRightVel = targetVel * (2 - curvature * trackWidth) / 2;

        // ratio the speeds to respect the max speed
        double ratio = std::max(std::fabs(targetLeftVel), std::fabs(targetRightVel)) / maxSpeed;
        if (ratio > 1) {
            targetLeftVel /= ratio;
            targetRightVel /= ratio;
        }

        // update previous velocities
        prevLeftVel = targetLeftVel;
        prevRightVel = targetRightVel;

        // move the drivetrain
        if (forwards) {
            this->driveWithVoltage(targetLeftVel, targetRightVel);
        } 
        else {
            this->driveWithVoltage(-targetLeftVel, -targetRightVel);
        }

        pros::delay(10);
    }

    // stop the robot
    this->driveWithVoltage(0, 0);
    distTravelled = -1;
    mutex.give();
}
