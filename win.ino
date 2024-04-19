void win() {

  //go forward a little
  resetRightEncoderCnt();
  while (getEncoderRightCnt() < 800) {
    lineFollowing();
  }

  //Turn right for 90 degree
  resetRightEncoderCnt();
  while (getEncoderRightCnt() < 70) { //Around 90 degree
    driveRobot(0, 30);
  }
  driveRobot(0, 0);

  for (int turns = 0; turns < 10; turns += 1) {
    Serial1.println(turns);
    IRsignal(0);
    IRsignal(1);
    resetRightEncoderCnt();
    while (getEncoderRightCnt() < 10) { //slight right turn
      driveRobot(0, 30);
    }
    driveRobot(0, 0);
  }

  //  resetRightEncoderCnt();
  //  while (getEncoderRightCnt() < 135) { //right turn
  //    driveRobot(0, 30);
  //  }

  g_won = 1;
}
