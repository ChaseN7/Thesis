#ifndef TRAIT_H
#define TRAIT_H

#include <vector>
#include <array>

class TraitClass
{
public:
    TraitClass();
    ~TraitClass();  // TODO
    static void setTraitSize(int size);

public:
    double Members;
    double BirthRate;
    double TotalBirthRate;
    double DeathRate;
    double TotalDeathRate;
    double TotalTraitRate;

    /// FIXME: Move most static's to TraitEventManager
    static double Mutation;
    static double TotalEventRate;
    static double Size;
    static double K;
    static std::vector<std::vector<double>> CompDeathRate;
    static std::vector<std::vector<double>> Fitness;

private:
    /// FIXME: Make getters and setters after moving the statics
};

#endif // TRAIT_H
