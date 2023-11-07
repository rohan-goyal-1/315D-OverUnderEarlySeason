#include "globals.h"

AutonSelector selector;

void on_center_button() {}

void initialize() {
	Robot::RobotMgr::currState = PROGRAM_STATE::INITIALIZE;
	pros::lcd::initialize(); pros::lcd::register_btn1_cb(on_center_button);
	Robot::RobotMgr::robotInit();
	selector.add(closeSideAWP, "Close-side AWP with one ball disturb");
	selector.add(farSide, "Far-side 6-ball");
	selector.add(progSkills, "Prog. skills");
	selector.start();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	Robot::RobotMgr::currState = PROGRAM_STATE::AUTONOMOUS;
	// selector.run();
	farSide();
}

void opcontrol() {
	Robot::RobotMgr::currState = PROGRAM_STATE::OPCONTROL;
	Robot::RobotMgr::pneumaticsInit();
	chassis.motorInitCoast();
}