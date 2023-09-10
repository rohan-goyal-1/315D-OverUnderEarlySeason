#include "globals.h"

void farSide () {
    //TODO: set initial position
    chassis.drive_dist(45);
    chassis.turn_to_angle(-90);
    chassis.driveWithVoltage(10000, 10000);
    wait(700);
    chassis.driveWithVoltage(0, 0);
    chassis.turn_to_angle(-90);
    chassis.driveWithVoltage(-5000, -5000);
    wait(1500);
    chassis.driveWithVoltage(0, 0);
    chassis.turn_to_angle(40);
    chassis.driveWithVoltage(-5000, -5000);
    wait(2250);
    chassis.driveWithVoltage(0, 0);
    arm.set_value(true);
    wait(200);
    chassis.turn_to_angle(100);
    arm.set_value(false);
    chassis.driveWithVoltage(5000, 5000);
    wait(1000);
    chassis.driveWithVoltage(0, 0);
    chassis.turn_to_angle(-90);
    chassis.driveWithVoltage(-5000, -5000);
    wait(400);
    chassis.driveWithVoltage(0, 0);
    arm.set_value(true);
    // chassis.turn_to_angle(-90);
    // chassis.driveWithVoltage(-5000, -5000);
    // wait(1000);
    // chassis.driveWithVoltage(0, 0);
    // arm.set_value(true);
    // chassis.drive_dist(10);
    // wait(500);
    // chassis.drive_dist(-30);
    // chassis.turn_to_angle(30);
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