#pragma once

using namespace std;

#include <iostream>
#include <cassert>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <cerrno>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <unistd.h>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <numeric>
#include <memory>

#define pct_to_volt(a) ( (a / 127) * MAX_VOLT)

#define PI 3.14159265358979323846
#define abs fabs
#define PROS_USE_LITERALS
#define jlx E_CONTROLLER_ANALOG_LEFT_X
#define jly E_CONTROLLER_ANALOG_LEFT_Y
#define jrx E_CONTROLLER_ANALOG_RIGHT_X
#define jry E_CONTROLLER_ANALOG_RIGHT_Y
#define buttonA E_CONTROLLER_DIGITAL_A
#define buttonY E_CONTROLLER_DIGITAL_Y
#define buttonX E_CONTROLLER_DIGITAL_X
#define buttonB E_CONTROLLER_DIGITAL_B
#define buttonLeft E_CONTROLLER_DIGITAL_LEFT
#define buttonRight E_CONTROLLER_DIGITAL_RIGHT
#define buttonUp E_CONTROLLER_DIGITAL_UP
#define buttonDown E_CONTROLLER_DIGITAL_DOWN
#define buttonR1 E_CONTROLLER_DIGITAL_R1
#define buttonR2 E_CONTROLLER_DIGITAL_R2
#define buttonL1 E_CONTROLLER_DIGITAL_L1
#define buttonL2 E_CONTROLLER_DIGITAL_L2
#define MAX_VOLT 12000
#define wait pros::delay

double reduce_0_to_360(double angle);
double reduce_neq_180_to_180(double angle);
double reduce_neg_90_to_90(double angle);
double to_rad(double angle_deg);
double to_deg(double angle_rad);
double clamp(double input, double min, double max);
double to_volt(double pct);
double deadband(double input, double width);
int sign(double a);
double reduceDiff (double desired, double curr);

#include "api.h"
#include "position.h"
#include "autons.h"
#include "robotMgr.h"
#include "main.h"
#include "odom.h"
#include "drive.h"
#include "PID.h"
#include "robots.h"