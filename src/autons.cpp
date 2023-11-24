#include "globals.h"

void closeSideAWP () {
    // Outtake preload to goal
    chassis.drive_dist(40);
    chassis.turn_to_angle(-70);
    intake.move_voltage(-MAX_VOLT);
    wait(200);
    chassis.drive_dist(-7);

    // Pick up other ball
    chassis.turn_to_angle(7);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(9);
    wait(250);
    intake.move_voltage(0);
    chassis.drive_dist(-2);

    // Shove preload with back
    chassis.turn_to_angle(90);
    chassis.drive_dist(-17, 90);
    chassis.drive_dist(25, 90);
    
    // Descore matchload ball
    chassis.turn_to_angle(-135);
    chassis.drive_dist(52);
    chassis.turn_to_angle(-45);
    flapjacks.set_value(true);
    wait(250);
    chassis.drive_dist(-7, -45);
    chassis.left_swing_to_angle(-90);
    flapjacks.set_value(false);
    wait(200);

    // Push three balls into offensive zone + 
    // Touch climbing bar
    chassis.turn_to_angle(130);
    intake.move_voltage(-MAX_VOLT);
    wait(500);
    chassis.turn_to_angle(-50);
    blocker.set_value(true);
    chassis.drive_dist(-38, -90);
    intake.move_voltage(0);
}

void closeSideElims () {
    // Outtake preload to goal
    chassis.drive_dist(42);
    chassis.turn_to_angle(-90);
    flapjacks.set_value(true);
    wait(250);
    chassis.drive_dist(-28, -90);
    chassis.drive_dist(25);
    flapjacks.set_value(false);
    intake.move_voltage(-MAX_VOLT);
    wait(500);
    chassis.turn_to_angle(90);
    chassis.drive_dist(-7);
    chassis.drive_dist(25, 90);
    
    // Descore matchload ball
    chassis.turn_to_angle(-135);
    chassis.drive_dist(50);
    chassis.turn_to_angle(-45);
    flapjacks.set_value(true);
    wait(250);
    chassis.drive_dist(-7, -45);
	chassis.setSwingExitConditions(1, 100, 500);
    chassis.left_swing_to_angle(-70);
    flapjacks.set_value(false);
    wait(200);

    // Push three balls into offensive zone + 
    // Touch climbing bar
    chassis.turn_to_angle(130);
    intake.move_voltage(-MAX_VOLT);
    chassis.drive_dist(37, 90);
    intake.move_voltage(0);
    chassis.drive_dist(-40);
}

void farSide6Ball () {
    // Intake first ball
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(10);
    intake.move_voltage(0);

    // Descore matchload ball
    chassis.drive_dist(-32);
    chassis.left_swing_to_angle(-45);
    flapjacks.set_value(true);
    chassis.drive_dist(-13);
    chassis.left_swing_to_angle(-90);
    chassis.drive_dist(-5);
    flapjacks.set_value(false);
    wait(250);
    
    // Outtake first ball + push all three balls into goal
    chassis.turn_to_angle(180);
    intake.move_voltage(-MAX_VOLT);
    wait(250);
    chassis.right_swing_to_angle(100);
    chassis.driveWithVoltage(MAX_VOLT, MAX_VOLT);
    wait(200);
    chassis.driveWithVoltage(0, 0);
    intake.move_voltage(0);
    chassis.drive_dist(-7, 90);

    // Intake fourth ball + outtake it towards the goal
    chassis.turn_to_angle(25);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(48);
    intake.move_voltage(0);
    chassis.drive_dist(-15);
    chassis.turn_to_angle(140);
    intake.move_voltage(-MAX_VOLT);
    wait(200);

    chassis.right_swing_to_angle(45);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(25);
    intake.move_voltage(0);

    // Back the fifth ball into the goal using wings
    flapjacks.set_value(true);
    chassis.drive_dist(-33, 0);
    chassis.drive_dist(10);
    flapjacks.set_value(false);

    //Turn around and score sixth ball
    chassis.turn_to_angle(180);
    intake.move_voltage(-MAX_VOLT);
    wait(500);
    intake.move_voltage(0);
    chassis.drive_dist(7);
}

