#include "globals.h"


void on_center_button() {}

void initialize() {
	Robot::RobotMgr::currState = PROGRAM_STATE::INITIALIZE;
	pros::lcd::initialize(); pros::lcd::register_btn1_cb(on_center_button);
	Robot::RobotMgr::robotInit();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	Robot::RobotMgr::currState = PROGRAM_STATE::AUTONOMOUS;
	// progSkills();
	farSide();
	// closeSide();
}

void opcontrol() {
	Robot::RobotMgr::currState = PROGRAM_STATE::OPCONTROL;
	// Robot::RobotMgr::pneumaticsInit();
	chassis.motorInitCoast();
    while (true) {
		// chassis.tankControl();
		pros::lcd::set_text(1, "hello");
		pros::delay(20);
	}
}
