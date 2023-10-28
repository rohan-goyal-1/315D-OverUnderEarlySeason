#pragma once

#include "globals.h"

// Motors
#define LF -7 //done
#define LM 9 //done
#define LB -4
#define RF 13 //done
#define RM -12
#define RB 8 //done
#define INTAKE_MTR 11
#define CATA_MTR 16

// IMU ports
#define imu1 18
#define imu2 15

// Pneumatics
#define FLAP_P 'B'
#define ENDGAME_P 'C'
#define BLOCKER_P 'A'

// ADI sensors
#define BUMPER_PORT 'D'

extern pros::Controller master;
extern pros::Motor intake, cata;
extern pros::MotorGroup DriveR, DriveL;
extern vector<pros::IMU> gyro;
extern Drive chassis;
extern pros::adi::DigitalOut flapjacks, endgame, blocker;
extern pros::adi::DigitalIn bumper;