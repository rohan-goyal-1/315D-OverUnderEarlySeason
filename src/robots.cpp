#include "globals.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor intake(INTAKE_MTR), cata(CATA_MTR);
pros::adi::DigitalOut flapjacks(FLAP_P), endgame(ENDGAME_P), arm(ARM_P);

// pros::MotorGroup DriveL ({ LF, LM, LB, }, pros::v5::MotorGears::blue); 
// pros::MotorGroup DriveR ({ RF, RM, RB, }, pros::v5::MotorGears::blue); 

// pros::MotorGroup DriveL ({ LF, LM, LB, }, pros::v5::MotorGears::green); 
// pros::MotorGroup DriveR ({ RF, RM, RB, }, pros::v5::MotorGears::green); 

pros::MotorGroup DriveL ({ LF, LM, LB, });
pros::MotorGroup DriveR ({ RF, RM, RB, });

vector<pros::IMU> gyro = {/* pros::IMU(imu1), */pros::IMU(imu2)};

Drive chassis (
	ZERO_ENCODER,
	gyro,
	&DriveR,
	&DriveL,
	36.0 / 60.0,
	3.25,
	0.0,
	5.875,
	0.0,
	NULL
);

Drive prog_chassis (
	ONE_ENCODER,
	gyro,
	&DriveR,
	&DriveL,
	36.0 / 60.0,
	3.25,
	2.75,
	5.875,
	// TODO: change side encoder values once it is attached
	0.0,
	NULL
);