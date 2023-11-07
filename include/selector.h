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
        static vector<Auton> autons;
        static size_t current;
        static pros::Task* selectorTask;

    public:
        AutonSelector(void){};
        void add(void (*auton) (void), string message);
        void start(void);
        void run(void);
        static void increment(void);
        static void decrement(void);
};