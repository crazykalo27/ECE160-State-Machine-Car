// Robot Library

#include <RSLK_Pins.h>
#include <math.h>
#include <SimpleRSLK.h>

//INFRARED REMOTE
#include <TinyIRremote.h>
IRsend sendIR;
IRData IRmsg;
#define IR_TRX_PIN 17 // pin to transmitter IR LED
#define IR_RCV_PIN 15 //pin to reciver IR LED


//PS2 CONTROLLER
#include "PS2X_lib.h"

#define PS2_DAT         32 //P1.7 <-> brown wire 15, 14,19,18
#define PS2_CMD         19 //P1.6 <-> orange wire
#define PS2_SEL         18 //P2.3 <-> yellow wire (also called attention)
#define PS2_CLK         14 //P6.7 <-> blue wire
#define PS2X_DEBUG
#define PS2X_COM_DEBUG

//#define pressures   true
#define pressures   false
//#define rumble      true
#define rumble      false
PS2X ps2x; // create PS2 Controller Class
int g_gamepad_error = 1;
byte g_gamepad_type = 0;
byte g_gamepad_vibrate = 0;


#define INITIAL_STATE 0
#define MANUAL_STATE 10
#define AUTO_STATE 20

int g_robotState;
int g_oldtime = 0;


//MOTORS 
float g_translationSpeedScale = 0.7;
float g_rotationSpeedScale = 0.3;


//SERVO 
#include <Servo.h>
Servo gripper; // Create object for servo gripper
int g_gripAng = 20; //The initial and changing angle of gripper servo
int g_increment = 10;


//LINE FOLLOWING - AUTONOMOUS
int g_photoresistorPin = 44;
#define TUNNEL_LIGHT_PIN 66
#define TUNNEL_LIGHT_PIN_2 50

bool g_lit = false; 

int g_initialLight;
bool g_tunneled = false;
bool g_lastTurn = false;

uint16_t g_sensorVal[LS_NUM_SENSORS];
uint16_t g_sensorCalVal[LS_NUM_SENSORS];
uint16_t g_sensorMaxVal[LS_NUM_SENSORS];
uint16_t g_sensorMinVal[LS_NUM_SENSORS];

uint32_t g_linePos;

float g_autoRobotSpeed = 20; //Robot Speed in auto mode

/* Valid values are either:
 *  DARK_LINE  if your floor is lighter than your line
 *  LIGHT_LINE if your floor is darker than your line
 */
uint8_t g_lineColor = LIGHT_LINE;


int g_won = 0;
int g_firstRosie = 0;
