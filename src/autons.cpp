#include "globals.h"

void closeSideAWP () {
    // chassis.right_swing_to_angle(-45);
    // chassis.drive_dist(20);
    // chassis.left_swing_to_angle(0);
    // intake.move_voltage(MAX_VOLT);
    // wait(250);
    // chassis.drive_dist(-6);
    // chassis.drive_dist(7);
    // chassis.drive_dist(-3);
    // chassis.left_swing_to_angle(-45);
    // chassis.drive_dist(-12);
    // flapjacks.set_value(true);
    // wait(500);
    // chassis.left_swing_to_angle(-80);
    // flapjacks.set_value(false);
    // wait(500);
    // chassis.drive_dist(-8);
    // chassis.turn_to_angle(90, 7000, false);
    // chassis.drive_dist(32, 90, 3000, 1000);
    chassis.right_swing_to_angle(45);
    chassis.drive_dist(-3);
    flapjacks.set_value(true);
    chassis.drive_dist(5);
    chassis.right_swing_to_angle(0);
    chassis.drive_dist(3);
    flapjacks.set_value(false);
    chassis.right_swing_to_angle(90);
    chassis.drive_dist(-7);
    chassis.turn_to_angle(205);
    chassis.drive_dist(9);
    chassis.turn_to_angle(-90);
    intake.move_voltage(MAX_VOLT);
    wait(500);
    intake.move_voltage(0);
    intake_pull.set_value(false);
    wait(200);
    chassis.drive_dist(7);
    chassis.drive_dist(-4);
    chassis.turn_to_angle(45);
    chassis.drive_dist(22);
    chassis.right_swing_to_angle(0);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(29, 0, 3000, 1000, false);
}

