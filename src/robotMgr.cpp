#include "globals.h"

// Initialize static variables
vector<bool> Robot::RobotMgr::stateMachine(6, false);
vector<pros::adi::DigitalOut*> Robot::RobotMgr::pneumatics(6, nullptr);
pros::Task* Robot::RobotMgr::robotManager = nullptr;
PROGRAM_STATE Robot::RobotMgr::currState = PROGRAM_STATE::INITIALIZE;

namespace Robot {

void RobotMgr::robotManage () {
    intakeManage();
    cataManage();
    pneuManage();
    chassis.tankControl();
}

void RobotMgr::pneuManage () {
    if (currState == PROGRAM_STATE::OPCONTROL) {
    if (master.get_digital_new_press(pros::buttonL1)) {
        pneumatics[FLAPJACK]->set_value(!stateMachine[FLAPJACK]);
        stateMachine[FLAPJACK] = !stateMachine[FLAPJACK];
    }
    if (master.get_digital_new_press(pros::buttonL2)) {
        pneumatics[BLOCKER]->set_value(!stateMachine[BLOCKER]);
        stateMachine[BLOCKER] = !stateMachine[BLOCKER];
    }
    if (master.get_digital_new_press(pros::buttonDown)) {
        pneumatics[ENDGAME]->set_value(!stateMachine[ENDGAME]);
        stateMachine[ENDGAME] = !stateMachine[ENDGAME];
    }
    }
}

void RobotMgr::intakeManage () {
    switch (currState) {
    
    case PROGRAM_STATE::OPCONTROL:
        if (bumper.get_value()) {
            if (master.get_digital_new_press(pros::buttonR2)) {
                intake.move_voltage(stateMachine[INTAKE_REV] ? 0 : -MAX_VOLT);
                stateMachine[INTAKE_REV] = !stateMachine[INTAKE_REV];
                stateMachine[INTAKE_FORW] = false;
            }
            else if (stateMachine[INTAKE_REV] == false) {
                intake.move_voltage(0);
                stateMachine[INTAKE_FORW] = false;
                stateMachine[INTAKE_REV] = false;
            }
        }
        else {
            if (master.get_digital_new_press(pros::buttonR2)) {
                intake.move_voltage(stateMachine[INTAKE_REV] ? 0 : -MAX_VOLT);
                stateMachine[INTAKE_REV] = !stateMachine[INTAKE_REV];
                stateMachine[INTAKE_FORW] = false;
            }
            else if (master.get_digital_new_press(pros::buttonR1)) {
                intake.move_voltage(stateMachine[INTAKE_FORW] ? 0 : MAX_VOLT);
                stateMachine[INTAKE_FORW] = !stateMachine[INTAKE_FORW];
                stateMachine[INTAKE_REV] = false;
            }
        }
        break;

    case PROGRAM_STATE::INITIALIZE:
        if (intake.get_actual_velocity() > 2 && intake.get_voltage() == 0) {
            wait(500);
            chassis.pauseOdom();
            chassis.gyroInit();
            chassis.resumeOdom();
        }
        break;
    }
}

void RobotMgr::intakeBall (double timeout) {
    pros::Task* intakeTask = new pros::Task {[=] {
        double start = pros::millis();
        intake.move_voltage(MAX_VOLT);
        waitUntil(bumper.get_value() || pros::millis() - start >= timeout);
        intake.move_voltage(0);
    }};
}

void RobotMgr::outtakeBall (double timeout) {
    pros::Task* outtakeTask = new pros::Task {[=] {
        double start = pros::millis();
        intake.move_voltage(-MAX_VOLT);
        waitUntil(!bumper.get_value() || pros::millis() - start >= timeout);
        intake.move_voltage(0);
    }};
}

void RobotMgr::cataManage () {
    if (currState == PROGRAM_STATE::OPCONTROL) {
    if (master.get_digital_new_press(pros::buttonX)) {
        cata.move_voltage(stateMachine[CATA] ? 0 : MAX_VOLT);
        stateMachine[CATA] = !stateMachine[CATA];
    }
    }
}

void RobotMgr::driveInit () {
    chassis.setDriveConstants(1500.0, 00.0, 10000.0, 10000, 0.0);
	chassis.setTurnConstants(400.0, 10.0, 4000.0, 12000, 15.0);
	chassis.setSwingConstants(550.0, 10.0, 6000.0, 12000, 15.0);
	chassis.setHeadingConstants(400.0, 0.0, 1000.0, 6000, 0.0);

	chassis.setTurnExitConditions(1, 100, 1000);
	chassis.setDriveExitConditions(1, 100, 2000);
	chassis.setSwingExitConditions(1, 100, 1000);

	chassis.chassisInit();
	chassis.startOdom();
}

void RobotMgr::robotInit () {
    // Initial drive and pneumatics states
    driveInit();
    pros::lcd::initialize();
	pros::lcd::print(2, "Finished IMU calibration");
    pneumaticsInit();
    if (robotManager == nullptr) {
        robotManager = new pros::Task {[=] {
            while (true) {
                robotManage();
                wait(10);
            }
        }};
    }
}

void RobotMgr::pneumaticsInit () {
	pneumatics[BLOCKER] = &blocker,
	pneumatics[ENDGAME] = &endgame,
	pneumatics[FLAPJACK] = &flapjacks;
    pneumatics[FLAPJACK]->set_value(false);
    pneumatics[ENDGAME]->set_value(false);
    pneumatics[BLOCKER]->set_value(false);
}

}