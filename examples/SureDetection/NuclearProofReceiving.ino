#include <RCSwitch.h>

#define PIN 4

RCSwitch mySwitch = RCSwitch();

#define RFRepeatTimeMs 350
long RFLastValue = 0;
long RFLastTime = 0;

void setup() {
  Serial.begin(115200);

  mySwitch.enableReceive(digitalPinToInterrupt(PIN));

  // Need receiving 20 equal code, report only after approx. 2500ms (but sure to read read value)
  mySwitch.setReveiceRepeat(20);
  
  Serial.println("Started");
}

void loop() {
  if (mySwitch.available())
  {
    long rfvalue = mySwitch.getReceivedValue(PIN);
    unsigned long elapsed = millis() - RFLastTime;
    
    //Skip repeated received values = continuously pressed button
    if (RFLastValue != rfvalue || elapsed > RFRepeatTimeMs)
    {
      Serial.print("Received ");
      Serial.print( String(mySwitch.getReceivedValue(PIN), 16) );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength(PIN) );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.print( mySwitch.getReceivedProtocol(PIN) );
      Serial.print(" Delay: ");
      Serial.println( mySwitch.getReceivedDelay(PIN) );
    }
    RFLastValue = rfvalue;
    RFLastTime = millis();
    
    mySwitch.resetAvailable();
  }
  delay(10);
}
