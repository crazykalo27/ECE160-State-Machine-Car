/****************************
   Function Name: driveRobot
   Description: Translate moving commands
                to drive motor
   Input: (int) translational: translational speed, -128 to 128,
                               positive to move forward,
                               negative to move backard.
          (int) rotational: rotational speed, -128 to 128,
                            positive to rotate CCW,
                            negative to rotate CW
 ****************************/

void driveRobot (float translational, float rotational) {

  enableMotor(BOTH_MOTORS);
  
  //mapped motor speed
  float motorLSpeed;
  float motorRSpeed;

  //Unmapped motor speed
  float RAWmotorLSpeed;
  float RAWmotorRSpeed;

  RAWmotorLSpeed = -(translational - rotational);
  RAWmotorRSpeed = -(translational + rotational);

  // Using differential control to drive the robot
  // The range of inputs are -128 to 128
  // Therefore the calculated motor speed range from -255 to 255
  // Remap them to -100 to 100 to drive motor
  motorLSpeed = map(RAWmotorLSpeed, -128, 128, -100, 100);
  motorRSpeed = map(RAWmotorRSpeed, -128, 128, -100, 100);

  //Set the speed of motor as absolute value of calculated speed
  setMotorSpeed(LEFT_MOTOR,(int) abs(motorLSpeed));
  setMotorSpeed(RIGHT_MOTOR, (int) abs(motorRSpeed));
/*
  Serial1.print(RAWmotorLSpeed);
  Serial1.print(" ");
  Serial1.print(RAWmotorRSpeed);
  Serial1.print(", ");

  Serial1.print(motorLSpeed);
  Serial1.print(" | ");
  Serial1.print(motorRSpeed);
  Serial1.println();
  */

  //If value of speed is positive drive motor forward
  //If value of speed is negative drive motor backward
  (motorLSpeed > 0) ? 
  setMotorDirection(LEFT_MOTOR, MOTOR_DIR_FORWARD) 
  : setMotorDirection(LEFT_MOTOR, MOTOR_DIR_BACKWARD);
  
  (motorRSpeed > 0) ? 
  setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_FORWARD) 
  : setMotorDirection(RIGHT_MOTOR, MOTOR_DIR_BACKWARD);
}
