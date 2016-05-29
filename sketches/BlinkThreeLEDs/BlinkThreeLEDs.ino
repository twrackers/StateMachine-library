#include <StateMachine.h>

StateMachine blinker1(1000, true);
StateMachine blinker2(1010, true);
StateMachine blinker3(1020, true);

const int led1 = 6;
const int led2 = 5;
const int led3 = 3;

bool state1 = false;   // false is OFF, true is ON
bool state2 = false;   // false is OFF, true is ON
bool state3 = false;   // false is OFF, true is ON

void setup() 
{
  pinMode(led1, OUTPUT);
  digitalWrite(led1, state1 ? HIGH : LOW);
  pinMode(led2, OUTPUT);
  digitalWrite(led2, state2 ? HIGH : LOW);
  pinMode(led3, OUTPUT);
  digitalWrite(led3, state3 ? HIGH : LOW);
}

void loop() 
{
  if (blinker1.update()) {
    state1 = !state1;
    digitalWrite(led1, state1 ? HIGH : LOW);
  }
  if (blinker2.update()) {
    state2 = !state2;
    digitalWrite(led2, state2 ? HIGH : LOW);
  }
  if (blinker3.update()) {
    state3 = !state3;
    digitalWrite(led3, state3 ? HIGH : LOW);
  }
}

