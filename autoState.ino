
void autoState() {

  setMotorDirection(BOTH_MOTORS, MOTOR_DIR_FORWARD);

  if (ps2x.ButtonPressed(PSB_SQUARE)) {
    g_robotState = MANUAL_STATE;
  } else {
    g_robotState = AUTO_STATE;
  }

  if (g_won == 0) {
    win();
  }

  lineFollowing();
}
