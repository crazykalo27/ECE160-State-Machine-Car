
void manualState() {
  // Printing the joystick values to the serial monitor
  Serial1.print("L: ("); // Left stick values
  Serial1.print(ps2x.Analog(PSS_LX), DEC);
  Serial1.print(",");
  Serial1.print(ps2x.Analog(PSS_LY), DEC);
  Serial1.print(") || ");
  Serial1.print("R: ("); // Right stick values
  Serial1.print(ps2x.Analog(PSS_RX), DEC);
  Serial1.print(",");
  Serial1.print(ps2x.Analog(PSS_RY), DEC);
  Serial1.println(")");

  enableMotor(BOTH_MOTORS);
  driveRobot(
    g_translationSpeedScale * (ps2x.Analog(PSS_RY) - 128),
    g_rotationSpeedScale * (ps2x.Analog(PSS_LX) - 128));

  //move gripper
  if  ((ps2x.Button(PSB_R1)) && (g_gripAng <= 180) ) {
    g_gripAng += g_increment;
  } else if ((ps2x.Button(PSB_L1)) && (g_gripAng >= 10)) {
    g_gripAng -= g_increment;
  }
  gripper.write(g_gripAng);

  Serial1.print("Gripper: ");
  Serial1.println(g_gripAng);


  readBumper();

  if (ps2x.Button(PSB_R2)) { //Weapon
    IRsignal(0);
  } else if (ps2x.Button(PSB_L2)) { //Health Pack
    IRsignal(1);
  } else if (ps2x.Button(PSB_PAD_UP)) { //shoots monster
    IRsignal(2);
  }

  if (ps2x.ButtonPressed(PSB_TRIANGLE)) {
    g_robotState = AUTO_STATE;
  } else {
    g_robotState = MANUAL_STATE;
  }
}
