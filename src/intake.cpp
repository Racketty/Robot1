#include "main.h"
#include "subsystems.hpp"

enum IntakeState {
    INTAKE_OFF,
    INTAKE_FORWARD,
    INTAKE_REVERSE
};

void set_top(int input) {
  top.move(input);
}

void set_bottom(int input) {
  top.move(input);
}

void set_outtake(int input) {
    outtake.move(input);
}

void set_scoreTop(int input) {
    scoreTop.move(input);
}
/*
void intake_opcontrol() {
    static IntakeState intake_state = INTAKE_OFF; 

    if (master.get_digital_new_press(DIGITAL_R1)) {
        // If the motor is currently OFF or REVERSE, set it to FORWARD
        if (intake_state != INTAKE_FORWARD) {
            intake_state = INTAKE_FORWARD;
        } 
        // If the motor is already FORWARD, turn it OFF
        else {
            intake_state = INTAKE_OFF;
        }
    }

    if (master.get_digital_new_press(DIGITAL_R2)) {
        // If the motor is currently OFF or FORWARD, set it to REVERSE
        if (intake_state != INTAKE_REVERSE) {
            intake_state = INTAKE_REVERSE;
        } 
        // If the motor is already REVERSE, turn it OFF
        else {
            intake_state = INTAKE_OFF;
        }
    }

    switch (intake_state) {
        case INTAKE_FORWARD:
            // R1 Toggled ON: Move forward at full power
            intake.move(127);
            break;
            
        case INTAKE_REVERSE:
            // R2 Toggled ON: Move backward at full power
            intake.move(-127);
            break;
            
        case INTAKE_OFF:
        default:
            // Both Toggled OFF: Stop motor
            intake.move(0);
            break;
    }
}
*/

int top_power;   // motors -20
int bottom_power;   // motor 10

void intake_apply() {
    top.move(top_power);       // motor -20
    bottom.move(bottom_power); // motor 10
}

void intake_toggle_update() {
    static IntakeState intake_state = INTAKE_OFF;

    if (master.get_digital_new_press(DIGITAL_R1)) {
        intake_state = (intake_state == INTAKE_FORWARD) ? INTAKE_OFF : INTAKE_FORWARD;
    }

    if (master.get_digital_new_press(DIGITAL_R2)) {
        intake_state = (intake_state == INTAKE_REVERSE) ? INTAKE_OFF : INTAKE_REVERSE;
    }

    switch (intake_state) {
        case INTAKE_FORWARD: top_power = 127; bottom_power = 127; break;
        case INTAKE_REVERSE: top_power = -127; bottom_power = -127; break;
        case INTAKE_OFF:     top_power = 0; bottom_power = 0; break;
    }

    if (master.get_digital(DIGITAL_A)) {
    intake_state = INTAKE_OFF;
    top_power = 127;
    bottom_power = -127;
    }
}





void outtake_opcontrol() {
    if (master.get_digital(DIGITAL_L1)) {
      outtake.move(127);
      scoreTop.move(127);

    } 
    else if (master.get_digital(DIGITAL_L2)) {
      outtake.move(-127);
      scoreTop.move(127);
    } 
    else {
      outtake.move(0);
      scoreTop.move(0);
    }
}
