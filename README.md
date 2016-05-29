# StateMachine

These files define a simple Finite-State Machine class for use with Arduino-type processors and the Arduino IDE.

The original concept is drawn from the description of multitasking on the Arduino in Adafruit's Learn Arduino pages, specifically here.

  https://learn.adafruit.com/multi-tasking-the-arduino-part-1/overview?view=all

StateMachine is a base class from which subclasses can inherit the basic behavior of a finite-state machine, or FSM (not to be confused with the Flying Spaghetti Monster).  A custom FSM will extend the StateMachine base class, and must implement two methods:

* a constructor to create and initialize a new custom FSM object, and
* an update method which changes the FSM's internal state based upon time, input conditions, or whatever is required.
  
There is also a convenience method, at the class level (i.e. a static method) to allow an application to perform the update method on a collection of FSM objects with a single call.

The best way to see how the StateMachine base class can be extended into a really useful class is to look at some of the other classes in this repository.

* [__Arduino/libraries/FadeLED__](https://github.com/twrackers/Arduino-projects/tree/master/libraries/FadeLED)
* [__Arduino/libraries/Pulser__](https://github.com/twrackers/Arduino-projects/tree/master/libraries/Pulser)
* [__Arduino/libraries/SlowSwitcher__](https://github.com/twrackers/Arduino-projects/tree/master/libraries/SlowSwitcher)
