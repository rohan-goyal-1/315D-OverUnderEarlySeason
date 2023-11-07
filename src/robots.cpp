#include "globals.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor intake(INTAKE_MTR), cata(CATA_MTR);
pros::adi::DigitalOut flapjacks(FLAP_P), endgame(ENDGAME_P), blocker(BLOCKER_P);
pros::adi::DigitalIn bumper(BUMPER_PORT);

pros::MotorGroup DriveL ({ LF, LM, LB, });
pros::MotorGroup DriveR ({ RF, RM, RB, });

vector<pros::IMU> gyro = {pros::IMU(Imu)};
pros::Rotation rot(-ROT);

Drive chassis (
	ZERO_ENCODER,
	gyro,
	&DriveR,
	&DriveL,
	36.0 / 60.0,
	3.25,
	2.75,
	5.875,
	5.0,
	nullptr,
	9.0
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
	5.0,
	&rot,
	9.0
);