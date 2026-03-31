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

// This runs only once.
void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
}

const uint32_t interval0 = 1000;      // blink interval is initially 1000 msec
const byte count0 = 100;              // rate adjustment cycles every 10 sec

StateMachine adjust(100, true);       // adjusts blink rate every 100 msec
Blinky blink(LED_BUILTIN, interval0);

uint32_t interval = interval0;
byte count = count0;

// This runs repeatedly.
void loop()
{

  // Every 100 msec...
  if (adjust.update()) {
    if (count) {
      // either cut the blink rate by 2%
      interval = interval * 98 / 100;
      --count;
    } else {
      // or reset to slowest blink rate
      interval = interval0;
      count = count0;
    }
    // Adjust the blink rate.
    blink.setInterval(interval);  // intervals in msec
  }
  
  // Update the Blinky object.
  blink.update();
 
}
