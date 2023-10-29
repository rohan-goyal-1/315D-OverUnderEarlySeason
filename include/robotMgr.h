#pragma once

#include "globals.h"

#define INTAKE_FORW 0
#define INTAKE_REV 1
#define CATA 2
#define BLOCKER 3
#define FLAPJACK 4
#define ENDGAME 5

enum PROGRAM_STATE {
    OPCONTROL,
    AUTONOMOUS,
    INITIALIZE
};

namespace Robot {

class RobotMgr {
    public:
        static vector<bool> stateMachine;
        static vector<pros::adi::DigitalOut*> pneumatics;
        static pros::Task* robotManager;
        static PROGRAM_STATE currState;
        static void intakeManage(void);
        static void cataManage(void);
        static void pneuManage(void);
        static void robotInit(void);
        static void pneumaticsInit(void);
        static void driveInit(void);
        static void robotManage(void);
};

}