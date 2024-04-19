/****************************
   Function Name: autoStop
   Description: stops robot at distance from wall using laser
 ****************************/

#define cm2in 2.54

void autoStop() {
  int leftLaserPin = 9.1; //DISTL
  int rightLaserPin = 9.0; //DISTR

  GP2Y0A21_Sensor leftlaser;
  GP2Y0A21_Sensor rightlaser;

  float distMeas;
  float error;
  float motorSpeed;
  float stopDistance = 7; //distance in inches from wall
  int oldtime = 0;

  leftlaser.begin(leftLaserPin, INPUT_PULLUP);
  rightlaser.begin(rightLaserPin, INPUT_PULLUP);


  while ((error > 1.5) || (error < -1.5)) {

    distMeas = findDistance(); // returns calculated distance from measurement
    error = (distMeas - stopDistance); // how close are we?
    motorSpeed = abs(error) * 7; // amplify the error. The number 5 is the P controller constant
    motorSpeed = constrain(motorSpeed, 0, 50); //Motor speed can't be greater than 100 or less than zero

    if (error > 1.5) {     //if greater than one inch away from stop distance, move towards wall (backward if sensor on claw end)
      enableMotor(2);
      setMotorDirection(2, 1);
      setMotorSpeed(2, (int)motorSpeed);    // turn on the motor proportionately
    }

    else if (error < -1.5) {
      enableMotor(2);      //move away from wall if error is more negative than -1.0 inches (forward if sensor on claw end)
      setMotorDirection(2, 0);
      setMotorSpeed(2, (int)motorSpeed);    // turn on the motor proportionately
    }

    delayMicroseconds(100*100); // add some delay to the loop to give motors time to change speed.

  }
  //Do a 180
  resetRightEncoderCnt();
  while (getEncoderRightCnt() < 380) { //Around 180 degree
    driveRobot(0, 40);
  }

  driveRobot(0, 0);     //disables motors to save battery if within 1 inch of stopping point
  delayMicroseconds(100 * 1000);

  g_tunneled = false;
  g_lastTurn = false;
  g_gripAng = 0;
  gripper.write(g_gripAng);
  g_robotState = AUTO_STATE;

  Serial1.print(distMeas); Serial1.print(" "); Serial1.println(motorSpeed);
}
