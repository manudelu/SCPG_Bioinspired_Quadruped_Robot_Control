// Copyright 1996-2020 Cyberbotics Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/***************************************************************************

  bioloid -- controller of the bioloid quadruped robot
  Copyright (C) 2007 Biological Inspired Robotic Group (BIRG), EPFL
  Authors: Jean-Christophe Fillion-Robin
  Email: jean-christophe@fillion-robin.org

***************************************************************************/

#include "Robot.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <webots/robot.h>

static Robot *robot = NULL;

int main() 
{
  srand(time(NULL));
  wb_robot_init();
  const char *robotName = wb_robot_get_name();
  robot = new Robot(robotName);
  
  //
  
  float decayFactor = 1.1; // alpha
  int Vth = 1; // Threshold membrane potential (normalized)
 
  
  
  
  
  //
  
  
  
  
  robot->standing();
  
  // index 0 for trot, 1 for walk
  robot -> walking(1, 0.5, -1, 100); //(1,0.5,-1,100)
  
  
  delete robot;

  return 0;
}