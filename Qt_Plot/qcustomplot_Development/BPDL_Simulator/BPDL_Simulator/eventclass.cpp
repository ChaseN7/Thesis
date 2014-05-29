#include "eventclass.h"

EventClass::EventClass()/*:
    EventTimes(),
    ChosenTrait(),
    isBirth()*/
{
//    EventTimes.assign(1,0.);
//    ChosenTrait.assign(1,0.);
//    isBirth.assign(1,0.);
}

void EventClass::clearEvents()
{
    EventTimes = 0;
    ChosenTrait = 0;
    isBirth = false;
}
