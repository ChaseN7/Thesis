#ifndef TRAITEVENTMANAGER_H
#define TRAITEVENTMANAGER_H

#include "traitclass.h"
#include "eventclass.h"
#include "randomdice.h"
#include "filestreaming.h"
#include <QVector>

class TraitEventManager
{
public:
    TraitEventManager();
    TraitEventManager(QString FileName);
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
    bool initWithFile(QString FName);
    double getKMembers(int TraitIndex);
    double retStableDimorphOf(int i) const;
    QVector<double> retStableDimorphVector() const;
    double getStableMonoStateOf(int i);
    bool isNear(QVector<double> &Expected);

public:
    RandomDice Dice;
    std::vector<TraitClass> Trait;
    EventClass Events;
};

#endif // TRAITEVENTMANAGER_H
