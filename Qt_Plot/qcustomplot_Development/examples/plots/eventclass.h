#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

class EventClass
{
public:
    EventClass();
    void clearEvents();

public:
    std::vector<double> EventTimes;
    std::vector<double> ChosenTrait;
    std::vector<double> isBirth;
};

#endif // EVENTS_H
