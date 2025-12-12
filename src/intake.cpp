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

int top_power;   // motors -20
int bottom_power;   // motor 10
int out_power;  // motor 19

// Optical sensor on port 5
pros::Optical optical(5);

void intake_apply() {
    top.move(top_power);       // motor -20
    bottom.move(bottom_power); // motor 10
    outtake.move(out_power);       // motor 19
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

void color_sorter() {
    // ---------------- OPTICAL COLOR LOGIC ----------------
    // Read hue from the optical sensor (0–359.999)
    double hue = optical.get_hue();

    // PROS returns negative on error -> treat as invalid
    if (hue < 0.0) {
      out_power = 0;
    } else {
      // Red: near 0° / 360° (adjust these later using real readings)
      bool is_red =
        (hue >= 0.0 && hue <= 30.0) ||
        (hue >= 330.0 && hue < 360.0);

      // Blue: roughly 125°–240° (also tweak based on your field lighting)
      bool is_blue =
        (hue >= 125.0 && hue <= 240.0);

      if (is_blue) {
        out_power = 127;     // forward on red
        top_power = 0;

      } else if (is_red) {
        out_power = -80;     // reverse on blue
      } else {
        out_power = 0;     // stop on other colors
      }
    }
}

void outtake_opcontrol() {
    if (master.get_digital(DIGITAL_L1)) {
      out_power = 127;
      scoreTop.move(127);

    } 
    else if (master.get_digital(DIGITAL_L2)) {
      out_power = -127;
      scoreTop.move(127);
    } 
    else {
      scoreTop.move(0);
      color_sorter();
    }
}

void piston_control() {
    if (master.get_digital(DIGITAL_Y)) {
  doinker.set(true);
} 
else if (master.get_digital(DIGITAL_X)) {
  doinker.set(false);
} 
}
