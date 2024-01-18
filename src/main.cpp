#include "globals.h"

AutonSelector selector;

void initialize() {
	Robot::RobotMgr::currState = PROGRAM_STATE::INITIALIZE;
	Robot::RobotMgr::robotInit();
	selector.add(closeSideElims, "Elims: Close-side with one ball disturb");
	selector.add(closeSideAWP, "Quals: Close-side with one ball disturb");
	selector.add(farSideMidRush, "Quals: Far-side mid-rush");
	selector.add(farSide6Ball, "Elims: Far-side 6-ball");
	selector.add(progSkills, "Prog. skills");
	selector.start();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	Robot::RobotMgr::currState = PROGRAM_STATE::AUTONOMOUS;
	// selector.run();
    chassis.drive_dist(10);
    chassis.turn_to_angle(90);
    // chassis.drive_dist(-20, 0, false);
    chassis.right_swing_to_angle(45);
    chassis.right_swing_to_angle(-45);
}

void opcontrol() {
	Robot::RobotMgr::currState = PROGRAM_STATE::OPCONTROL;
	Robot::RobotMgr::pneumaticsInit();
	chassis.motorInitCoast();
}
