#include "globals.h"

AutonSelector selector;

void initialize() {
	Robot::RobotMgr::currState = PROGRAM_STATE::INITIALIZE;
    intake_pull.set_value(true);
	Robot::RobotMgr::robotInit();
	selector.add(closeSideAWP, "AWP safe");
	selector.add(farSideMidRush, "Four-ball auton");
	selector.add(closeSideElims, "Elims ball disturb");
	// selector.add(farSide6Ball, "Elims: Far-side 6-ball");
	// selector.add(progSkills, "Prog. skills");
	selector.start();
}

void disabled() {
    // intake_pull.set_value(true);
}

void competition_initialize() {
    intake_pull.set_value(true);
}

void autonomous() {
	Robot::RobotMgr::currState = PROGRAM_STATE::AUTONOMOUS;
	selector.run();
}

void opcontrol() {
	Robot::RobotMgr::currState = PROGRAM_STATE::OPCONTROL;
	Robot::RobotMgr::pneumaticsInit();
	chassis.motorInitCoast();
    intake_pull.set_value(true);
    Robot::RobotMgr::stateMachine[INTAKE_PULL] = true;
}
