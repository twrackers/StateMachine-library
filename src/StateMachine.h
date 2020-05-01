#ifndef _STATE_MACHINE__H_
#define _STATE_MACHINE__H_

#include <Arduino.h>

/**
 * StateMachine
 * 
 * This class is a base class which implements a simple Finite State Machine
 * or FSM.  It provides the basic timing for the FSM's update cycle, but leaves
 * the definitions of the states and the implementation of the state-change
 * logic to subclasses which inherit from this class.
 *
 * The concept of real-time in this class requires some explanation.  When the
 * system clock as returned by function micros() is equal or greater than
 * m_nextUpdate, the time of the next scheduled update, the update() method will
 * update m_nextUpdate with the time of this FSM's next update, then it returns
 * true, indicating whatever subclass has inherited from this class should 
 * perform its update as well.
 *
 * If m_realTime is set to true by the constructor, then the next update will be
 * set to occur m_updateDelta microseconds later than this update's scheduled
 * time, even if this update is occurring later than scheduled.
 *
 * If m_realTime is set to false, then the next update will be set to occur 
 * m_updateDelta microseconds later than when this update is actually occurring.
 *
 * So if trying to keep to a fixed periodic rate on the updates is important,
 * then the constructor should be called with realTime set to true.
 *
 * If it's more important to maintain a minimum interval between updates, even
 * if an update runs late, then the constructor should be called with realTime
 * set to false.
 *
 * Author: Thomas W Rackers, May 2016
 * GitHub: https://github.com/twrackers
 * Blog:   https://modelrailroadelectronics.blog
 */
class StateMachine
{
    protected:
        unsigned long m_updateDelta;    // time between updates
        unsigned long m_nextUpdate;     // time of next scheduled update
        const bool m_realTime;          // real-time vs non-real-time
        
    public:
        /**
         * Constructor
         *
         * @param updateDelta interval between update cycles.
         * @param realTime true enforces periodic updates, false enforces
         *                 minimum intervals between updates
         * @param hires true if updateDelta is in microseconds rather than
         *                 milliseconds (default false)
         */
        StateMachine(
            const unsigned int updateDelta, 
            const bool realTime,
            const bool hires = false
        );
        
        /**
         * Test for time to update
         *
         * Tests if the FSM's next time-to-update has arrived.  If so, the next
         * update is scheduled and this method returns true.  Otherwise, it
         * returns false without modifying the time of the next update.
         *
         * This method is meant be overridden by the inheriting subclass.
         *
         * @return true if time for update, false otherwise
         */
        virtual bool update();
        
        /**
         * Update a list of StateMachine objects
         *
         * If given an array of pointers to StateMachine objects, this class
         * method will call their update() methods in the order given.
         *
         * @param fsm pointer to array of pointers to StateMachine objects to
         *      be updated together
         * @param num number of pointers in array fsm
         */
        static void updateAll(
            StateMachine** fsm,
            const int num
        );
};

#endif
