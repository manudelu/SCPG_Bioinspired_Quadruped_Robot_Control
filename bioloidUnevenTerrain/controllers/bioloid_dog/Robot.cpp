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

#include "Robot.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include <webots/robot.h>
#include <webots/touch_sensor.h>
#include <stdlib.h>


double status[16] = {-0.0215367628635059,-12.3706153890073,0.0215367628635059,-14.1293846109927,-0.0215367628635059,-12.3706153890073,0.0215367628635059,-14.1293846109927,-0.0215367628635059,-12.3706153890073,0.0215367628635059,-14.1293846109927,-0.0215367628635059,-12.3706153890073,0.0215367628635059,-14.1293846109927};

/*
 * List of motors
 */
const char *Robot::MOTOR_NAMES[MAX_MOTORS + 1] = {"pelvis",
                                                  "front_left_1",
                                                  "front_right_1",
                                                  "front_left_2",
                                                  "front_right_2",
                                                  "front_left_3",
                                                  "front_right_3",
                                                  "back_left_1",
                                                  "back_right_1",
                                                  "back_left_2",
                                                  "back_right_2",
                                                  "back_left_3",
                                                  "back_right_3",
                                                  "neck_1",
                                                  "neck_2",
                                                  "head",
                                                  NULL};

/*
const double Robot::coupling_matrix[2][4][4] = {
  {
    //trot matrix
    {0, -0.01, 0.01, -0.01},
    {-0.01, 0, -0.01, 0.01},
    {0.01, -0.01, 0, -0.01},
    {-0.01, 0.01, -0.01, 0},
  },
  {
    //walk matrix
    {0, -0.01, -0.01, 0.01},
    {-0.01, 0, 0.01, -0.01},
    {0.01, -0.01, 0, -0.01},
    {-0.01, 0.01, -0.01, 0}
  }
};
*/

const int Robot::gait_setup[4][2] = {{FRONT_LEFT_1, FRONT_LEFT_3},
                                     {FRONT_RIGHT_1, FRONT_RIGHT_3},
                                     {BACK_RIGHT_1, BACK_RIGHT_3},
                                     {BACK_LEFT_1, BACK_LEFT_3}};

Robot::Robot(const char *name) : _name(name), _controlStep(SIMULATION_STEP_DURATION), _stepCount(0){
  int i = 0;
  for (i = 0; Robot::MOTOR_NAMES[i]; i++) {
    motors[i] = wb_robot_get_device(MOTOR_NAMES[i]);
    assert(motors[i]);
    position_sensor[i] = wb_motor_get_position_sensor(motors[i]);
    assert(position_sensor[i]);
    wb_position_sensor_enable(position_sensor[i], (int)_controlStep);
  }
     touch_sensor_FRONT_LEFT = wb_robot_get_device("touch_sensor_FRONT_LEFT");
     wb_touch_sensor_enable(touch_sensor_FRONT_LEFT, SIMULATION_STEP_DURATION);
     
     touch_sensor_FRONT_RIGHT = wb_robot_get_device("touch_sensor_FRONT_RIGHT");
     wb_touch_sensor_enable(touch_sensor_FRONT_RIGHT, SIMULATION_STEP_DURATION);
     
     touch_sensor_BACK_LEFT = wb_robot_get_device("touch_sensor_BACK_LEFT");
     wb_touch_sensor_enable(touch_sensor_BACK_LEFT, SIMULATION_STEP_DURATION);
     
     touch_sensor_BACK_RIGHT = wb_robot_get_device("touch_sensor_BACK_RIGHT");
     wb_touch_sensor_enable(touch_sensor_BACK_RIGHT, SIMULATION_STEP_DURATION);
}

/*
 * Set motor position
 */
void Robot::setMotorPosition(int motorId, double value) {
  wb_motor_set_position(motors[motorId], value);
}

/*
 * Get motor position
 */
double Robot::getMotorPosition(int motorId) {
  return wb_position_sensor_get_value(position_sensor[motorId]);
}

