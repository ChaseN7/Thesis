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
    static double Mutation;
    static double TotalEventRate;
    static std::vector<std::vector<double>> CompDeathRate;
    static double Size;
    static double K;

private:

};

#endif // TRAIT_H
