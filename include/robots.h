#pragma once

#include "globals.h"

// Motors
#define LF -20 //done
#define LM 18 //done
#define LB -15 //done
#define RF 16 //done
#define RM -14 //done
#define RB 12 //done
#define INTAKE_MTR 11
#define CATA_MTR 2

// IMU ports
#define Imu 19

#define ROT 17

// Pneumatics
#define FLAP_P 'A'
#define ENDGAME_P 'G'
#define BLOCKER_P 'F'

// ADI sensors
#define BUMPER_PORT 'H'

extern pros::Controller master;
extern pros::Motor intake, cata;
extern pros::MotorGroup DriveR, DriveL;
extern vector<pros::IMU> gyro;
extern Drive chassis;
extern pros::adi::DigitalOut flapjacks, endgame, blocker;
extern pros::adi::DigitalIn bumper;