void farSideMidRush () {
    // Outtake preload to goal
    chassis.drive_dist(40);
    chassis.turn_to_angle(70);
    intake.move_voltage(-MAX_VOLT);
    wait(200);
    chassis.drive_dist(-10);

    // Intake 2nd ball
    chassis.turn_to_angle(-45);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(14);
    chassis.right_swing_to_angle(-90);
    intake.move_voltage(0);
    
    // Shove all three balls
    flapjacks.set_value(true);
    chassis.drive_dist(-31, -90);
    chassis.drive_dist(10);
    flapjacks.set_value(false);
    chassis.turn_to_angle(90);
    intake.move_voltage(-MAX_VOLT);
    wait(500);
    intake.move_voltage(0);
    chassis.drive_dist(7);
    chassis.drive_dist(-10);

    // Intake 4th ball
    chassis.turn_to_angle(-135);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(20);
    chassis.left_swing_to_angle(-90);

    // Score 4th ball
    chassis.drive_dist(-30, 135);
    chassis.turn_to_angle(90);
    intake.move_voltage(-MAX_VOLT);
    wait(500);
    intake.move_voltage(0);
    chassis.drive_dist(7);

    // Touch pole
    chassis.drive_dist(-24);
    chassis.turn_to_angle(0);
    flapjacks.set_value(true);
    chassis.drive_dist(-35);
}

void progSkills () {
    chassis.drive_dist(-20, -65);
    chassis.right_swing_to_angle(0);
    chassis.drive_dist(15, -45);
    chassis.turn_to_angle(-110);
    chassis.drive_dist(-3);
    flapjacks.set_value(true);
    cata.move_voltage(MAX_VOLT * 0.8);
    wait(33000); 
    cata.move_voltage(0);
    flapjacks.set_value(false);
    chassis.left_swing_to_angle(-35);
    chassis.drive_dist(7);
    chassis.right_swing_to_angle(-90);
    chassis.drive_dist(70);
    chassis.turn_to_angle(90);
    chassis.drive_dist(-10);
    chassis.left_swing_to_angle(45);
    chassis.drive_dist(-10);
    chassis.left_swing_to_angle(0);
    chassis.drive_dist(-5);
    chassis.drive_dist(7);
    intake.move_voltage(-MAX_VOLT);
    chassis.driveWithVoltage(-MAX_VOLT, -MAX_VOLT);
    wait(700);
    chassis.driveWithVoltage(0, 0);
    chassis.drive_dist(7);
    chassis.driveWithVoltage(-MAX_VOLT, -MAX_VOLT);
    wait(700);
    chassis.driveWithVoltage(0, 0);
    chassis.drive_dist(10, 45);
    chassis.turn_to_angle(-65);
    chassis.drive_dist(-35);
    flapjacks.set_value(true);
    chassis.right_swing_to_angle(90, 8000);
    chassis.drive_dist(-18, 90);
    flapjacks.set_value(false);
    chassis.drive_dist(20, 90);
    flapjacks.set_value(true);
    chassis.driveWithVoltage(-MAX_VOLT, -MAX_VOLT);
    wait(750);
    chassis.driveWithVoltage(0, 0);
    flapjacks.set_value(false);
    chassis.drive_dist(30, 75);
    chassis.turn_to_angle(0);
    chassis.drive_dist(-30, 0, 8000, 6000);
    chassis.right_swing_to_angle(135, 6000);
    flapjacks.set_value(true);
    chassis.drive_dist(-20, 135, 8000, 6000);
    chassis.drive_dist(-17, 90);
    flapjacks.set_value(false);
    chassis.drive_dist(20, 90);
    flapjacks.set_value(true);
    chassis.driveWithVoltage(-MAX_VOLT, -MAX_VOLT);
    wait(750);
    chassis.driveWithVoltage(0, 0);
    chassis.drive_dist(20);
}