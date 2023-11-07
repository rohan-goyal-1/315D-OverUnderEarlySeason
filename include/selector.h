#pragma once

#include "globals.h"

struct Auton {
    string message;
    void (*auton) (void);
    Auton (void (*auton) (void), string message) :
        auton(auton),
        message(message)
    {}
};

class AutonSelector {
    private:
        vector<Auton> autons;
        size_t current = 0;
        pros::Task* selectorTask;

    public:
        AutonSelector(void){};
        void add(void (*auton) (void), string message);
        void start(void);
        void run();
};