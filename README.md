# StateMachine #

----------

The `StateMachine` class defines a framework for *Finite-State Machines* for use with Arduino-type processors and the Arduino IDE.

The original concept is drawn from the description of multitasking on the Arduino in Adafruit's Learn Arduino pages ([https://learn.adafruit.com/multi-tasking-the-arduino-part-1](https://learn.adafruit.com/multi-tasking-the-arduino-part-1)).

`StateMachine` is a base class from which subclasses can inherit the basic behavior of a finite-state machine, or FSM (not to be confused with the Flying Spaghetti Monster).  A custom FSM will extend the `StateMachine` base class, and must implement two methods:

* a constructor to create and initialize a new custom FSM object, and
* an update method which changes the FSM's internal state based upon time, input conditions, or whatever is required.

There is also a convenience method, at the class level (i.e. a static method) to allow an application to perform the update method on a collection of FSM objects with a single call.

The `StateMachine` class itself defines no state information other than those parameters which handle the timing.  Derived classes which inherit from `StateMachine` are responsible for defining any other state information required by the class's logic.

## Real-time vs. Non-real-time ##

A `StateMachine` can be created as a *real-time* or a *non-real-time* object.  The difference is in how each update is scheduled after the previous update.

- If `update()` is called before the next update is scheduled, no action is taken and `false` is returned.
- If `update()` is called when or after the next update was scheduled, the state of the `StateMachine` object is updated, and the following update is scheduled.  After updating and rescheduling occur, `true` is returned.
	- In real-time mode, the time of the next update will be the time when the current update was scheduled, plus the update interval given when the state machine was created.  So even if the current update is occurring late, the next one should happen on time as long as it isn't late as well.
	- In non-real-time mode, the next update will not be scheduled relative to when the current update was scheduled to happen, but when it *does* happen.

As an example, let's define two state machines as follows.

    StateMachine fsmRT(500, true);
    StateMachine fsmNRT(500, false);

Suppose both are scheduled to do their next updates when the clock (`millis()` in the Arduino library) reaches 10000.  However, due to a longer than expected operation, both try to update when the clock reads 10100, or 100 milliseconds late.  Both will update, but `fsmRT` will schedule its next update at 10500, while `fsmNRT` will be scheduled for 10600, or 500 milliseconds after the current time, not its previous scheduled time of 10000.

In the special case where the state machine is created without an update interval, or with a zero interval, then no scheduling is done and the state machine can update upon every pass through `loop()`.

### Use cases ###

A state machine with a zero update delay can be used in cases where the timing of state changes is not important, only their sequencing matter.  An example would be a state machine which parses a string of characters according to one or more patterns.

A real-time state machine would be used for cases where it's important to maintain a fixed pace, even if an update occasionally occurs a little late.

A non-real-time state machine would be used for cases where it's more important to maintain a minimum interval between one update and the next.  So if an update occurs a little late, all following updates would nominally be bumped back by the delay.

## High-resolution mode ##

By default, a `StateMachine` is created in low-resolution mode.  In this mode, the interval between updates is set in *milliseconds*.  In low-resolution mode, the timing code will roll over to zero every 2³² milliseconds, or just over 49 days 17 hours.

If a `StateMachine` is created in high-resolution mode (see the constructor definition in the API section below), the update interval is set in *microseconds*.  In this mode, the timing code will roll over every 2³² *micro*seconds, or just over 71 minutes 35 seconds.

## Examples ##

The `StateMachine` library includes a few example sketches in the `examples` directory.

- `BlinkOneLED` behaves in a similar manner to the `Blink` example which is supplied with the Arduino IDE, except a `StateMachine` object is used rather than `delay()` calls to set the timing of a blinking LED.  It defaults to using GPIO pin 9 to drive the LED, but you can edit the source to use `LED_BUILTIN` instead.
- `BlinkThreeLEDs` expands the one-LED example to control **three** LEDs, connected by default to GPIO pins 6, 5, and 3.  Each `StateMachine` object is defined with a slightly different update period of about 1 second, and each will control one of the three LEDs.
- `BlinkClassy` blinks four LEDs on pins 8, 9, 10, 11 at slightly different rates.  In this example, a `Blinky` class derives from `StateMachine`, and each `Blinky` is assigned its own GPIO pin number and update period.  With update periods of 1000, 1010, 1020, and 1030 milliseconds, the four LEDs will resynchronize every 530553000 milliseconds, or about 6 days 3 hours 22 minutes.  (530553000 is the lowest common multiple or LCM of the four periods.)
  
Another way to see how the `StateMachine` base class can be extended into a really useful class is to look at some of the other classes in these repositories which inherit from `StateMachine`.

* [__FadeLED__](https://github.com/twrackers/FadeLED-library)
* [__Pulser__](https://github.com/twrackers/Pulser-library)
* [__SlowSwitcher__](https://github.com/twrackers/SlowSwitcher-library)

## Dependencies ##

The `StateMachine` class has no dependencies on any libraries which are not included in the standard Arduino IDE installation.

## Installation ##

Instructions for installing the *StateMachine* class can be found in file `INSTALL.md` in this repository at [https://github.com/twrackers/StateMachine-library/blob/main/INSTALL.md](https://github.com/twrackers/StateMachine-library/blob/main/INSTALL.md).
