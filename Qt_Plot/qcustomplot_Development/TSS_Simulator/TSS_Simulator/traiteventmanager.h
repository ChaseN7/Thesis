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
    /// All Methods below should be private after testing is over.
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
    void ImprovedEvolutionStep();

    /// Performence increasing Method
    /// FIXME: not clean coded, but selfexplaining and simple
    void adjustNewEventRates();

    /// Utilities
    bool initWithFile(QString FName);
    double getKMembers(int TraitIndex) const;
    double retStableDimorphOf(int i) const;
    double retStableMonoStateOf(int i) const;
    QVector<double> retStableDimorphKVector() const;
    QVector<double> retStableMonoKVector() const;
    bool isNear(QVector<double> &Expected);
    void calcFitness();

    /// Testing
    void clearData();
public:
    RandomDice Dice;
    std::vector<TraitClass> Trait;
    EventClass Events;
};

#endif // TRAITEVENTMANAGER_H
