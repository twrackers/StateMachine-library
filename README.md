# StateMachine

The `StateMachine` class defines a framework for *Finite-State Machines* for use with Arduino-type processors and the Arduino IDE.

The original concept is drawn from the description of multitasking on the Arduino in Adafruit's Learn Arduino pages ([https://learn.adafruit.com/multi-tasking-the-arduino-part-1](https://learn.adafruit.com/multi-tasking-the-arduino-part-1)).

`StateMachine` is a base class from which subclasses can inherit the basic behavior of a finite-state machine, or FSM (not to be confused with the Flying Spaghetti Monster).  A custom FSM will extend the `StateMachine` base class, and must implement two methods:

* a constructor to create and initialize a new custom FSM object, and
* an update method which changes the FSM's internal state based upon time, input conditions, or whatever is required.

There is also a convenience method, at the class level (i.e. a static method) to allow an application to perform the update method on a collection of FSM objects with a single call.

The `StateMachine` class itself defines no state information other than those parameters which handle the timing.  Derived classes which inherit from `StateMachine` are responsible for defining any other state information required by the class's logic.

## Examples ##

The `StateMachine` library includes a pair of example sketches in the `examples` directory.

- `BlinkOneLED.ino` behaves in a similar manner to the `Blink` example which is supplied with the Arduino IDE, except a `StateMachine` object is used rather than `delay()` calls to set the timing of a blinking LED.  It defaults to using GPIO pin 9 to drive the LED, but you can edit the source to use `LED_BUILTIN` instead.
- `BlinkThreeLEDs.ino` expands the one-LED example to control **three** LEDs, connected by default to GPIO pins 6, 5, and 3.  Each `StateMachine` object is defined with a slightly different update period of about 1 second, and each will control one of the three LEDs.
  
The best way to see how the `StateMachine` base class can be extended into a really useful class is to look at some of the other classes in these repositories, all of which inherit from `StateMachine`.

* [__FadeLED__](https://github.com/twrackers/FadeLED-library)
* [__Pulser__](https://github.com/twrackers/Pulser-library)
* [__SlowSwitcher__](https://github.com/twrackers/SlowSwitcher-library)

## Dependencies ##

The `StateMachine` class has no dependencies on any libraries which are not included in the standard Arduino IDE installation.

## Installation ##

Instructions for installing the *StateMachine* class can be found in file `INSTALL.md` in this repository at [https://github.com/twrackers/StateMachine-library/blob/main/INSTALL.md](https://github.com/twrackers/StateMachine-library/blob/main/INSTALL.md).