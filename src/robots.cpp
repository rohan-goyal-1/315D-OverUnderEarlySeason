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
	gyro,
	&DriveR,
	&DriveL,
	36.0 / 60.0,
	3.25
);