#include "globals.h"

Drive::Drive(DriveType drive_type, vector<pros::IMU>& gyro, pros::MotorGroup* DriveR, pros::MotorGroup* DriveL, double gearRatio, double wheelDiam, double sideDiam, double forwDist, double sideDist, pros::Rotation* sideEncoder, double trackWidth) :
    gyro(gyro),
    DriveR(DriveR),
    DriveL(DriveL),
    gearRatio(gearRatio),
    wheelCircum(wheelDiam * PI),
    odom(Odom(Position(0, 0, 0), forwDist, sideDist, 0, 0)),
    sideCircum(sideDiam * PI),
    sideEncoder(sideEncoder),
    trackWidth(trackWidth)
{}

void Drive::setHeading(double heading) {
    for (auto& imu : gyro) imu.set_heading(heading);
}

void Drive::setPosition(Position p) {
    odom.pos = p;
    setHeading(p.heading);
}

Position Drive::getPosition (bool radians) {
    if (!radians) {
        return odom.pos;
    }
    return Position(odom.pos.x, odom.pos.y, to_rad(odom.pos.heading));
}

void Drive::chassisInit() {
    gyroInit();
    motorInitBrake();
    if (drive_type == DriveType::ONE_ENCODER && sideEncoder != nullptr) {
        sideEncoder->reset();
    }
}

void Drive::motorInitBrake() {
    DriveR->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
    DriveL->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);

    DriveR->set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
    DriveL->set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
}

void Drive::motorInitCoast() {
    DriveR->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
    DriveL->set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);

    DriveR->set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
    DriveL->set_brake_mode_all(pros::E_MOTOR_BRAKE_COAST);
}

void imu_display (int time) {
    if (pros::lcd::is_initialized()) return;

    int border = 50;

    pros::screen::set_pen(pros::Color::white);
    for (int i = 1; i < 3; i++) {
        pros::screen::draw_rect(border + i, border + i, 480 - border - i, 240 - border - i);
    }

    static int last_x1 = border;
    pros::screen::set_pen(pros::Color::royal_blue); 
    int x1 = (time * ((480 - (border * 2)) / 2000.0)) + border;
    pros::screen::fill_rect(last_x1, border, x1, 240 - border);
    last_x1 = x1;
}

