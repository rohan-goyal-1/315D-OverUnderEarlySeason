#include "globals.h"

AutonSelector selector;

void initialize() {
	Robot::RobotMgr::currState = PROGRAM_STATE::INITIALIZE;
	pros::lcd::initialize(); 
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
	selector.run();
}

void opcontrol() {
	Robot::RobotMgr::currState = PROGRAM_STATE::OPCONTROL;
	Robot::RobotMgr::pneumaticsInit();
	chassis.motorInitCoast();
}