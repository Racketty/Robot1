#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// inline pros::Motor intake(1);

inline pros::Motor top(-20);  
inline pros::Motor bottom(10); 
inline pros::Motor outtake(19); 
inline pros::Motor scoreTop(18);

// void set_intake(int input);
// void set_top(int input);
// void set_bottom(int input);

// void intake_opcontrol();

// void set_outtake(int input);
// void outtake_opcontrol();

// void set_scoreTop(int input);

// void intake_toggle_update();
// void intake_apply();

// inline pros::adi::DigitalIn limit_switch('A');

