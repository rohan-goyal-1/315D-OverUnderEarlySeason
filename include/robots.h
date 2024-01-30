#pragma once

#include "globals.h"

// Motors
#define LF 11 //done
#define LM 12 //done
#define LB 16 //done
#define RF -17 //done
#define RM -19 //done
#define RB -18 //done
#define INTAKE_MTR 6
#define CATA_MTR 2

// sensor ports
#define Imu 2
#define DIST 3

// Pneumatics
#define FLAP_P 'H'
#define ENDGAME_P 'G'
#define BLOCKER_P 'F'

// ADI sensors

extern pros::Controller master;
extern pros::Motor intake, cata;
extern pros::MotorGroup DriveR, DriveL;
extern vector<pros::IMU> gyro;
extern pros::Distance distance_sensor;
extern Drive chassis;
extern pros::adi::DigitalOut flapjacks, endgame, blocker;
