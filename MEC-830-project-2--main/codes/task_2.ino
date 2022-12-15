// Encoder output to Arduino Interrupt pin. Tracks the pulse count.
#define ENC_IN_RIGHT_A 3

// Keep track of the number of right wheel pulses
volatile long right_wheel_pulse_count = 0;

void setup() {

  // Open the serial port at 9600 bps
  Serial.begin(9600);

  // Set pin states of the encoder
  pinMode(ENC_IN_RIGHT_A , INPUT_PULLUP);

  // Every time the pin goes high, this is a pulse
  attachInterrupt(digitalPinToInterrupt(ENC_IN_RIGHT_A), right_wheel_pulse, RISING);

}

void loop() {

  forward(110);
  right();
  forward(110);
  left();
  forward(110);

  Serial.println("code done");
  delay(100);
  exit(0);
}

/////functions////
// Increment the number of pulses by 1
void right_wheel_pulse() {
  right_wheel_pulse_count++;
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
      analogWrite(12, 253);// left
      analogWrite(11, 215);// right
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

void right ()
{
  // contants used
  int x = 1 ;

  // converting distance to encoder count
  float target_distance = 27.00; // calculated distance that must be travelled to do a right turn based on the robot wheel base distance
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

void left ()
{
  // contants used
  int x = 1 ;

  // converting distance to encoder count
  float target_distance = 26.8 * 3; // calculated distance that must be travelled to do a left turn based on the robot wheel base distance
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
