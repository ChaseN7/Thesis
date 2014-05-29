#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

class EventClass
{
public:
    EventClass();
    void clearEvents();

public:
    double EventTimes;
    double ChosenTrait;
    bool isBirth;
};

#endif // EVENTS_H
