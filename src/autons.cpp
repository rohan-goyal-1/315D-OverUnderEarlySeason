#include "globals.h"

void farSide () {
    //TODO: set initial position
    chassis.drive_dist(45);
    chassis.turn_to_angle(-90);
    chassis.driveWithVoltage(10000, 10000);
    wait(700);
    chassis.driveWithVoltage(0, 0);
    chassis.turn_to_angle(-90);
    chassis.drive_dist(-30);
    chassis.turn_to_angle(27);
    chassis.drive_dist(-55);
    arm.set_value(true);
    wait(500);
    chassis.turn_to_angle(95);
    arm.set_value(false);
    chassis.drive_dist(10);
    chassis.turn_to_angle(-45);
    chassis.drive_dist(-20);
    chassis.turn_to_angle(-90);
    chassis.drive_dist(-17);
    arm.set_value(true);
}

void closeSide () {
    //TODO: set initial position
    chassis.drive_dist(45);
    chassis.turn_to_angle(90);
    chassis.driveWithVoltage(10000, 10000);
    wait(700);
    chassis.driveWithVoltage(0, 0);
    chassis.driveWithVoltage(-5000, -5000);
    wait(1000);
    chassis.driveWithVoltage(0, 0);
}

void progSkills () {
    flapjacks.set_value(true);
    wait(200);
    flapjacks.set_value(false);
    chassis.turn_to_angle(150);
    chassis.drive_dist(-5);
    wait(500);
    cata.move_voltage(-MAX_VOLT * 0.9);
    wait(30000); 
    cata.move_voltage(0);
    chassis.drive_dist(5);
    chassis.turn_to_angle(-120);
    chassis.drive_dist(-25);
    wait(500);
    chassis.drive_dist(25);
    while (abs(180 - chassis.getHeading()) >= 2) chassis.driveWithVoltage(0, 3000);
    chassis.driveWithVoltage(0, 0);
    chassis.drive_dist(71);
    chassis.turn_to_angle(90);
    chassis.drive_dist(21);
    chassis.turn_to_angle(0);
    chassis.drive_dist(20);
    chassis.turn_to_angle(90);
    chassis.drive_dist(30);
    chassis.gyroInit();
    chassis.turn_to_angle(90);
    flapjacks.set_value(true);
    chassis.drive_dist(25);
    wait(500);
    chassis.drive_dist(-30);
    flapjacks.set_value(false);
    chassis.turn_to_angle(0);
    chassis.drive_dist(20);
    chassis.turn_to_angle(90);
    flapjacks.set_value(true);
    chassis.drive_dist(30);
    wait(500);
    chassis.drive_dist(-30);
}