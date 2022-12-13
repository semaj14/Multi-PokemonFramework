#include <Headers.hpp>

namespace CTRPluginFramework {
    static inline Time GetCurrentTime(void) {
        return Ticks(svcGetSystemTick());
    }

    Clock::Clock(void) :
        _startTime(GetCurrentTime())
    {}

    Clock::Clock(Time time) :
        _startTime{ time }
    {}

    Time Clock::GetElapsedTime(void) const {
        return (GetCurrentTime() - _startTime);
    }

    bool Clock::HasTimePassed(Time time) const {
        return (GetElapsedTime() >= time);
    }

    Time Clock::Restart(void) {
        Time now = GetCurrentTime();
        Time ret = now - _startTime;
        _startTime = now;
        return (ret);
    }
}