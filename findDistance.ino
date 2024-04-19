/*
   Function Name: findDistance
   Description: Reads laser sensors and returns a distance from the wall in inches

   Ways to improve: needs to be able to read from 2 at once but one of 
   our lasers is broken
 */

float findDistance() {
  float distanceMeas;
  /*
   * num of the distance sensor to read. Valid values are 0 - 2. 
   * Representing the 3 RSLK's sensors that can be mounted on the RSLK (on top of the bump switch assembly).
      0 for the sensor to left if gripper facing you (NOT WORKING RIGHT NOW)
      1 for pin 6.1
      2 for the sensor to right if gripper facing you
   */
  int measurement = readSharpDist(1);
  if (measurement < 45) {
    return 200.0; // Need to avoid anything close to a divide by zero problem.
  }
  distanceMeas = (6731 / (measurement - 40)) + 2; // Equation comes from 2Y0A21 Datasheet
  return distanceMeas / cm2in; //returns distance in inches
}
