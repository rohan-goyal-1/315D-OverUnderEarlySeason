#include "globals.h"

Drive::Drive(vector<pros::IMU>& gyro, pros::MotorGroup* DriveR, pros::MotorGroup* DriveL, double gearRatio, double wheelDiam) :
    gyro(gyro),
    DriveR(DriveR),
    DriveL(DriveL),
    gearRatio(gearRatio),
    wheelDiam(wheelDiam),
    wheelCircum(wheelDiam * PI),
    pos(Position(0, 0, 0))
{}

void Drive::setPosition(Position p) {
    pos = p;
}

void Drive::chassisInit() {
    gyroInit();
    motorInitBrake();
}

void Drive::motorInitBrake() {
    DriveR->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
    DriveL->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);

    DriveR->set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    DriveL->set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
	pros::lcd::print(3, "Motors set to brake.");
}

void Drive::motorInitCoast() {
    DriveR->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
    DriveL->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);

    DriveR->set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    DriveL->set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
	pros::lcd::print(3, "Motors set to coast.");
}

void Drive::gyroInit() {
    for (auto& imu : gyro) { 
        imu.reset(); 
        while (imu.is_calibrating()) pros::delay(5);
    }
	pros::lcd::print(2, "Finished gyro calibration");
}

void Drive::driveWithVoltage(double left, double right) {
    if (left != 0.0) DriveL->move_voltage(left);
    else DriveL->brake();
    if (right != 0.0) DriveR->move_voltage(right);
    else DriveR->brake();
}

double Drive::getHeading() {
    double sum = 0;
    for (auto& imu : gyro) 
        sum += imu.get_yaw();
    return sum / gyro.size();
}

double Drive::getRightPosition() {
    vector<double> positions = DriveR->get_position_all();
    double avg = accumulate(positions.begin(), positions.end(), 0);

    return avg / 360.0 * wheelCircum * gearRatio;
}


double Drive::getLeftPosition() {
    vector<double> positions = DriveL->get_position_all();
    double avg = accumulate(positions.begin(), positions.end(), 0);

    return avg / 360.0 * wheelCircum * gearRatio;
}

void Drive::setDriveConstants(double kp, double ki, double kd) {
    setDriveConstants(kp, ki, kd, 12000, 40);
}

void Drive::setDriveConstants(double kp, double ki, double kd, double max_volt, double starti) {
    drive_kp = kp;
    drive_ki = ki;
    drive_kd = kd;
    drive_maxVolt = max_volt;
    drive_starti = starti;
}

void Drive::setTurnConstants(double kp, double ki, double kd) {
    setTurnConstants(kp, ki, kd, 12000, 40);
}

void Drive::setTurnConstants(double kp, double ki, double kd, double max_volt, double starti) {
    turn_kp = kp;
    turn_ki = ki;
    turn_kd = kd;
    turn_maxVolt = max_volt;
    turn_starti = starti;
}

void Drive::setSwingConstants(double kp, double ki, double kd) {
    setSwingConstants(kp, ki, kd, 12000, 40);
}

void Drive::setSwingConstants(double kp, double ki, double kd, double max_volt, double starti) {
    swing_kp = kp;
    swing_ki = ki;
    swing_kd = kd;
    swing_maxVolt = max_volt;
    swing_starti = starti;
}

void Drive::setHeadingConstants(double kp, double ki, double kd) {
    setHeadingConstants(kp, ki, kd, 12000, 40);
}

void Drive::setHeadingConstants(double kp, double ki, double kd, double max_volt, double starti) {
    heading_kp = kp;
    heading_ki = ki;
    heading_kd = kd;
    heading_maxVolt = max_volt;
    heading_starti = starti;
}

void Drive::setDriveExitConditions(double settle_error, double settle_time, double timeout) {
    drive_settle_error = settle_error;
    drive_settle_time = settle_time;
    drive_timeout = timeout;
}

void Drive::setTurnExitConditions(double settle_error, double settle_time, double timeout) {
    turn_settle_error = settle_error;
    turn_settle_time = settle_time;
    turn_timeout = timeout;
}

void Drive::setSwingExitConditions(double settle_error, double settle_time, double timeout) {
    swing_settle_error = settle_error;
    swing_settle_time = settle_time;
    swing_timeout = timeout;
}

void Drive::turn_to_angle(double angle) {
    turn_to_angle(angle, turn_maxVolt);
}

void Drive::turn_to_angle(double angle, double maxVolt) {
    turn_to_angle(angle, maxVolt, turn_settle_error, turn_settle_time, turn_timeout);
}

void Drive::turn_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout) {
    turn_to_angle(angle, maxVolt, settle_error, settle_time, timeout, turn_kp, turn_ki, turn_kd, turn_starti);
} 

