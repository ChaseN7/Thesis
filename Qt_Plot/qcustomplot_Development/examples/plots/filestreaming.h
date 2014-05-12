#ifndef FILESTREAMING_H
#define FILESTREAMING_H
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "traitclass.h"

class FileStreaming
{
public:
    FileStreaming();
    void initializeWithFile(QString FName, std::vector<TraitClass> &Traits);
    void readSize_Mutation_K(QTextStream&in, std::vector<TraitClass> & Traits);
    void readMembersDeathsBirths(QTextStream&in, std::vector<TraitClass> & Traits);
    void readCompetitionKernel(QTextStream&in);
    void clearTraitsAndRewriteWith(QFile& mFile, std::vector<TraitClass>& _Traits);
private:
    std::vector<TraitClass> Traits;
};

#endif // FILESTREAMING_H
