
void IRsignal(int command) {

  IRmsg.protocol = NEC; //use this protocol
  IRmsg.address = 160; //Tx address (can be in decimal)
  IRmsg.isRepeat = false; //Sends REPEAT instead of original command (don’t use)

  switch (command) {
    case 0: //Weapon reciever 222
      IRmsg.command = 143; //Tx command (can be in decimal)
      sendIR.write(&IRmsg);
      break;
    case 1:  //Health Pack
      IRmsg.command = 123; //Tx command (can be in decimal)
      sendIR.write(&IRmsg);
      break;
    case 2:
      IRmsg.command = 69; //Tx command (can be in decimal)
      //sendIR.write(HIGH);
      digitalWrite(IR_TRX_PIN, HIGH);
      delayMicroseconds(500*1000);
      digitalWrite(IR_TRX_PIN, LOW);
      break;
    default:
      break;
  }

  if (decodeIR(&IRmsg))
  {
    Serial1.print(IRmsg.address, DEC); //prints out address of remote
    Serial1.print(" || Command Dec: ");
    Serial1.print(IRmsg.command, DEC); //prints out HEX command from remote
  }

  delay(20);
}
