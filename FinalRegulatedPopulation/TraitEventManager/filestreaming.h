#ifndef FILESTREAMING_H
#define FILESTREAMING_H
#include <vector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "traiteventmanager.h"

class TraitEventManager;    // improve me with Include Guards please!
class FileStreaming
{
public:
    FileStreaming();
    FileStreaming(QString FName);
    ~FileStreaming();
    bool initializeWithFile(QString FName, std::vector<TraitClass> &Traits);
    void readSize_Mutation_K(QTextStream&in, std::vector<TraitClass> & Traits);
    void readMembersBirthsDeaths(QTextStream&in, std::vector<TraitClass> & Traits);
    void readCompetitionKernel(QTextStream&in);
    void clearTraitsAndRewriteWith(QFile& mFile, std::vector<TraitClass>& _Traits);
    static void appendToFileEndl(QString FileName, QString Value);

    bool writeLimitedData(TraitEventManager Manager);
    int storeEvolution(TraitEventManager Manager, int max_it);
    void copyEvolutionIntoData(TraitEventManager &Manager, QTextStream &in, double &ElapsedTime);
private:
    std::vector<TraitClass> Traits;
    QFile File;
};

#endif // FILESTREAMING_H
