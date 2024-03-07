#pragma once

#include "globals.h"

// Motors
#define LF 1 //done
#define LM1 12 //done
#define LM2 2 //done
#define LB -11 //done
#define RF -10 //done
#define RM1 -19 //done
#define RM2 -7 //done
#define RB 20 //done
#define INTAKE_MTR 17
#define CATA_MTR 2

// sensor ports
#define Imu 13
#define DIST 3

// Pneumatics
#define FLAP_P 'G'
#define ENDGAME_P 'B'
#define BLOCKER_P 'A'
#define INTAKE_P 'H'
#define DESCORE_P 'F'

// ADI sensors

extern pros::Controller master;
extern pros::Motor intake, cata;
extern pros::MotorGroup DriveR, DriveL;
extern vector<pros::IMU> gyro;
extern pros::Distance distance_sensor;
extern Drive chassis;
extern pros::adi::DigitalOut flapjacks, endgame, blocker, intake_pull, descore;
