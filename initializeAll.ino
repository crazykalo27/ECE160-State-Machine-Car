
void initializeAll() {
  setupRSLK();
  g_robotState = INITIAL_STATE;
  //Initialize bluetooth serial
  Serial1.begin(57600);
  delayMicroseconds(2000 * 1000);
  Serial1.println("SYSTEM STARTED");

  sendIR.begin(IR_TRX_PIN, true, GREEN_LED);
  //initTinyIRReceiver();

  delayMicroseconds(6000*1000);
  Serial1.print("out of time");

  initPS2X();

  gripper.attach(SRV_0);
}

void initPS2X () {

  delayMicroseconds(500 * 1000); //added delay to give wireless ps2 module some time to startup, before configuring it

  g_gamepad_error = 1;
  while (g_gamepad_error) {
    g_gamepad_error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
    Serial1.println(g_gamepad_error);
    delayMicroseconds(500 * 1000);


    if (g_gamepad_error == 0) {
      Serial1.print("Found Controller, configured successful ");
      Serial1.print("pressures = ");
      if (pressures)
        Serial1.println("true ");
      else
        Serial1.println("false");
      Serial1.print("rumble = ");
      if (rumble)
        Serial1.println("true)");
      else
        Serial1.println("false");
      Serial1.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
      Serial1.println("holding L1 or R1 will print out the analog stick values.");
      Serial1.println("Note: Go to www.billporter.info for updates and to report bugs.");
    }  else if (g_gamepad_error == 1)
      Serial1.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");

    else if (g_gamepad_error == 2)
      Serial1.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

    else if (g_gamepad_error == 3)
      Serial1.println("Controller refusing to enter Pressures mode, may not support it. ");
    delayMicroseconds(1000 * 1000);
  }
  //  Serial1.print(ps2x.Analog(1), HEX);

  g_gamepad_type = ps2x.readType();
  switch (g_gamepad_type) {
    case 0:
      Serial1.print("Unknown Controller type found ");
      break;
    case 1:
      Serial1.print("DualShock Controller found ");
      break;
    case 2:
      Serial1.print("GuitarHero Controller found ");
      break;
    case 3:
      Serial1.print("Wireless Sony DualShock Controller found ");
      break;
  }
}
