#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){ 

        switch(results.value){
          case 0xFF629D:
          forward();
          Serial.println("FORWARD");
          break;
          case 0xFF22DD:
          right();
          Serial.println("RIGHT");
          break;
          case 0xFFC23D:
          left();
          Serial.println("LEFT");
          break;
          case 0xFFE21D:
          stop();
          Serial.println("STOP");
          break ;
        }
        irrecv.resume(); 
  }
}

void forward(){
  analogWrite(11,255);
  analogWrite(12,255); 
}


void left()
{
  analogWrite(11,0);
  analogWrite(12,255);
}

void right()
{
  analogWrite(11,255);
  analogWrite(12,0);
}

void stop()
{
  analogWrite(11,0);
  analogWrite(12,0);
}
