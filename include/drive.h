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
        pros::Task odomTask;
        double forwDist;
        double sideDist;
        bool odom_started = false;
        pros::Rotation* sideEncoder;

    public:
        Drive(DriveType drive_type, vector<pros::IMU>& gyro, pros::MotorGroup* DriveR, pros::MotorGroup* DriveL, double gearRatio, double wheelDiam, double sideDiam, double forwDist, double sideDist, pros::Rotation* sideEncoder);

        // Init stuff
        void chassisInit(void);
        void motorInitBrake(void);
        void motorInitCoast(void);
        void gyroInit(void);
        void setPosition(Position p);

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
        void turn_to_angle(double angle);
        void turn_to_angle(double angle, double maxVolt);
        void turn_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout);
        void turn_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti);

        // Left swing to angle
        void left_swing_to_angle(double angle);
        void left_swing_to_angle(double angle, double maxVolt);
        void left_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout);
        void left_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti);

        // Right swing to angle
        void right_swing_to_angle(double angle);
        void right_swing_to_angle(double angle, double maxVolt);
        void right_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout);
        void right_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti);

        // Drive distance
        void drive_dist(double dist);
        void drive_dist(double dist, double heading);
        void drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt);
        void drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt, double drive_settle_error, double drive_settle_time, double drive_timeout);
        void drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt, double drive_settle_error, double drive_settle_time, double drive_timeout, double drive_kp, double drive_ki, double drive_kd, double drive_starti, double heading_kp, double heading_ki, double heading_kd, double heading_starti);

        // Drive options
        void tankControl(void);

        // Odom functions
        double getSideEncoder(void);
        double getForwPos(void);
        double getSidePos(void);
        void setHeading(double heading);
        void setPosition(Position p);
        void startOdom(void);
        void updateOdom(void);
};
