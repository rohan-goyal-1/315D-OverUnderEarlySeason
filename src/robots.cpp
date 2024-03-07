#include "globals.h"

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor intake(INTAKE_MTR), cata(CATA_MTR);
pros::adi::DigitalOut flapjacks(FLAP_P), endgame(ENDGAME_P), blocker(BLOCKER_P), descore(DESCORE_P), intake_pull(INTAKE_P);

pros::MotorGroup DriveL ({ LF, LM1, LB, });
pros::MotorGroup DriveR ({ RF, RM1, RB, });

vector<pros::IMU> gyro = {pros::IMU(Imu)};

pros::Distance distance_sensor(DIST);

Drive chassis (
	ZERO_ENCODER,
	gyro,
	&DriveR,
	&DriveL,
	36.0 / 36.0,
	2.75,
	2.75,
	5.875,
	5.0,
	nullptr,
	11.0
);
