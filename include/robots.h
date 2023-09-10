#pragma once

#include "globals.h"

// Motors
#define LF -19
#define LM 20
#define LB -21
#define RF -8
#define RM 9
#define RB 10
#define INTAKE_MTR 1
#define CATA_MTR 6

// IMU ports
#define imu1 18
#define imu2 3

// Pneumatics
#define FLAP_P 'B'
#define ENDGAME_P 'C'
#define ARM_P 'A'

extern pros::Controller master;
extern pros::Motor intake, cata;
extern pros::MotorGroup DriveR, DriveL;
extern vector<pros::IMU> gyro;
extern Drive chassis;
extern pros::adi::DigitalOut flapjacks, endgame, arm;