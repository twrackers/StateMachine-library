/**
 * StateMachine
 *
 * Author: Thomas W Rackers, May 2016
 * GitHub: https://github.com/twrackers
 * Blog:   https://modelrailroadelectronics.blog
 */

#include <StateMachine.h>

// Constructor
//
// See StateMachine.h for explanation of real-time vs non-real-time operation.
StateMachine::StateMachine(
    const unsigned long updateDelta,  // time between updates (default zero)
    const realtime_t realTime,        // true for real-time (default),
                                      // false for non-real-time
    const hires_t hires               // true if updateDelta is usec,
                                      // false if updateDelta is msec (default)
) : m_updateDelta(updateDelta), m_nextUpdate(0L),
    m_realTime(realTime), m_hires(hires)
{
    if (m_updateDelta) {
        // First update will occur m_updateDelta msec or usec from now.
        m_nextUpdate = (m_hires ? micros() : millis()) + m_updateDelta;
    }
}

// Check for time-to-update
//
// Returns true if it's time to perform the next update of the FSM.
bool StateMachine::update()
{
    // Return right away if m_updateDelta is zero.
    if (m_updateDelta == 0) {
        return true;
    }
    // Get the current clock time.
    unsigned long now = (m_hires ? micros() : millis());
    // Have we reached or passed the scheduled time for an update?
    if ((long) (now - m_nextUpdate) >= 0L) {
        // If so, schedule the next update...
        if (m_realTime) {
            // ... based on when this update was scheduled, ...
            m_nextUpdate += m_updateDelta;
        } else {
            // ... or based on when this update is actually occurring.
            m_nextUpdate = now + m_updateDelta;
        }
        // Tell subclass it should update.
        return true;
    }
    // Not time yet for update.
    return false;
}

// Perform updates on a collection of StateMachine objects.
void StateMachine::updateAll(
    StateMachine** fsm, // pointer to array of pointers to StateMachine objects
    const int num       // number of pointers in array
)
{
    // We'll step through array of pointers to StateMachine objects.
    StateMachine** p = fsm;
    for (int i = 0; i < num; ++i) {
        // Update i'th StateMachine and bump pointer.
        (*p++)->update();
    }
}
