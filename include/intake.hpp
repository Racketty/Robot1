#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

inline pros::MotorGroup intake({10, -20});  
inline pros::Motor outtake(19); 
inline pros::Motor scoreTop(18);
void set_intake(int input);
void intake_opcontrol();

void set_outtake(int input);
void outtake_opcontrol();

void set_scoreTop(int input);