void Drive::turn_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti) {
    PID turnPID(angle - this->getHeading(), kp, ki, kd, starti, settle_error, settle_time, timeout);

    // Start time
    turnPID.start();
    
    while (!turnPID.is_settled()) {
        double error = angle - this->getHeading();

        double output = clamp(turnPID.compute(error), -maxVolt, maxVolt);
        this->driveWithVoltage(output, -output);

        // Delay to avoid hogging the processor
        pros::delay(5);
    }
    this->driveWithVoltage(0, 0);
}


void Drive::left_swing_to_angle(double angle) {
    left_swing_to_angle(angle, swing_maxVolt);
}

void Drive::left_swing_to_angle(double angle, double maxVolt) {
    left_swing_to_angle(angle, maxVolt, swing_settle_error, swing_settle_time, swing_timeout);
}

void Drive::left_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout) {
    left_swing_to_angle(angle, maxVolt, settle_error, settle_time, timeout, swing_kp, swing_ki, swing_kd, swing_starti);
} 

void Drive::left_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti) {
    PID swingPID(angle - this->getHeading(), kp, ki, kd, starti, settle_error, settle_time, timeout);

    // Start time
    swingPID.start();
    
    while (!swingPID.is_settled()) {
        double error = angle - this->getHeading();

        double output = clamp(swingPID.compute(error), -maxVolt, maxVolt);

        this->driveWithVoltage(output, 0);

        // Delay to avoid hogging the processor
        pros::delay(5);
    }
    this->driveWithVoltage(0, 0);
}

void Drive::right_swing_to_angle(double angle) {
    right_swing_to_angle(angle, swing_maxVolt);
}

void Drive::right_swing_to_angle(double angle, double maxVolt) {
    right_swing_to_angle(angle, maxVolt, swing_settle_error, swing_settle_time, swing_timeout);
}

void Drive::right_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout) {
    right_swing_to_angle(angle, maxVolt, settle_error, settle_time, timeout, swing_kp, swing_ki, swing_kd, swing_starti);
} 

void Drive::right_swing_to_angle(double angle, double maxVolt, double settle_error, double settle_time, double timeout, double kp, double ki, double kd, double starti) {
    PID swingPID(angle - this->getHeading(), kp, ki, kd, starti, settle_error, settle_time, timeout);

    // Start time
    swingPID.start();
    
    while (!swingPID.is_settled()) {
        double error = angle - this->getHeading();

        double output = clamp(swingPID.compute(error), -maxVolt, maxVolt);

        this->driveWithVoltage(0, output);

        // Delay to avoid hogging the processor
        pros::delay(5);
    }
    this->driveWithVoltage(0, 0);
}

void Drive::drive_dist(double dist) {
    drive_dist(dist, getHeading());
}

void Drive::drive_dist(double dist, double heading) {
    drive_dist(dist, heading, drive_maxVolt, heading_maxVolt);
}

void Drive::drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt) {
    drive_dist(dist, heading, drive_maxVolt, heading_maxVolt, drive_settle_error, drive_settle_time, drive_timeout);
}

void Drive::drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt, double drive_settle_error, double drive_settle_time, double drive_timeout) {
    drive_dist(dist, heading, drive_maxVolt, heading_maxVolt, drive_settle_error, drive_settle_time, drive_timeout, drive_kp, drive_ki, drive_kd, drive_starti, heading_kp, heading_ki, heading_kd, heading_starti);
}

void Drive::drive_dist(double dist, double heading, double drive_maxVolt, double heading_maxVolt, double drive_settle_error, double drive_settle_time, double drive_timeout, double drive_kp, double drive_ki, double drive_kd, double drive_starti, double heading_kp, double heading_ki, double heading_kd, double heading_starti) {
   PID drivePID(dist, drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
   PID headingPID(reduceDiff(heading, this->getHeading()), heading_kp, heading_ki, heading_kd, heading_starti);
    
    double start_pos = (this->getLeftPosition() + this->getRightPosition()) / 2;
    while (!drivePID.is_settled()) {
        double drive_error = start_pos + dist - ((this->getLeftPosition() + this->getRightPosition()) / 2);
        double heading_error = heading - this->getHeading();

        double drive_output = clamp(drivePID.compute(drive_error), -drive_maxVolt, drive_maxVolt);
        double heading_ouput = clamp(headingPID.compute(heading_error), -heading_maxVolt, heading_maxVolt);

        this->driveWithVoltage(drive_output + heading_ouput, drive_output - heading_ouput);
        // Delay to avoid hogging processor
        pros::delay(5);
    }
    this->driveWithVoltage(0, 0);
}

void Drive::tankControl() {
    double l = pros::Controller(pros::E_CONTROLLER_MASTER).get_analog(pros::jly);
    double r = pros::Controller(pros::E_CONTROLLER_MASTER).get_analog(pros::jry);

    this->driveWithVoltage(pct_to_volt(l), pct_to_volt(r));
}
