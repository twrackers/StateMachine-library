#include <StateMachine.h>

// Define new Blinky class which inherits from StateMachine.
class Blinky : public StateMachine
{
  private:
    const byte m_pin;   // pin number to toggle
    bool m_state;       // current state (true=HIGH, false=LOW)

  public:
    // Constructor
    Blinky(const byte pin, const unsigned int period) :
      StateMachine(period, true),   // period in milliseconds, realtime mode
      m_pin(pin), m_state(false)
    {
      // Set GPIO pin to OUTPUT mode.
      pinMode(m_pin, OUTPUT);
      // Initialize GPIO pin to match state.
      digitalWrite(m_pin, m_state ? HIGH : LOW);
    }

    // Update method, runs from loop() function
    virtual bool update()
    {
      // Is it time to update this Blinky?
      if (StateMachine::update()) {
        // If so, toggle its state...
        m_state = !m_state;
        // ... and set GPIO pin to match new state.
        digitalWrite(m_pin, m_state ? HIGH : LOW);
        // We updated.
        return true;
      }
      // We didn't update anything this time around.
      return false;
    }
};

// We'll define 4 Blinky objects to drive 4 LEDs.
const int NUM = 4;

// Create an array of pointer-to-Blinky.
Blinky* blinkys[NUM];

// This runs only once.
void setup()
{
  // Create 4 Blinky objects.  Pin numbers will be 8, 9, 10, 11.
  // Periods in milliseconds will be 1000, 1010, 1020, 1030.
  // With these periods, the four LEDs will take 530,553,000 milliseconds,
  // or roughly 6 days 3 hours 22 minutes after start to resynchronize.
  for (byte i = 0; i < NUM; ++i) {
    byte pin = 8 + i;
    unsigned int period = 1000 + i * 10;
    // Create an actual Blinky object now.
    blinkys[i] = new Blinky(pin, period);
  }
}

// This runs repeatedly.
void loop()
{
  // Update all Blinky objects together.
  StateMachine::updateAll(blinkys, NUM);
}
