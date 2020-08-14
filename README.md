# StateMachine

These files define a simple Finite-State Machine class for use with Arduino-type processors and the Arduino IDE.

The original concept is drawn from the description of multitasking on the Arduino in Adafruit's Learn Arduino pages, specifically here.

  https://learn.adafruit.com/multi-tasking-the-arduino-part-1/overview?view=all

StateMachine is a base class from which subclasses can inherit the basic behavior of a finite-state machine, or FSM (not to be confused with the Flying Spaghetti Monster).  A custom FSM will extend the StateMachine base class, and must implement two methods:

* a constructor to create and initialize a new custom FSM object, and
* an update method which changes the FSM's internal state based upon time, input conditions, or whatever is required.
  
There is also a convenience method, at the class level (i.e. a static method) to allow an application to perform the update method on a collection of FSM objects with a single call.

The best way to see how the StateMachine base class can be extended into a really useful class is to look at some of the other classes in this repository, all of which inherit from StateMachine.

* [__FadeLED__](https://github.com/twrackers/FadeLED-library)
* [__Pulser__](https://github.com/twrackers/Pulser-library)
* [__SlowSwitcher__](https://github.com/twrackers/SlowSwitcher-library)

## NOTE 1
The StateMachine timing mechanism relies on the Arduino IDE's _millis()_ function, which returns the number of milliseconds since the Arduino was reset as a 32-bit _unsigned long_.  The internal clock counter will roll over to zero after a little over 49 days.  At this time that will cause unexpected behavior in StateMachine objects.
## NOTE 2
The timing behavior above has now been fixed.
## NOTE 3
High-precision (microseconds vs milliseconds) timing is now supported.  An optional boolean parameter _hires_ to the constructor causes the StateMachine to select between using _millis()_ or _micros()_ to get the system time.  This also sets the units of the next time to update and the update interval to match the resolution of the clock function being used.
