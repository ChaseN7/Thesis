#include "filestreaming.h"
#include <QTextStream>
#include <QDebug>

FileStreaming::FileStreaming()
{
    //Traits = _Traits;
}

void FileStreaming::clearTraitsAndRewriteWith(QFile &mFile, std::vector<TraitClass>& _Traits)
{
    Traits.clear();
    QTextStream in(&mFile);
    readSize_Mutation_K(in, _Traits);
    readMembersDeathsBirths(in, _Traits);
    readCompetitionKernel(in);
    mFile.flush();
}

void FileStreaming::initializeWithFile(QString FName, std::vector<TraitClass> & _Traits)
{
    QFile mFile(FName);

    if(!mFile.open(QFile::ReadOnly)){
        qDebug() << "Datei konnte nicht geoffnet werden";
        return;
    }

    clearTraitsAndRewriteWith(mFile, _Traits);
    mFile.close();
}

void FileStreaming::readSize_Mutation_K(QTextStream & in, std::vector<TraitClass> & Traits)
{
    int size;
    in>>size;
    Traits.assign(size,TraitClass());
    TraitClass::setTraitSize(size);
    in>>TraitClass::K;
    if(TraitClass::K == 0) TraitClass::K = 1;
    in>>TraitClass::Mutation;
}

void FileStreaming::readMembersDeathsBirths(QTextStream &in, std::vector<TraitClass> & Traits)
{
    for(int i = 0; i < TraitClass::Size; i++){
        in>>Traits.at(i).Members;
        Traits.at(i).Members = Traits.at(i).Members*TraitClass::K;
        in>>Traits.at(i).BirthRate;
        in>>Traits.at(i).DeathRate;
    }
}

void FileStreaming::readCompetitionKernel(QTextStream &in)
{
    double p;
    for(int i = 0; i < TraitClass::Size; i++){
        for(int j = 0; j < TraitClass::Size; j++){

            in>>p;
            TraitClass::CompDeathRate.at(i).at(j) = p;
            p = TraitClass::K;
            TraitClass::CompDeathRate.at(i).at(j) /= TraitClass::K;
            p = TraitClass::CompDeathRate.at(i).at(j);
        }
    }
}
