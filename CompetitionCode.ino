
//Include necessary headers and libraries
#include "robotLibs.h"
int g_printtime = 0;
int g_lighttime = 0;

void setup() {
  initializeAll();
}

void loop() {
  //Read values of gamepad
  ps2x.read_gamepad(false, g_gamepad_vibrate);

  if ((millis() - g_printtime) > 500) {
    Serial1.print(ps2x.Button(PSB_TRIANGLE));
    Serial1.print(ps2x.Button(PSB_SQUARE));
    Serial1.println(ps2x.Button(PSB_CROSS));
    g_printtime = millis();
  }

  switch (g_robotState) {
    case AUTO_STATE:
      if ((millis() - g_oldtime) > 1500) {
        Serial1.println("AUTO_STATE");
        g_oldtime = millis();
      }
      autoState();
      break;
    case MANUAL_STATE:
      if ((millis() - g_oldtime) > 1500) {
        Serial1.println("MANUAL_STATE");
        g_oldtime = millis();
      }
      manualState();
      break;
    case INITIAL_STATE:
      if ((millis() - g_oldtime) > 1500) {
        Serial1.println("INITIAL_STATE");
        g_oldtime = millis();
      }
      initialState();
      break;
    default: Serial1.println("Unknown State");
  }

  tunnelLight();
}

void tunnelLight() {
  if (g_initialLight - readLight() > 3) {
    if ((millis() - g_lighttime) > 500) {
      if (g_lit == false) {
        digitalWrite(TUNNEL_LIGHT_PIN_2, LOW);
        digitalWrite(TUNNEL_LIGHT_PIN, HIGH);
        g_lit = true;
      } else if (g_lit = true) {
        digitalWrite(TUNNEL_LIGHT_PIN, LOW);
        digitalWrite(TUNNEL_LIGHT_PIN_2, HIGH);
        g_lit = false;
      }
      g_lighttime = millis();
    }

  }
  else {
    digitalWrite(TUNNEL_LIGHT_PIN, LOW);
    digitalWrite(TUNNEL_LIGHT_PIN_2, LOW);

  }
}
