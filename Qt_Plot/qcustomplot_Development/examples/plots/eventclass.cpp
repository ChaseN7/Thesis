#include "eventclass.h"

EventClass::EventClass():
    EventTimes(),
    ChosenTrait(),
    isBirth()
{
}

void EventClass::clearEvents()
{
    EventTimes.clear();
    ChosenTrait.clear();
    isBirth.clear();
}