/*
 * Enable the 'motor_get_position' function for the provided motor
 */
void Robot::enableMotorPosition(int motorId) {
  wb_position_sensor_enable(position_sensor[motorId], (int)_controlStep);
}

/*
 * Run simulation for X seconds
 */
void Robot::wait(double x) {
  // number of iteration
  double num = x / (_controlStep/500);
  for (int i = 0; i < num; i++)
    wb_robot_step((int)_controlStep);
}

/*
 * Set the robot into walking position
 */  
void Robot::standing() {
  setMotorPosition(NECK_1, -M_PI/ 2);
  setMotorPosition(FRONT_LEFT_2, M_PI / 2);
  setMotorPosition(FRONT_RIGHT_2, -M_PI / 2);
  setMotorPosition(BACK_LEFT_2, M_PI/ 2);
  setMotorPosition(BACK_RIGHT_2, -M_PI/ 2);

  wait(1);
}

void Robot::walking(int gait_type, double DC, double ztd, double time) {
 
  int counter = 0; 
  
  while (wb_robot_step(SIMULATION_STEP_DURATION) != -1)
 { 
  while(counter < (time*1000/16))
  {
    double motorPositions[2] = {0, 0};

      computeTrajectory(status, gait_type, DC, ztd, _controlStep/1000, counter);

      // compute motors position for each legs
      for (int legId = 0; legId < 4; legId++) {
        computeAnglePosition(motorPositions, status[2*legId], status[2*legId + 1]); //computeAnglePosition(motorPositions, status[8+2*legId], status[8+2*legId + 1]);
        setMotorPosition(gait_setup[legId][0], motorPositions[0]);
        setMotorPosition(gait_setup[legId][1], motorPositions[1]);
      }
         
    // simulator step
    wb_robot_step((unsigned int)_controlStep);
    
    //_stepCount++;
    counter++;
  }
   // getTouchSensorValue();
}
}

void Robot::getTouchSensorValue() {
 
  FILE *fd;
  fd=fopen("scrivi.txt", "a");
  if( fd==NULL ) {
    perror("Errore in apertura del file");
    exit(1);
  }
  int front_left_force = wb_touch_sensor_get_value(touch_sensor_FRONT_LEFT);		/* scrive il numero */
  int front_right_force = wb_touch_sensor_get_value(touch_sensor_FRONT_RIGHT);	
  int back_left_force = wb_touch_sensor_get_value(touch_sensor_BACK_LEFT);	
  int back_right_force = wb_touch_sensor_get_value(touch_sensor_BACK_RIGHT); 
  
  
  fprintf(fd, "Touch Sensors \n: front left force is %d\t front right force is %d\t back left force is %d\t back right force is %d\n ", front_left_force, front_right_force, back_left_force, back_right_force);
  
  
	/* chiude il file */
  fclose(fd);
}
  		/* scrive il numero */

/*
 * Compute the position of the three motors according to the time by using the Inverse Kinematics Equations
 * in order to find A2 and A1
 */
void Robot::computeAnglePosition(double *motorsPosition, double x, double y) {
  
  // compute angle A2
  double A2 = acos((x * x + y * y - L1 * L1 - L2 * L2) / (2 * L1 * L2));

  // compute angle A1
  double A1 = acos(((L1 + L2 * cos(A2)) * (-x) - (-L2 * sin(A2)) * y) / (pow(L1 + L2 * cos(A2), 2) + pow(-L2 * sin(A2), 2)));

  // subtract 2PI
  A1 = M_PI / 2 - A1;

  motorsPosition[0] = A1;
  motorsPosition[1] = A2;
  
  // printf("Angle A1 = %f\n",A1);
  // printf("Angle A2 = %f\n",A2);
  // printf("Angle x = %f\n",x);
  // printf("Angle y = %f\n",y);
}

/*
 * Compute x and y values
 */
