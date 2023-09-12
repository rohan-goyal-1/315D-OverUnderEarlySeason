#include "globals.h"

#define INTAKE_FORW 0
#define INTAKE_REV 1
#define CATA 2
#define ARM 3
#define FLAPJACK 4
#define ENDGAME 5

vector<bool> stateMachine(6, false);
unordered_map<int, pros::adi::DigitalOut*> pneumatics;

void initPneumatics () {
	pneumatics[ARM] = &arm,
	pneumatics[ENDGAME] = &endgame,
	pneumatics[FLAPJACK] = &flapjacks;
	for (auto& [a, b] : pneumatics) b->set_value(false);
}

void intakeManage (int which) {
	if (which == INTAKE_FORW) {
		intake.move_voltage(stateMachine[INTAKE_FORW] ? 0 : MAX_VOLT);
		stateMachine[INTAKE_FORW] = !stateMachine[INTAKE_FORW];
		stateMachine[INTAKE_REV] = false;
	}
	else {
		intake.move_voltage(stateMachine[INTAKE_REV] ? 0 : -MAX_VOLT);
		stateMachine[INTAKE_REV] = !stateMachine[INTAKE_REV];
		stateMachine[INTAKE_FORW] = false;
	}
}

void cataManage () {
	cata.move_voltage(stateMachine[CATA] ? 0 : -MAX_VOLT * 0.925);
	stateMachine[CATA] = !stateMachine[CATA];
}

void pneuManage (int pneu) {
	pneumatics[pneu]->set_value(!stateMachine[pneu]);
	stateMachine[pneu] = !stateMachine[pneu];
}

void robotManage () {
	if (master.get_digital_new_press(pros::buttonR1)) intakeManage(INTAKE_FORW);
	if (master.get_digital_new_press(pros::buttonR2)) intakeManage(INTAKE_REV);
	if (master.get_digital_new_press(pros::buttonX)) cataManage();
	if (master.get_digital_new_press(pros::buttonL1)) pneuManage(FLAPJACK);
	if (master.get_digital_new_press(pros::buttonL2)) pneuManage(ARM);
	if (master.get_digital_new_press(pros::buttonDown)) pneuManage(ENDGAME);
}

void on_center_button() {}

void initialize() {
	pros::lcd::initialize(); pros::lcd::register_btn1_cb(on_center_button);
    chassis.setDriveConstants(500.0, 3.0, 70.0, MAX_VOLT, 20.0);
	chassis.setTurnConstants(160.0, 03.5, 16.0, MAX_VOLT, 20.0);
	chassis.setSwingConstants(235.0, 01.0, 90.0, MAX_VOLT, 40.0);
	chassis.setHeadingConstants(150.0, 0.0, 00.0, MAX_VOLT / 3, 40);

	chassis.setTurnExitConditions(3, 200, 3000);
	chassis.setDriveExitConditions(1, 200, 5000);
	chassis.setSwingExitConditions(2, 200, 3000);

	chassis.chassisInit();
	chassis.startOdom();
	initPneumatics();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	farSide();
}

void opcontrol() {
	initPneumatics();
	chassis.motorInitCoast();
    while (true) {
		chassis.tankControl();
		robotManage();
		// pros::lcd::set_text(4, "Left: " + to_string(chassis.getLeftPosition()) + "\tRight: " + to_string(chassis.getRightPosition()));
		pros::delay(20);
	}
}
