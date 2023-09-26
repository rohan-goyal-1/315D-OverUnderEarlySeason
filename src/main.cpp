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
	cata.move_voltage(stateMachine[CATA] ? 0 : -MAX_VOLT * 0.9);
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
    chassis.setDriveConstants(700.0, 5.0, 00.0, 10000, 5.0);
	chassis.setTurnConstants(120.0, 7.0, 10.0, 9000, 10.0);
	chassis.setSwingConstants(120.0, 7.0, 300.0, 9000, 10.0);
	chassis.setHeadingConstants(50.0, 0.0, 00.0, 400, 40);

	chassis.setTurnExitConditions(2, 200, 1000);
	chassis.setDriveExitConditions(1, 200, 5000);
	chassis.setSwingExitConditions(2, 200, 3000);

	chassis.chassisInit();
	chassis.startOdom();
	initPneumatics();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	// progSkills();
	farSide();
}

void opcontrol() {
	initPneumatics();
	chassis.motorInitCoast();
    while (true) {
		chassis.tankControl();
		robotManage();
		// if (master.get_digital_new_press(pros::buttonA)) {
		// 	flapjacks.set_value(true);
		// 	wait(200);
		// 	flapjacks.set_value(false);
		// 	chassis.turn_to_angle(160);
		// 	chassis.drive_dist(-5);
		// 	wait(500);
		// 	cata.move_voltage(-MAX_VOLT * 0.9);
		// 	wait(30000); 
		// 	cata.move_voltage(0);
		// 	chassis.drive_dist(5);
		// 	chassis.turn_to_angle(-120);
		// 	chassis.drive_dist(-25);
		// 	wait(500);
		// 	chassis.drive_dist(25);
		// }
		pros::lcd::set_text(4, "Left: " + to_string(chassis.getLeftPosition()) + "\tRight: " + to_string(chassis.getRightPosition()));
		pros::lcd::set_text(5, "Heading: " + to_string(chassis.getHeading()));
		pros::delay(20);
	}
}
