#include "globals.h"

// Initialize static variables
vector<bool> Robot::RobotMgr::stateMachine(5, false);
vector<pros::adi::DigitalOut*> Robot::RobotMgr::pneumatics(5, nullptr);
pros::Task* Robot::RobotMgr::robotManager = nullptr;
PROGRAM_STATE Robot::RobotMgr::currState = PROGRAM_STATE::INITIALIZE;

namespace Robot {

void RobotMgr::robotManage () {
    intakeManage();
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
            pneumatics[INTAKE_PULL]->set_value(!stateMachine[INTAKE_PULL]);
            stateMachine[INTAKE_PULL] = !stateMachine[INTAKE_PULL];
        }
    }
}

bool RobotMgr::intakeStopped () {
    // return distance_sensor.get() <= 30;
    return false;
    // return stateMachine[INTAKE_FORW] && intake.get_actual_velocity() < 10;
}

void RobotMgr::intakeManage () {
    switch (currState) {
    
    case PROGRAM_STATE::OPCONTROL:
        if (intakeStopped()) {
            if (master.get_digital_new_press(pros::buttonR2)) {
                intake.move_voltage(stateMachine[INTAKE_REV] ? 0 : MAX_VOLT);
                stateMachine[INTAKE_REV] = !stateMachine[INTAKE_REV];
                stateMachine[INTAKE_FORW] = false;
            }
            else {
                intake.move_voltage(0);
                stateMachine[INTAKE_REV] = false;
            }
        }
        else {
            if (master.get_digital_new_press(pros::buttonR2)) {
                intake.move_voltage(stateMachine[INTAKE_REV] ? 0 : MAX_VOLT);
                stateMachine[INTAKE_REV] = !stateMachine[INTAKE_REV];
                stateMachine[INTAKE_FORW] = false;
            }
            if (master.get_digital_new_press(pros::buttonR1)) {
                intake.move_voltage(stateMachine[INTAKE_FORW] ? 0 : -MAX_VOLT);
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
        waitUntil(intakeStopped() || pros::millis() - start >= timeout);
        intake.move_voltage(0);
    }};
}

void RobotMgr::outtakeBall (double timeout) {
    pros::Task* outtakeTask = new pros::Task {[=] {
        double start = pros::millis();
        intake.move_voltage(-MAX_VOLT);
        waitUntil(!intakeStopped() || pros::millis() - start >= timeout);
        intake.move_voltage(0);
    }};
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
	pneumatics[FLAPJACK] = &flapjacks;
    pneumatics[FLAPJACK]->set_value(false);
	pneumatics[INTAKE_PULL] = &intake_pull;
    pneumatics[INTAKE_PULL]->set_value(false);
}

}
