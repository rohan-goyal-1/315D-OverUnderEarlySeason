#include "globals.h"

// Initialize static variables
vector<bool> Robot::RobotMgr::stateMachine(6, false);
vector<pros::adi::DigitalOut*> Robot::RobotMgr::pneumatics(6, NULL);
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
        // if (intake.get_actual_velocity() > 2 && intake.get_voltage() == 0) {
        //     wait(500);
        //     chassis.gyroInit();
        // }
        break;
    }
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
    chassis.setDriveConstants(700.0, 5.0, 00.0, 10000, 5.0);
	chassis.setTurnConstants(120.0, 8.0, 10.0, 9000, 10.0);
	chassis.setSwingConstants(170.0, 8.0, 12.0, 9000, 10.0);
	chassis.setHeadingConstants(120.0, 10.0, 50.0, 1000, 40);

	chassis.setTurnExitConditions(1, 200, 1000);
	chassis.setDriveExitConditions(1, 200, 2000);
	chassis.setSwingExitConditions(2, 200, 3000);

	chassis.chassisInit();
	chassis.startOdom();
}

void RobotMgr::robotInit () {
    // Initial drive and pneumatics states
    driveInit();
    // TODO: uncomment
    // pneumaticsInit();
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
    for (auto& p : pneumatics) p->set_value(false);
}

}