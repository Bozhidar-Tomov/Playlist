#pragma once
#include <ostream>

constexpr unsigned SECONDS_IN_HOURS = 3600;
constexpr unsigned SECONDS_IN_MINUTE = 60;
constexpr unsigned DAY_SECONDS = 24 * 3600;

class Time
{
private:
    unsigned secondsFromMidnight = 0;
    bool _isValid = true;

    bool validateAndSet(unsigned, unsigned, unsigned, unsigned, unsigned);

public:
    Time() = default;
    Time(unsigned, unsigned, unsigned);

    unsigned getHours() const;

    unsigned getMins() const;

    unsigned getSeconds() const;
    bool setHours(unsigned);

    bool setMins(unsigned);
    bool setSeconds(unsigned);

    bool isValid() const;

    void tick();

    bool isLess(const Time &) const;
    bool isEq(const Time &) const;
    bool isBigger(const Time &) const;

    void serialize(std::ostream &) const;
};