
void initialState() {
  if (ps2x.ButtonPressed(PSB_SQUARE)) {
    g_robotState = MANUAL_STATE;
  } else if (ps2x.ButtonPressed(PSB_CIRCLE)) {
    simpleCalibrate();
  }
  else {
    g_robotState = INITIAL_STATE;
  }
}

void simpleCalibrate() {
  clearMinMax(g_sensorMinVal, g_sensorMaxVal);

  /* Set both motors direction forward */
  setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);
  /* Enable both motors */
  enableMotor(BOTH_MOTORS);
  /* Set both motors speed 20 */
  setMotorSpeed(BOTH_MOTORS, 20);

  for (int x = 0; x < 100; x++) {
    readLineSensor(g_sensorVal);
    setSensorMinMax(g_sensorVal, g_sensorMinVal, g_sensorMaxVal);
    Serial1.println("Reading and Calibrating");
  }

  setMotorSpeed(BOTH_MOTORS, 0);
  g_initialLight = readLight();
  g_tunneled = false;
}
