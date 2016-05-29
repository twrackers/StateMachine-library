#include <StateMachine.h>

StateMachine blinker(1000, true);

const int led = 9;
bool state = false;   // false is OFF, true is ON

void setup() 
{
  pinMode(led, OUTPUT);
  digitalWrite(led, state ? HIGH : LOW);
}

void loop() 
{
  if (blinker.update()) {
    state = !state;
    digitalWrite(led, state ? HIGH : LOW);
  }
}