void Robot::computeTrajectory(double *status, int mat_ind, double D,float ztd, double dt, int counter) {
  float a = 1;
  float b = 500;
  float c = 0.5;
  
  float L = 17.100; //L = 8.55
  float H = 0.8706; //H =0.875
  
  
  //float D = 0.5;  //duty cylce
  float Vx = 1; 
  float Vz = 0;
  float Vf = 0;
   //componenti x e z di Vf: la componente z è nulla perchè Vf è la velocità di avanzamento
  float bf = 50;  //influenza la smoothness del taglio
  float K = 200;  //deve essere impostato ad almeno 10*Vf (l'ho messo a 200 dato che per il trotto usiamo Vf=20)
  
  if(mat_ind == 0)
  {
  
    Vf = 50;  //Componente x della Velocità di avanzamento
  }
  else if(mat_ind == 1)
  {
  
    Vf = 32*2; //Avendo cambiato il SIMULATION_STEP_DURATION da 16 a 10, che regola il passo di integrazione, devo modificare anche la velocità per mantenerla uguale a prima
  }
  
  // Componenti x e z di Vf
  float V[2] = {Vx*Vf , Vz*Vf}; 
  
     
  int front_left_force = wb_touch_sensor_get_value(touch_sensor_FRONT_LEFT);		/* scrive il numero */
  int front_right_force = wb_touch_sensor_get_value(touch_sensor_FRONT_RIGHT);	
  int back_left_force = wb_touch_sensor_get_value(touch_sensor_BACK_LEFT);	
  int back_right_force = wb_touch_sensor_get_value(touch_sensor_BACK_RIGHT); 
 
  
  float ztd1 = -1*H;  //coordinata z del taglio rispetto all'asse orizzontale dell'ellisse
  float ztd2 = -1*H;   //coordinata z del taglio rispetto all'asse orizzontale dell'ellisse
  float ztd3 = -1*H;    //coordinata z del taglio rispetto all'asse orizzontale dell'ellisse
  float ztd4 = -1*H;   //coordinata z del taglio rispetto all'asse orizzontale dell'ellisse

  
  float x0 = 0; //x0 = 3;  // coordinata x del centro
  //float x034 = 0;  
  float z012 = -13.25; // coordinata y del centro
  float z034 = -13.25;  //-12.75
  double dxdt[8];
  double dzdt[8];
  double A1[4]={getMotorPosition(gait_setup[0][0]),getMotorPosition(gait_setup[1][0]),getMotorPosition(gait_setup[2][0]),getMotorPosition(gait_setup[3][0])};
  double A2[4]={getMotorPosition(gait_setup[0][1]),getMotorPosition(gait_setup[1][1]),getMotorPosition(gait_setup[2][1]),getMotorPosition(gait_setup[3][1])};
  double z_real[4]={-L1*cos(-A1[0])-L2*cos(-A2[0]-A1[0]),-L1*cos(-A1[1])-L2*cos(-A2[1]-A1[1]),-L1*cos(-A1[2])-L2*cos(-A2[2]-A1[2]),-L1*cos(-A1[3])-L2*cos(-A2[3]-A1[3])};
  
  
if(counter > 100) {               
  if(front_left_force == 1){               //Se il sensore vale 1,quindi la zampa tocca il terreno/l'ostacolo, 
                                           //modifico il movimento della zampa,tagliando l'ellisse
      //ztd1 = (status[9]-0.1*H - z012); 
      ztd1 = (z_real[0] - z012); 
      
      if(ztd1 > 0) {
          ztd1 = 0;
      }
  }  
       
  else {                      //Quando la zampa non tocca più, la zampa torna a percorrere l'ellisse non filtrata
      ztd1 = -1*H;
  }
  
 
  if(front_right_force == 1){               
                                          
      //ztd2 = (status[11]-0.1*H - z012); 
      ztd2 = (z_real[1] - z012); 
      
      if(ztd2 > 0) {
          ztd2 = 0;
      }
  }  
       
  else {                      
      ztd2 = -1*H;
  }
  
  
  if(back_right_force == 1){              
                                          
      // ztd3 = (status[13]-0.1*H - z034);
      ztd3 = (z_real[2] - z034); 
      
      if(ztd3 > 0) {
          ztd3 = 0;
      }
  }  
       
  else {                      
      ztd3 = -1*H;
  }
  
  
  if(back_left_force == 1){              
                                          
      // ztd4 = (status[15]-0.1*H - z034);
      ztd4 = (z_real[3] - z034);
      
     if(ztd4 > 0) {
          ztd4 = 0;
      } 
  }  
       
  else {                      
      ztd4 = -1*H;
  }
 }
  
  
  /*
  status[16] represents all the 16 variables in order
  x1 status[0]
  z1 status[1]
  x2 status[2]
  z2 status[3]
  x3 status[4]
  z3 status[5]
  x4 status[6]
  z4 status[7]
  x1f status[8]
  z1f status[9]
  x2f status[10]
  z2f status[11]
  x3f status[12]
  z3f status[13]
  x4f status[14]
  z4f status[15]
  
  */
  
  double s11 = 1/(exp(-b*(status[1]-z012))+1);
  double s12 = 1/(exp(b*(status[1]-z012))+1);
  double w1 = (M_PI*Vf/L)*((D/(1-D)*s11+s12));
  
  double s21 = 1/(exp(-b*(status[3]-z012))+1);
  double s22 = 1/(exp(b*(status[3]-z012))+1);
  double w2 = (M_PI*Vf/L)*((D/(1-D)*s21+s22));
  
  double s31 = 1/(exp(-b*(status[5]-z034))+1);
  double s32 = 1/(exp(b*(status[5]-z034))+1);
  double w3 = (M_PI*Vf/L)*((D/(1-D)*s31+s32));
  
  double s41 = 1/(exp(-b*(status[7]-z034))+1);
  double s42 = 1/(exp(b*(status[7]-z034))+1);
  double w4 = (M_PI*Vf/L)*((D/(1-D)*s41+s42));
  
  double s1_f1 = 1/((exp(-bf*(status[1]-z012-ztd1))+1));
  double s1_f2 = 1/((exp(bf*(status[1]-z012-ztd1))+1));
  
  double s2_f1 = 1/((exp(-bf*(status[3]-z012-ztd2))+1));
  double s2_f2 = 1/((exp(bf*(status[3]-z012-ztd2))+1));
  
  double s3_f1 = 1/((exp(-bf*(status[5]-z034-ztd3))+1));
  double s3_f2 = 1/((exp(bf*(status[5]-z034-ztd3))+1));
  
  double s4_f1 = 1/((exp(-bf*(status[7]-z034-ztd4))+1));
  double s4_f2 = 1/((exp(bf*(status[7]-z034-ztd4))+1));
  
  dxdt[0] = a*(1-(4*pow((status[0]-x0),2)/(L*L))-pow((status[1]-z012),2)/(H*H))*(status[0]-x0)+(w1*L/(2*H))*(status[1]-z012);
  dzdt[0] = c*(1-(4*pow((status[0]-x0),2)/(L*L))-pow((status[1]-z012),2)/(H*H))*(status[1]-z012)-(w1*2*H/L)*(status[0]-x0);//+(coupling_matrix[mat_ind][0][0])*(status[1]-z012)+(coupling_matrix[mat_ind][0][1])*(status[3]-z012)+(coupling_matrix[mat_ind][0][2])*(status[5]-z034)+(coupling_matrix[mat_ind][0][3])*(status[7]-z034); 

  dxdt[1] = a*(1-(4*pow((status[2]-x0),2)/(L*L))-pow((status[3]-z012),2)/(H*H))*(status[2]-x0)+(w2*L/(2*H))*(status[3]-z012);
  dzdt[1] = c*(1-(4*pow((status[2]-x0),2)/(L*L))-pow((status[3]-z012),2)/(H*H))*(status[3]-z012)-(w2*2*H/L)*(status[2]-x0);//+(coupling_matrix[mat_ind][1][0])*(status[1]-z012)+(coupling_matrix[mat_ind][1][1])*(status[3]-z012)+(coupling_matrix[mat_ind][1][2])*(status[5]-z034)+(coupling_matrix[mat_ind][1][3])*(status[7]-z034);
  
  dxdt[2] = a*(1-(4*pow((status[4]-x0),2)/(L*L))-pow((status[5]-z034),2)/(H*H))*(status[4]-x0)+(w3*L/(2*H))*(status[5]-z034);
  dzdt[2] = c*(1-(4*pow((status[4]-x0),2)/(L*L))-pow((status[5]-z034),2)/(H*H))*(status[5]-z034)-(w3*2*H/L)*(status[4]-x0);//+(coupling_matrix[mat_ind][2][0])*(status[1]-z012)+(coupling_matrix[mat_ind][2][1])*(status[3]-z012)+(coupling_matrix[mat_ind][2][2])*(status[5]-z034)+(coupling_matrix[mat_ind][2][3])*(status[7]-z034);

  dxdt[3] = a*(1-(4*pow((status[6]-x0),2)/(L*L))-pow((status[7]-z034),2)/(H*H))*(status[6]-x0)+(w4*L/(2*H))*(status[7]-z034);
  dzdt[3] = c*(1-(4*pow((status[6]-x0),2)/(L*L))-pow((status[7]-z034),2)/(H*H))*(status[7]-z034)-(w4*2*H/L)*(status[6]-x0);//+(coupling_matrix[mat_ind][3][0])*(status[1]-z012)+(coupling_matrix[mat_ind][3][1])*(status[3]-z012)+(coupling_matrix[mat_ind][3][2])*(status[5]-z034)+(coupling_matrix[mat_ind][3][3])*(status[7]-z034);

  dxdt[4] = (dxdt[0] + K*(status[0]-status[8]))*s1_f1 - V[0]*s1_f2;
  dzdt[4] = (dzdt[0] + K*(status[1]-status[9]))*s1_f1 - V[1]*s1_f2;

  dxdt[5] = (dxdt[1] + K*(status[2]-status[10]))*s2_f1 - V[0]*s2_f2;
  dzdt[5] = (dzdt[1] + K*(status[3]-status[11]))*s2_f1 - V[1]*s2_f2;

  dxdt[6] = (dxdt[2] + K*(status[4]-status[12]))*s3_f1 - V[0]*s3_f2;
  dzdt[6] = (dzdt[2] + K*(status[5]-status[13]))*s3_f1 - V[1]*s3_f2;

  dxdt[7] = (dxdt[3] + K*(status[6]-status[14]))*s4_f1 - V[0]*s4_f2;
  dzdt[7] = (dzdt[3] + K*(status[7]-status[15]))*s4_f1 - V[1]*s4_f2;
  
  
  //Metodo di Eulero esplicito
  for(int i = 0; i < 8; i++)
  {
    status[2*i] = status[2*i] + dt * dxdt[i];
    
    // FILE *f1 = fopen("status.txt", "a");
    // if (f1 == NULL)
    // {
        // printf("Error opening file!\n");
        // exit(1);
    // }
    // fprintf(f1,"%f\n",status[2*i]);
    
    status[2*i + 1] = status[2*i + 1] + dt * dzdt[i];
    
    // fprintf(f1,"%f\n",status[2*i+1]);
    // fclose(f1);
  }
  // printf("z1 = %f\n",z_real[0]);
  // printf("stat1 = %f\n",status[9]);
  // printf("z2 = %f\n",z_real[1]);
  // printf("stat2 = %f\n",status[11]);
  // printf("z3 = %f\n",z_real[2]);
  // printf("stat3 = %f\n",status[13]);
  // printf("z4 = %f\n",z_real[3]);
  // printf("stat4 = %f\n",status[15]);
}


