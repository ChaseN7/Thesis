#include "randomdice.h"
#include <time.h>

RandomDice::RandomDice():generator(time(0)){
//    generator.seed(time(0));
}
double RandomDice::computeAverage(int Loops){
    double Average = 0;
    for(int i = 0; i < Loops; i++) Average += rollExpDist()/(double)Loops;
    return Average;
}
double RandomDice::rollExpDist(){
    static std::exponential_distribution<double> distribution(1.);
    return distribution(generator);
}
double RandomDice::rollExpDist(double Lambda){
    static std::exponential_distribution<double> distribution(Lambda);
    return distribution(generator);
}

double RandomDice::rollContUnifDist(double tmp){
    std::uniform_real_distribution<double> distribution(0,tmp);
//    std::uniform_real_distribution<double> UnifDist();
//    std::uniform_real_distribution<double>::param_type parameter(0,tmp);
//    UnifDist.param(parameter);
    return distribution(generator);
}
double RandomDice::rollDiscrUnifDist(int tmp)
{
    if(tmp > 0){
        std::uniform_int_distribution<int> distribution(1, tmp);
        return distribution(generator);
    }
    else return 0;
}