void closeSideElims () {
 //    // Outtake preload to goal
 //    chassis.drive_dist(42);
 //    chassis.turn_to_angle(-90);
 //    flapjacks.set_value(true);
 //    wait(250);
 //    chassis.drive_dist(-28, -90, false);
 //    chassis.drive_dist(25);
 //    flapjacks.set_value(false);
 //    intake.move_voltage(-MAX_VOLT);
 //    wait(500);
 //    chassis.turn_to_angle(90);
 //    chassis.drive_dist(-7);
 //    chassis.drive_dist(25, 90, false);
 //    
 //    // Descore matchload ball
 //    chassis.turn_to_angle(-135);
 //    chassis.drive_dist(50);
 //    chassis.turn_to_angle(-45);
 //    flapjacks.set_value(true);
 //    wait(250);
 //    chassis.drive_dist(-7, -45, false);
	// chassis.setSwingExitConditions(1, 100, 500);
 //    chassis.left_swing_to_angle(-70);
 //    flapjacks.set_value(false);
 //    wait(200);
	//
 //    // Push three balls into offensive zone + 
 //    // Touch climbing bar
 //    chassis.turn_to_angle(130);
 //    intake.move_voltage(-MAX_VOLT);
 //    chassis.drive_dist(37, 90, false);
 //    intake.move_voltage(0);
 //    chassis.drive_dist(-40);
    // chassis.drive_dist(-41);
    // chassis.turn_to_angle(90);
    // flapjacks.set_value(true);
    // wait(200);
    // chassis.drive_dist(-25, 90, false);
    // wait(200);
    // intake.move_voltage(MAX_VOLT);
    // chassis.drive_dist(10, 105, false);
    // flapjacks.set_value(false);
    // wait(500);
    // chassis.turn_to_angle(36);
    // chassis.drive_dist(50);
    // chassis.turn_to_angle(135);
    // chassis.drive_dist(-2);
    // wait(200);
    // flapjacks.set_value(true);
    // wait(100);
    // // chassis.drive_dist(7.5);
    // wait(500);
    // chassis.left_swing_to_angle(80);
    // wait(100);
    // flapjacks.set_value(false);
    // wait(500);
    // chassis.drive_dist(-8);
    // chassis.turn_to_angle(-70, 7000, false);
    // chassis.drive_dist(5);
    // chassis.drive_dist(-23, -90, false);
    chassis.drive_dist(41, 0, false);
    chassis.turn_to_angle(90);
    flapjacks.set_value(true);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(31);
    wait(200);
    flapjacks.set_value(false);
    chassis.turn_to_angle(30);
    chassis.drive_dist(-47);
    chassis.right_swing_to_angle(135);
    chassis.drive_dist(-10);
    flapjacks.set_value(true);
    wait(200);
    chassis.drive_dist(12);
    chassis.right_swing_to_angle(90);
    wait(200);
    flapjacks.set_value(false);
    intake.move_voltage(MAX_VOLT);
    chassis.drive_dist(30);
    wait(200);
    chassis.drive_dist(-38);
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
    chassis.drive_dist(-7, 90, false);

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
    chassis.drive_dist(-33, 0, false);
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
    chassis.turn_to_angle(90);
    intake.move(MAX_VOLT);
    wait(200);
    chassis.setDriveExitConditions(1, 100, 1000);
    chassis.drive_dist(16);
	chassis.setDriveExitConditions(1, 100, 2000);
    wait(500);
    chassis.drive_dist(-10);
    chassis.turn_to_angle(-115);
    intake.move_voltage(-MAX_VOLT);
    chassis.drive_dist(30);
    wait(200);
    chassis.left_swing_to_angle(-160);
    chassis.drive_dist(-8, -180, false);
    chassis.turn_to_angle(-90);
    chassis.turn_to_angle(0);
    chassis.drive_dist(3);
    chassis.turn_to_angle(90);
    flapjacks.set_value(true);
    wait(500);
    intake.move_voltage(MAX_VOLT);
    chassis.setDriveExitConditions(1, 100, 1000);
    chassis.drive_dist(28);
	chassis.setDriveExitConditions(1, 100, 2000);
    wait(750);
    flapjacks.set_value(false);
    chassis.drive_dist(-15, 45, false);
    chassis.turn_to_angle(-70);
    intake.move_voltage(-MAX_VOLT);
    chassis.drive_dist(15);
    chassis.drive_dist(-7);
    intake.move_voltage(0);
    chassis.turn_to_angle(90);
    flapjacks.set_value(true);
    intake.move_voltage(MAX_VOLT);
    wait(200);
    chassis.setDriveExitConditions(1, 100, 1000);
    chassis.drive_dist(25);
	chassis.setDriveExitConditions(1, 100, 2000);
    wait(500);
    chassis.drive_dist(-20);
    // chassis.drive_dist(-10);
    // chassis.turn_to_angle(-45);
    //
    // // Intake 2nd ball
    // chassis.turn_to_angle(-45);
    // intake.move_voltage(-MAX_VOLT);
    // chassis.drive_dist(14);
    // chassis.right_swing_to_angle(-90);
    // intake.move_voltage(0);
    //
    // // Shove all three balls
    // flapjacks.set_value(true);
    // chassis.drive_dist(-31, -90, false);
    // chassis.drive_dist(10);
    // flapjacks.set_value(false);
    // chassis.turn_to_angle(90);
    // intake.move_voltage(MAX_VOLT);
    // wait(500);
    // intake.move_voltage(0);
    // chassis.drive_dist(7);
    // chassis.drive_dist(-10);
    //
    // // Intake 4th ball
    // chassis.turn_to_angle(-135);
    // intake.move_voltage(-MAX_VOLT);
    // chassis.drive_dist(20);
    // chassis.left_swing_to_angle(-90);
    //
    // // Score 4th ball
    // chassis.drive_dist(-30, 135, false);
    // chassis.turn_to_angle(90);
    // intake.move_voltage(MAX_VOLT);
    // wait(500);
    // intake.move_voltage(0);
    // chassis.drive_dist(7);
}

void progSkills () {
    chassis.drive_dist(-20, -65, false);
    chassis.right_swing_to_angle(0);
    chassis.drive_dist(15, -45, false);
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
    chassis.drive_dist(10, 45, false);
    chassis.turn_to_angle(-65);
    chassis.drive_dist(-35);
    flapjacks.set_value(true);
    chassis.right_swing_to_angle(90, 8000, false);
    chassis.drive_dist(-18, 90, false);
    flapjacks.set_value(false);
    chassis.drive_dist(20, 90, false);
    flapjacks.set_value(true);
    chassis.driveWithVoltage(-MAX_VOLT, -MAX_VOLT);
    wait(750);
    chassis.driveWithVoltage(0, 0);
    flapjacks.set_value(false);
    chassis.drive_dist(30, 75, false);
    chassis.turn_to_angle(0);
    chassis.drive_dist(-30, 0, 8000, 6000);
    chassis.right_swing_to_angle(135, 6000, false);
    flapjacks.set_value(true);
    chassis.drive_dist(-20, 135, 8000, 6000);
    chassis.drive_dist(-17, 90, false);
    flapjacks.set_value(false);
    chassis.drive_dist(20, 90, false);
    flapjacks.set_value(true);
    chassis.driveWithVoltage(-MAX_VOLT, -MAX_VOLT);
    wait(750);
    chassis.driveWithVoltage(0, 0);
    chassis.drive_dist(20);
}
