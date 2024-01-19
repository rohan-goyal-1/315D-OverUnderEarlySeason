#pragma once

#include "globals.h"

enum DriveType {
    ZERO_ENCODER,
    ONE_ENCODER
};
class Drive {
    private:
        // Physical Constants
        double gearRatio;
        double wheelCircum;
        double sideCircum;
        double trackWidth;

        // PID Constants
        double drive_kp;
        double drive_ki;
        double drive_kd;
        double drive_starti;
        double drive_timeout;
        double drive_maxVolt;
        double drive_settle_time;
        double drive_settle_error;

        double turn_kp;
        double turn_ki;
        double turn_kd;
        double turn_starti;
        double turn_timeout;
        double turn_maxVolt;
        double turn_settle_time;
        double turn_settle_error;

        double swing_kp;
        double swing_ki;
        double swing_kd;
        double swing_starti;
        double swing_timeout;
        double swing_maxVolt;
        double swing_settle_time;
        double swing_settle_error;

        double heading_kp;
        double heading_ki;
        double heading_kd;
        double heading_starti;
        double heading_maxVolt;

        pros::MotorGroup* DriveR;
        pros::MotorGroup* DriveL;
        vector<pros::IMU>& gyro;
        DriveType drive_type;

        Odom odom;
        pros::Task* odomTask;
        double forwDist;
        double sideDist;
        pros::Rotation* sideEncoder;
        pros::Mutex mutex;
        double distTravelled = -1;

    public:
        Drive(DriveType drive_type, vector<pros::IMU>& gyro, pros::MotorGroup* DriveR, pros::MotorGroup* DriveL, double gearRatio, double wheelDiam, double sideDiam, double forwDist, double sideDist, pros::Rotation* sideEncoder, double trackWidth);

        // Init stuff
        void chassisInit(void);
        void motorInitBrake(void);
        void motorInitCoast(void);
        void gyroInit(void);

        // Misc
        void driveWithVoltage(double left, double right);
        double getHeading(void);
        double getLeftPosition(void);
        double getRightPosition(void);

        // PID Setters
        void setDriveConstants(double kp, double ki, double kd);
        void setDriveConstants(double kp, double ki, double kd, double max_volt, double starti);
        void setTurnConstants(double kp, double ki, double kd);
        void setTurnConstants(double kp, double ki, double kd, double max_volt, double starti);
        void setSwingConstants(double kp, double ki, double kd);
        void setSwingConstants(double kp, double ki, double kd, double max_volt, double starti);
        void setHeadingConstants(double kp, double ki, double kd);
        void setHeadingConstants(double kp, double ki, double kd, double max_volt, double starti);

        void setDriveExitConditions(double settle_error, double settle_time, double timeout);
        void setTurnExitConditions(double settle_error, double settle_time, double timeout);
        void setSwingExitConditions(double settle_error, double settle_time, double timeout);

        // Turn to angle
        void turn_to_angle(double angle, bool async = false);
        void turn_to_angle(double angle, double maxVolt, bool async = false);
        void turn_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, bool async = false);
        void turn_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti, bool async = false);

        // Left swing to angle
        void left_swing_to_angle(double angle, bool async = false);
        void left_swing_to_angle(double angle, double maxVolt, bool async = false);
        void left_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, bool async = false);
        void left_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti, bool async = false);

        // Right swing to angle
        void right_swing_to_angle(double angle, bool async = false);
        void right_swing_to_angle(double angle, double maxVolt, bool async = false);
        void right_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, bool async = false);
        void right_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti, bool async = false);

        // Drive distance
        void drive_dist(double dist, bool async = false);
        void drive_dist(double dist, double heading, bool async = false);
        void drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt, bool async = false);
        void drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt, double drive_settle_error, double drive_settle_time, double drive_timeout, bool async = false);
        void drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt, double drive_settle_error, double drive_settle_time, double drive_timeout, double drive_kp, double drive_ki, double drive_kd, double drive_starti, double heading_kp, double heading_ki, double heading_kd, double heading_starti, bool async = false);

        // Extra efficiency
        void turn_and_drive(double heading, double dist, double turnVolt, double tolerance = 2);
        void left_swing_and_drive(double heading, double dist, double turnVolt, double tolerance = 2);
        void right_swing_and_drive(double heading, double dist, double turnVolt, double tolerance = 2);

        // Odom methods
        void move_to_point(Position point, bool forwards = true);
        void move_to_point(Position point, double maxVolt, bool forwards = true, double lead = 0.6, double chasePower = 2);

        // Drive options
        void tankControl(void);

        // Odom helper methods
        double getForwPos(void);
        double getSidePos(void);
        void setHeading(double heading);
        void setPosition(Position p);
        Position getPosition(bool radians = false);
        void startOdom(void);
        void pauseOdom(void);
        void resumeOdom(void);

        // Pursuit methods
        double getCurvature(Position pose, Position other);
        void follow(vector<Position> pathPoints, int timeout, double lookahead, bool async = true, bool forwards = true, double maxSpeed = 12000);

        // Async helpers
        void waitUntilSettled();
        void waitUntilDist(double dist);
};
