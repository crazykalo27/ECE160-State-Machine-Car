
void lineFollowing() {

  float tempLight = readLight();
  Serial1.print("----------------------");
  Serial1.print(tempLight);
  Serial1.print("----------------------");

  if (g_intialLight - tempLight > 3) {
    g_tunneled = true;
  }

  Serial1.println(g_tunneled);

  //Read and print line following sensor value
  readLineSensor(g_sensorVal);
  readCalLineSensor(g_sensorVal,
                    g_sensorCalVal,
                    g_sensorMinVal,
                    g_sensorMaxVal,
                    g_lineColor);

  for (int i = 0; i < 8; i++) {
    Serial1.print(g_sensorCalVal[i]);
    Serial1.print(", ");
  }
  Serial1.println();

  g_linePos = getLinePosition(g_sensorCalVal, g_lineColor);
  Serial1.print("linePos=");
  Serial1.println(g_linePos);

  //TUNNEL CHECK AND STOP
  if (g_sensorCalVal[6] > 100 && g_sensorCalVal[7] > 100 && g_tunneled == true && g_lastTurn == true) {
    //Detect final zone
    Serial1.println("Aligning and Dropping Rosie");
    autoStop();
  }

  //  //LEFT
  //  else if (g_sensorCalVal[0] > 100 && g_sensorCalVal[1] > 100 && g_firstRosie < 2) {
  //    //Detect a LEFT sharp turn
  //    Serial1.println("Left Sharp Turn");
  //
  //    //Drive forward a little bit
  //    resetRightEncoderCnt();
  //    while (getEncoderRightCnt() < 30) {
  //      driveRobot(-g_autoRobotSpeed, 0.0);
  //    }
  //
  //    //Turn right for 90 degree
  //    resetRightEncoderCnt();
  //    while (getEncoderRightCnt() < 150) { //Around 90 degree
  //      driveRobot(0, -30);
  //    }
  //
  //    //Move Forward to catch the middle line
  //    driveRobot(-70, 0);
  //    delayMicroseconds(1000 * 1000 / g_autoRobotSpeed);
  //
  //    g_firstRosie += 1;
  //    g_tunneled = false;
  //    g_lastTurn = false;
  //  }

  // Sensor #6 and #7 both detect line
  // indicates there's a right turn
  // laser read >10 indicates it's
  // a T-cross and do not turn
  else if (g_sensorCalVal[6] > 100 && g_sensorCalVal[7] > 100 && findDistance() < 10) {

    if (g_tunneled == true) {
      g_lastTurn = true;
    }

    //Detect a right sharp turn
    Serial1.println("Right Sharp Turn");

    //Drive forward a little bit
    resetRightEncoderCnt();
    while (getEncoderRightCnt() < 30) {
      driveRobot(-g_autoRobotSpeed, 0.0);
    }

    //Turn right for 90 degree
    resetRightEncoderCnt();
    while (getEncoderRightCnt() < 150) { //Around 90 degree
      driveRobot(0, 30);
    }

    //Move Forward to catch the middle line
    driveRobot(-30, 0);
    delayMicroseconds(1000 * 1000 / g_autoRobotSpeed);
  }

  //  else if(g_firstRosie == 2) {
  //    while(findDistance() > 15.0) {
  //      Staright();
  //    }
  //    g_robotState = MANUAL_STATE;
  //  }

  else { //Staright Line following
    Staright();
  }
}

void Staright() {
  if (g_linePos > 0 && g_linePos < 3000) {
        setMotorSpeed(LEFT_MOTOR, g_autoRobotSpeed);
        setMotorSpeed(RIGHT_MOTOR, g_autoRobotSpeed * 1.5);
//    setMotorSpeed(LEFT_MOTOR, (g_autoRobotSpeed * g_linePos / 5000));
//    setMotorSpeed(RIGHT_MOTOR, (g_autoRobotSpeed);
  } else if (g_linePos > 3400) {
    setMotorSpeed(LEFT_MOTOR, g_autoRobotSpeed * 1.5);
    setMotorSpeed(RIGHT_MOTOR, g_autoRobotSpeed);
//    setMotorSpeed(RIGHT_MOTOR, (g_autoRobotSpeed);
//    setMotorSpeed(LEFT_MOTOR, (g_autoRobotSpeed * g_linePos / 5000));
  } else {
    setMotorSpeed(LEFT_MOTOR, g_autoRobotSpeed );
    setMotorSpeed(RIGHT_MOTOR, g_autoRobotSpeed );
  }
}
