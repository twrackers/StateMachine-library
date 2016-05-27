#include <StateMachine.h>

// Constructor
//
// See StateMachine.h for explanation of real-time vs non-real-time operation.
StateMachine::StateMachine(
    const unsigned int updateDelta,     // time in milliseconds between updates
    const bool realTime                 // real-time vs non-real-time
) : m_updateDelta((unsigned long) updateDelta), m_realTime(realTime)
{
    // A zero update interval is not allowed, set to minimum of 1 msec.
    if (m_updateDelta == 0) ++m_updateDelta;
    // First update will occur m_updateDelta msec from now.
    m_nextUpdate = millis() + m_updateDelta;
}

// Check for time-to-update
//
// Returns true if it's time to perform the next update of the FSM.
bool StateMachine::update()
{
    // Get the current clock time in msec.
    unsigned long now = millis();
    // Have we reached or passed the scheduled time for an update?
    if (now >= m_nextUpdate) {
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