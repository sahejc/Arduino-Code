
#include <IRremote.h>
int IRpin=9;
IRrecv IR(IRpin);
decode_results cmd;
void setup() {
  // put your setup code here, to run once:
   IR.enableIRIn();
   Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  
   
 while(IR.decode(&cmd)==0){
 }
 
Serial.println(cmd.value,HEX);
delay(1500);
IR.resume();
}
