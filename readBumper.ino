void readBumper(){
  Serial1.print(" | ");
  for (int i=0; i<6; i++){
    isBumpSwitchPressed(i) ?
    Serial1.print("Pressed")
    : Serial1.print("Unpressed");

    Serial1.print(" | ");
  }
  Serial1.println();
}
