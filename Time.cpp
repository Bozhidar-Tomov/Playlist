#include "Time.h"
#include <iomanip>

bool Time::validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldVlaue, unsigned multiplier)
{

    if (newValue >= lowerBound && newValue <= upperBound)
    {
        (secondsFromMidnight -= (oldVlaue * multiplier)) += (newValue * multiplier);
        return true;
    }
    else
        return false;
}

Time::Time(unsigned hours, unsigned mins, unsigned seconds)
{
    if (setHours(hours) && setMins(mins) && setSeconds(seconds))
        _isValid = true;
    else
        _isValid = false;
}

unsigned Time::getHours() const
{
    return secondsFromMidnight / SECONDS_IN_HOURS;
}

unsigned Time::getMins() const
{
    return (secondsFromMidnight / 60) % 60;
}

unsigned Time::getSeconds() const
{
    return secondsFromMidnight % 60;
}
bool Time::setHours(unsigned hours)
{
    return validateAndSet(0, 23, hours, getHours(), SECONDS_IN_HOURS);
}

bool Time::setMins(unsigned mins)
{
    return validateAndSet(0, 59, mins, getMins(), SECONDS_IN_MINUTE);
}
bool Time::setSeconds(unsigned seconds)
{
    return validateAndSet(0, 59, seconds, getSeconds(), 1);
}

bool Time::isValid() const
{
    return _isValid;
}

void Time::tick()
{
    ++secondsFromMidnight %= DAY_SECONDS;
}

bool Time::isLess(const Time &rhs) const
{
    return secondsFromMidnight < rhs.secondsFromMidnight;
}

bool Time::isEq(const Time &rhs) const
{
    return secondsFromMidnight == rhs.secondsFromMidnight;
}

bool Time::isBigger(const Time &rhs) const
{
    return !isLess(rhs) && !isEq(rhs);
}

void Time::serialize(std::ostream &os) const
{
    os << std::setw(2) << std::setfill('0') << getHours() << ":"
       << std::setw(2) << std::setfill('0') << getMins() << ":"
       << std::setw(2) << std::setfill('0') << getSeconds();
}