void Drive::gyroInit() {
    // Set background
    pros::screen::set_pen(pros::Color::black);
    pros::screen::fill_rect(1, 1, 1000, 1000);
    for (auto& imu : gyro) { 
        imu.reset(); 
        int time = 0;
        while (imu.is_calibrating()) {
            time += 10;
            imu_display(time);
            pros::delay(10);
        }
    }
    master.rumble("-");
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
    // Create the PID object to calculate the outputs
    PID turnPID(kp, ki, kd, starti, settle_error, settle_time, timeout);

    // Start the running time here
    turnPID.start();
    
    // Compute and move the drivetrain until the exit conditions are met
    while (!turnPID.is_settled()) {
        // Update the error values
        double error = reduceDiff(angle, this->getHeading());

        //Compute the output based on the error and drive the chassis
        double output = clamp(turnPID.compute(error), -maxVolt, maxVolt);
        this->driveWithVoltage(output, -output);

        // Delay to avoid hogging the processor
        pros::delay(5);
    }
    // Brake when exit conditions are met
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
    PID swingPID(kp, ki, kd, starti, settle_error, settle_time, timeout);

    // Start time
    swingPID.start();
    
    while (!swingPID.is_settled()) {
        double error = reduceDiff(angle, this->getHeading());

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
    PID swingPID(kp, ki, kd, starti, settle_error, settle_time, timeout);

    // Start time
    swingPID.start();
    
    while (!swingPID.is_settled()) {
        double error = reduceDiff(angle, this->getHeading());

        double output = clamp(swingPID.compute(error), -maxVolt, maxVolt);

        this->driveWithVoltage(0, -output);

        // Delay to avoid hogging the processor
        pros::delay(5);
    }
    this->driveWithVoltage(0, 0);
}

void Drive::drive_dist(double dist) {
    drive_dist(dist, this->getHeading());
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
   PID drivePID(drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
   PID headingPID(heading_kp, heading_ki, heading_kd, heading_starti);
    
    double start_pos = (this->getLeftPosition() + this->getRightPosition()) / 2;
    while (!drivePID.is_settled()) {
        double drive_error = start_pos + dist - ((this->getLeftPosition() + this->getRightPosition()) / 2);
        double heading_error = reduceDiff(heading, this->getHeading());

        double drive_output = clamp(drivePID.compute(drive_error), -drive_maxVolt, drive_maxVolt);
        double heading_output = clamp(headingPID.compute(heading_error), -heading_maxVolt, heading_maxVolt);

        this->driveWithVoltage(drive_output + heading_output, drive_output - heading_output);
        // Delay to avoid hogging processor
        pros::delay(5);
    }
    this->driveWithVoltage(0, 0);
}

double Drive::getForwPos () {
    return this->getRightPosition();
}

double Drive::getSidePos () {
    if (drive_type == ZERO_ENCODER) return 0.0;
    return sideEncoder->get_position() / 36000 * sideCircum;
}

void Drive::startOdom () {
    odomTask = new pros::Task{[this] {
        while (true) {
            odom.update(this->getForwPos(), this->getSidePos(), this->getHeading());
            pros::lcd::set_text(6, odom.pos.toString());
            wait(10);
        }
    }};
}

void Drive::pauseOdom () {
    odomTask->suspend();
}

void Drive::resumeOdom () {
    odomTask->resume();
}

void Drive::tankControl () {
    if (Robot::RobotMgr::currState == PROGRAM_STATE::OPCONTROL) {
    double l = pros::Controller(pros::E_CONTROLLER_MASTER).get_analog(pros::jly);
    double r = pros::Controller(pros::E_CONTROLLER_MASTER).get_analog(pros::jry);

    this->driveWithVoltage(pct_to_volt(l), pct_to_volt(r));
    }
}

void Drive::move_to_point (Position point, bool forwards) {
    move_to_point(point, drive_maxVolt, forwards);
}

void Drive::move_to_point (Position point, double maxVolt, bool forwards, double lead, double chasePower) {
    if (!mutex.take(10)) return;

    Position target(point.x, point.y, PI / 2 - to_rad(point.heading)); 
    Position lastPose = this->getPosition();
    PID linearPID = PID(drive_kp, drive_ki, drive_kd, drive_starti, drive_settle_error, drive_settle_time, drive_timeout);
    PID angularPID = PID(turn_kp, turn_ki, turn_kd, turn_starti);
    double prevLinearPower = 0;
    PROGRAM_STATE compState = Robot::RobotMgr::currState;
    int start = pros::millis();
    distTravelled = 0;

    if (!forwards) target.heading = fmod(target.heading + PI, 2 * PI); // backwards movement

    bool close = false; // used for settling

    while (Robot::RobotMgr::currState == compState && !linearPID.is_settled()) {
        Position pose = this->getPosition(true);
        if (!forwards) pose.heading += PI;
        pose.heading = PI / 2 - pose.heading;

        distTravelled += pose.distance(lastPose);
        lastPose = pose;

        if (pose.distance(target) < 7.5 && close == false) {
            close = true;
            maxVolt = fmax(fabs(prevLinearPower), 30);
        }

        Position carrot = target - (Position(cos(target.heading), sin(target.heading), 0) * lead * pose.distance(target));
        if (close) carrot = target;

        double angularError = to_rad(reduceDiff(pose.angle(carrot), pose.heading));
        double linearError = pose.distance(carrot) * cos(angularError);
        if (close) angularError = to_rad(reduceDiff(target.heading, pose.heading));
        if (!forwards) linearError = -linearError;

        double angularPower = -angularPID.compute(to_deg(angularError));
        double linearPower = linearPID.compute(linearError);

        double curvature = fabs(getCurvature(pose, carrot));
        if (curvature == 0) curvature = -1;
        double radius = 1 / curvature;

        if (radius != -1) {
            double maxTurnSpeed = sqrt(chasePower * radius * 9.8);
            if (linearPower > maxTurnSpeed && !close) linearPower = maxTurnSpeed;
            else if (linearPower < -maxTurnSpeed && !close) linearPower = -maxTurnSpeed;
        }

        double overturn = fabs(angularPower) + fabs(linearPower) - maxVolt;
        if (overturn > 0) linearPower -= linearPower > 0 ? overturn : -overturn;
        prevLinearPower = linearPower;

        double leftPower = linearPower + angularPower;
        double rightPower = linearPower - angularPower;

        this->driveWithVoltage(leftPower, rightPower);

        pros::delay(10); 
    }

    this->driveWithVoltage(0, 0);
    distTravelled = -1;
    mutex.give();
}
double Drive::getCurvature (Position pose, Position other) {
    double side = sign(sin(pose.heading) * (other.x - pose.x) - cos(pose.heading) * (other.y - pose.y));
    double a = -tan(pose.heading);
    double c = tan(pose.heading) * pose.x - pose.y;
    double x = fabs(a * other.x + other.y + c) / sqrt((a * a) + 1);
    double d = hypot(other.x - pose.x, other.y - pose.y);

    return side * ((2 * x) / (d * d));
}

void Drive::turn_and_drive (double heading, double dist, double turnVolt, double tolerance) {
    double error = reduceDiff(heading, this->getHeading());
    while (abs(error) > tolerance) {
        this->driveWithVoltage(turnVolt * sign(error), -turnVolt * sign(error));
        error = reduceDiff(heading, this->getHeading());
    }
    this->drive_dist(dist, heading);
}

void Drive::left_swing_and_drive (double heading, double dist, double turnVolt, double tolerance) {
    double error = reduceDiff(heading, this->getHeading());
    while (abs(error) > tolerance) {
        this->driveWithVoltage(turnVolt * sign(error), 0);
        error = reduceDiff(heading, this->getHeading());
    }
    this->drive_dist(dist, heading);
}

void Drive::right_swing_and_drive (double heading, double dist, double turnVolt, double tolerance) {
    double error = reduceDiff(heading, this->getHeading());
    while (abs(error) > tolerance) {
        this->driveWithVoltage(0, -turnVolt * sign(error));
        error = reduceDiff(heading, this->getHeading());
    }
    this->drive_dist(dist, heading);
}