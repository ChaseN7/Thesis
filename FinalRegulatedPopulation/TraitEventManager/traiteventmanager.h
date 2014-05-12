#ifndef TRAITEVENTMANAGER_H
#define TRAITEVENTMANAGER_H

#include "traitclass.h"
#include "eventclass.h"
#include "randomdice.h"
#include "filestreaming.h"

class TraitEventManager
{
public:
    TraitEventManager();
    TraitEventManager(QString FileName, std::vector<TraitClass> &Traits);
    TraitEventManager(int n);
    void addTotalCompDeathRateOf(int TraitIndex);
    void addTotalIntrisicDeathRateOf(int TraitIndex);
    void calculateTotalDeathRateOf(int TraitIndex);
    void calculateTotalBirthRates(int StartRecursion);
    void calculateTotalEventRate();
    void calculateEventRates();
    void sampleEventTime();
    void choseTraitToChange();
    void choseEventType();
    void executeEventTypeOnTrait();
    void changeATrait();
    void EvolutionStep();

    // Utilities
    void clearData();
    double getKMembers(int TraitIndex);
    double getStableDimorphStateOf(int i);
    double getStableMonoStateOf(int i);
    std::vector<double> getAmoutOfTraitChanges();

public:
    RandomDice Dice;
    std::vector<TraitClass> Trait;
    EventClass Events;
    FileStreaming Stream;
};

#endif // TRAITEVENTMANAGER_H
