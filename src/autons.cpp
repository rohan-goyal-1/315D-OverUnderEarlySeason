#include "globals.h"

void farSideAWP () {
    while (abs(45 - chassis.getHeading()) >= 2) chassis.driveWithVoltage(0, -6000);
    chassis.drive_dist(-6);
    flapjacks.set_value(true);
    wait(500);
    chassis.drive_dist(4);
    flapjacks.set_value(false);
    chassis.drive_dist(-17, 110);
    chassis.turn_to_angle(-90);
    intake.move_voltage(-MAX_VOLT);
    wait(500);
    intake.move_voltage(0);
    chassis.turn_to_angle(90);
    chassis.driveWithVoltage(-7000, -7000);
    wait(600);
    chassis.driveWithVoltage(0, 0);
    // chassis.drive_dist(-14, 90);
    wait(100);
    // chassis.drive_dist(2, 90);
    chassis.turn_to_angle(25);
    chassis.drive_dist(27, 45);
    chassis.turn_to_angle(0);
    intake.move_voltage(-MAX_VOLT);
    chassis.drive_dist(37, 0);
}

void closeSide () {
    //TODO: set initial position
    chassis.drive_dist(45, 0);
    chassis.turn_to_angle(90);
    intake.move_voltage(-MAX_VOLT);
    wait(200);
    intake.move_voltage(0);
    chassis.drive_dist(20, 90);
    wait(100);
    chassis.drive_dist(-10, 90);
    chassis.turn_to_angle(-55);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(7, -55);
    wait(500);
    chassis.turn_to_angle(90);
    intake.move_voltage(-MAX_VOLT);
    chassis.drive_dist(30, 90);
    intake.move_voltage(0);
    wait(500);
    chassis.drive_dist(-15, 90);
}

void farSide () {
    chassis.drive_dist(42, 0);
    chassis.turn_to_angle(-90);
    intake.move_voltage(-MAX_VOLT);
    wait(200);
    chassis.drive_dist(-2, -90);
    intake.move_voltage(0);
    chassis.turn_to_angle(90);
    chassis.drive_dist(-15, 90);
    wait(100);
    chassis.drive_dist(23, 90);
    chassis.turn_to_angle(0);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(5, 0);
    wait(500);
    chassis.drive_dist(-7, 0);
    intake.move_voltage(0);
    chassis.turn_to_angle(90);
    chassis.driveWithVoltage(11000, 11000);
    wait(500);
    chassis.driveWithVoltage(0, 0);
    intake.move_voltage(-MAX_VOLT);
    wait(500);
    chassis.drive_dist(-25, 90);
}

void progSkills () {
    flapjacks.set_value(true);
    wait(200);
    flapjacks.set_value(false);
    chassis.turn_to_angle(150);
    chassis.drive_dist(-7, 150);
    wait(500);
    cata.move_voltage(-MAX_VOLT * 0.9);
    wait(30000); 
    cata.move_voltage(0);
    chassis.drive_dist(1, 150);
    chassis.turn_to_angle(-130);
    chassis.drive_dist(-25, -130);
    wait(500);
    chassis.drive_dist(25, -130);
    chassis.turn_to_angle(-180);
    chassis.drive_dist(77, -180);
    chassis.turn_to_angle(90);
    chassis.drive_dist(21, 90);
    chassis.turn_to_angle(0);
    chassis.drive_dist(21, 0);
    chassis.turn_to_angle(90);
    chassis.drive_dist(30, 90);
    chassis.turn_to_angle(180);
    // flapjacks.set_value(true);
    chassis.drive_dist(25, 180);
    wait(500);
    chassis.drive_dist(-30, 180);
    flapjacks.set_value(false);
    chassis.turn_to_angle(90);
    chassis.drive_dist(20, 90);
    chassis.turn_to_angle(180);
    // flapjacks.set_value(true);
    chassis.drive_dist(30, 180);
    wait(500);
    chassis.drive_dist(-30, 180);
}