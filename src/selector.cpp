#include "globals.h"

size_t AutonSelector::current = 0;
vector<Auton> AutonSelector::autons;
pros::Task* AutonSelector::selectorTask = nullptr;

void AutonSelector::add (void (*auton) (void), string message) {
    autons.push_back(Auton(auton, message));
}

void AutonSelector::increment () { current++; current %= autons.size(); }
void AutonSelector::decrement () { current--; current = current < 0 ? autons.size() - 1 : current; }

void AutonSelector::start () {
    pros::lcd::register_btn2_cb(&AutonSelector::increment);
    pros::lcd::register_btn0_cb(&AutonSelector::decrement);
    selectorTask = new pros::Task{[this] {
        while (Robot::RobotMgr::currState == PROGRAM_STATE::INITIALIZE) {
            pros::lcd::set_text(1, autons[current].message);
            wait(10);
        }
    }};
}

void AutonSelector::run () {
    if (Robot::RobotMgr::currState == PROGRAM_STATE::AUTONOMOUS) {
        autons[current].auton();
    }
}