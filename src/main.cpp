#include "globals.h"

AutonSelector selector;

void initialize() {
	Robot::RobotMgr::currState = PROGRAM_STATE::INITIALIZE;
	Robot::RobotMgr::robotInit();
	selector.add(farSideMidRush, "Four-ball auton");
	selector.add(closeSideAWP, "AWP safe");
	selector.add(closeSideElims, "Elims ball disturb");
	// selector.add(farSide6Ball, "Elims: Far-side 6-ball");
	// selector.add(progSkills, "Prog. skills");
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
