#define INT_A 11    // control the left motor direction pin to D2
#define INT_B 12    // control the right motor direction pin to D4

// Encoder output to Arduino Interrupt pin. Tracks the pulse count.
#define ENC_IN_RIGHT_A 3

// Ultrasonic 
int servopin=9;// digital 9 is connected to servo signal pin
int myangle;// define the angle
int pulsewidth;// define the pulsewidth 
#include <SR04.h>    // add the ultrasonic libraries 
#define TRIG_PIN 4   // define the pin ting of ultrasonic as D12
#define ECHO_PIN 5   //define the pin echo of ultrasonic as D13
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);    // build the ultrasonic object to control the ultrasonic 
long a;      // used to receive the distance measured by ultrasonic 

// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;

void setup() 
{
  Serial.begin(9600);  // set the monitor baud rate to 9600
  delay(100);     // delay 100ms
  digitalWrite(11,OUTPUT);// set the servo pin as OUTPUT 
  digitalWrite(12,OUTPUT);
  pinMode(servopin,OUTPUT);
  servopulse(servopin,70);  // call the pulse function, make the ultrasonic keep front.

  // Set pin states of the encoder
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);
  
   // Every time the pin goes high, this is a pulse
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);
}

void loop() 
{
   a=sr04.Distance();    // assign the front distance measured by ultrasonic to a
   Serial.print(a);     // print a value on the monitor 
   Serial.println("cm");   // print cm and line wrap 
   delay(100);    // delay
   if(a>20){
    forward(15);
    delay(100);
    a = sr04.Distance();
    Serial.println(a);
   }
   if(a<20)    // whether the distance a is less than 15cm, if yes, then perform the program in the brace.
   {
    Stop();    // car stops
    delay(100);   // delay 100ms
    right();
    delay(100);
    forward(25);
    left();
    a= sr04.Distance();
    }
}

void right_wheel_pulse() {
  right_wheel_pulse_count++;
}

// forward
void front()
{
  Serial.println("front");
  analogWrite(11,220);   // set the motor speed（PWM=200)
  analogWrite(12,255); 
}

void forward (int input_distance)
{
  // contants used
  int x = 1 ;

  // converting distance to encoder count
  float target_distance = input_distance;
  int target_count;
  int counter = 0 ;
  int count_per_rev = 645 ; // constant , identified via visual test
  float wheel_circumference = 13.91; //CM diameter was measured by a caliper and wheel cirsumference was calculated
  target_count = ((target_distance / wheel_circumference) * count_per_rev);
  Serial.println("target count : ");
  Serial.print(target_count);
  Serial.println();


  while (x == 1)
  {
    Serial.print(right_wheel_pulse_count);
    Serial.println();
    if (right_wheel_pulse_count != target_count)
    {
      analogWrite(12, 255);// left
      analogWrite(11, 220);// right
    }
    if (right_wheel_pulse_count >= target_count)
    {
      analogWrite(12, 0);
      analogWrite(11, 0);
      right_wheel_pulse_count = 0; // reset the counter before exit
      x = 0; // breaks out of the while loop
    }
  }
}
// turn left
void left()
{
  // contants used
  int x = 1 ;

  // converting distance to encoder count
  float target_distance = 27.487 * 3; // calculated distance that must be travelled to do a left turn based on the robot wheel base distance
  int target_count;
  int counter = 0 ;
  int count_per_rev = 645 ; // constant , identified via visual test
  float wheel_circumference = 13.91; //CM diameter was measured by a caliper and wheel cirsumference was calculated
  target_count = ((target_distance / wheel_circumference) * count_per_rev);
  Serial.println("target count : ");
  Serial.print(target_count);
  Serial.println();
  while (x == 1)
  {
    Serial.print(right_wheel_pulse_count);
    Serial.println();
    if (right_wheel_pulse_count != target_count)
    {
      analogWrite(12, 255);

    }
    if (right_wheel_pulse_count >= target_count)
    {
      analogWrite(12, 0);

      right_wheel_pulse_count = 0; // reset the counter before exit
      x = 0; // breaks out of the while loop
    }
  }
}
// turn right 
void right()
{
 // contants used
    int x = 1 ;
  
    // converting distance to encoder count
    float target_distance = 27.487; // calculated distance that must be travelled to do a right turn based on the robot wheel base distance
    int target_count;
    int counter = 0 ;
    int count_per_rev = 645 ; // constant , identified via visual test
    float wheel_circumference = 13.91; //CM diameter was measured by a caliper and wheel cirsumference was calculated
    target_count = ((target_distance / wheel_circumference) * count_per_rev);
    Serial.println("target count : ");
    Serial.print(target_count);
    Serial.println();
    while (x == 1)
    {
      Serial.print(right_wheel_pulse_count);
      Serial.println();
      if (right_wheel_pulse_count != target_count)
      {
        analogWrite(12, 255);
  
      }
      if (right_wheel_pulse_count >= target_count)
      {
        analogWrite(12, 0);
  
        right_wheel_pulse_count = 0; // reset the counter before exit
        x = 0; // breaks out of the while loop
      }
    }
}
// stop
void Stop()
{  
  analogWrite(11,0);     // PWM of both left and right is 0
  analogWrite(12,0);
}
// servo
void servopulse(int servopin,int myangle)// define a pulse function
{
  for(int i=0;i<50;i++)
  {
    pulsewidth=(myangle*11)+500;// convert the angle into the pulsewidth of 500-2480 
    digitalWrite(servopin,HIGH);// servo pin to HIGH 
    delayMicroseconds(pulsewidth);// delay the microseconds of pulsewidth 
    digitalWrite(servopin,LOW);// servo pin to LOW
    delay(20-pulsewidth/1000); // delay the rest circle time to LOW level（20ms circle ）
  }
}
