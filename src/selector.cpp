#include "globals.h"

void AutonSelector::add (void (*auton) (void), string message) {
    autons.push_back(Auton(auton, message));
}

void AutonSelector::start () {
    //TODO: make it to touch screen based
    if (Robot::RobotMgr::currState == PROGRAM_STATE::INITIALIZE) {
        selectorTask = new pros::Task{[this] {
            while (true) {
                if (Robot::RobotMgr::currState != PROGRAM_STATE::INITIALIZE) {
                    selectorTask->remove();
                }
                if (bumper.get_new_press())
                    current++;
                current %= autons.size();
                pros::lcd::set_text(1, autons[current].message);
                wait(10);
            }
        }};
    }
    else {
        selectorTask->remove();
    }
}

void AutonSelector::run () {
    if (Robot::RobotMgr::currState == PROGRAM_STATE::AUTONOMOUS) {
        autons[current].auton();
    }
}