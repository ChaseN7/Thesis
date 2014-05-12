#include "traitclass.h"

double TraitClass::Mutation = 0;
double TraitClass::TotalEventRate = 0;
double TraitClass::Size = 0;
double TraitClass::K = 0;
std::vector<std::vector<double>> TraitClass::CompDeathRate;
//double** TraitClass::CompDeathVector;


TraitClass::TraitClass()
{
    Members = 0;
    BirthRate = 0;
    TotalBirthRate = 0;
    DeathRate = 0;
    TotalDeathRate = 0;
    TotalTraitRate = 0;
}

TraitClass::~TraitClass()
{

}

void TraitClass::setTraitSize(int size)
{
    TraitClass::Size = size;
    TraitClass::CompDeathRate.clear();
    TraitClass::TotalEventRate = 0;
    for(int i = 0; i < size; i++){
        std::vector<double> tmp;
        tmp.assign(size,0);
        TraitClass::CompDeathRate.push_back(tmp);
    }
}

//int TraitClass::getMembers()
//{
//    return Members;
//}

//void TraitClass::setMembers(int NewMembers)
//{
//    Members = NewMembers;
//}

