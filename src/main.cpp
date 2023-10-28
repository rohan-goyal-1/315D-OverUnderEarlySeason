#include "globals.h"


void on_center_button() {}

void initialize() {
	//TODO: check if all motors are braked after some movement
	//TODO: reset gyro etc. mech (maybe to intake) look at 5150d
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
	Robot::RobotMgr::pneumaticsInit();
	chassis.motorInitCoast();
    while (true) {
		Robot::RobotMgr::robotManage();
		pros::lcd::set_text(4, "Left: " + to_string(chassis.getLeftPosition()) + "\tRight: " + to_string(chassis.getRightPosition()));
		pros::lcd::set_text(5, "Heading: " + to_string(chassis.getHeading()));
		pros::delay(20);
	}
}
