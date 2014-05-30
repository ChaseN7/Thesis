#include <QString>
#include <QtTest>
#include "traiteventmanager.h"
#include "graphclass.h"
#include "filestreaming.h"
#include "time.h"

class TraitEventManagerTest : public QObject
{
    Q_OBJECT

public:
    TraitEventManagerTest();


    void verifyWrittenData();
    void makeEvolutionVerifyConv(double iterations);
    void printAndCheckDifference();
private Q_SLOTS:
    void readAndClearStandardInput();

    void verifyTotalIntrinsicDeathRate(); // ------------ Section 1
    void verifyTotalCompDeathRate();
    void verifyTotalDeathRate();
    void verifyTotalBirthRate();
    void verifyEventRates();
    void sampleEventTimeTest();     // ------------ Section 2
    void verifyRandomnessOfTimeSamples();
    void choseTraitToChangeTest();  // ------------ Section 3
    void choseEventTypeTest();
    void executeEventTypeOnTraitTest();
    void changeATraitTest();

    void randomDicesTesting();   // ---------- Section 4 - Final Test
    void finalTestMono();
    void finalTestDimorph();
    void finalTestDimorph2();
    void testDataStorage();
    void testResizeDataVector();

private:
    TraitEventManager Manager;
};

TraitEventManagerTest::TraitEventManagerTest():
    Manager()
{
}


// -------------------------- section 1: Rates ------------------------------------

void TraitEventManagerTest::verifyWrittenData()
{
    QCOMPARE(TraitClass::Size,3.);
    QCOMPARE(TraitClass::Mutation,0.1);
    for(int i = 0; i < TraitClass::Size; ++i){
        QCOMPARE(Manager.Trait[i].BirthRate,10.);
        QCOMPARE(Manager.Trait[i].DeathRate,5.);
        QCOMPARE(TraitClass::CompDeathRate[i][i],2.);
    }
}

void TraitEventManagerTest::readAndClearStandardInput()
{
    Manager.initWithFile("ValidateTests.txt");
    verifyWrittenData();
    Manager.clearData();
    QVERIFY(TraitClass::Size == 0.);
    QVERIFY(Manager.Trait.size() == 0.);
    QVERIFY(TraitClass::CompDeathRate.size() == 0.);
    QVERIFY(Manager.Trait.size() == 0.);
}

void TraitEventManagerTest::verifyTotalIntrinsicDeathRate()
{
    Manager.initWithFile("ValidateTests.txt");
    for(int i = 0; i < TraitClass::Size; ++i){
        Manager.addTotalIntrisicDeathRateOf(i);
        QCOMPARE(Manager.Trait[i].TotalDeathRate, 500.);
    }
    Manager.clearData();
}

void TraitEventManagerTest::verifyTotalCompDeathRate()
{
    Manager.initWithFile("ValidateTests.txt");
    QVERIFY(TraitClass::Size == 3);
    for(int i = 0; i < TraitClass::Size; ++i)
        Manager.addTotalCompDeathRateOf(i);
    QCOMPARE(Manager.Trait[0].TotalDeathRate, 30000.);
    QCOMPARE(Manager.Trait[1].TotalDeathRate, 25000.);
    QCOMPARE(Manager.Trait[2].TotalDeathRate, 40000.);
    Manager.clearData();
}

void TraitEventManagerTest::verifyTotalDeathRate()
{
    Manager.initWithFile("ValidateTests.txt");
    QVERIFY(TraitClass::Size == 3);
    for(int i = 0; i < TraitClass::Size; ++i)
        Manager.calculateTotalDeathRateOf(i);
    qDebug()<<"verify total death rates ...";
    QCOMPARE(Manager.Trait[0].TotalDeathRate, 30000.+500.);
    qDebug()<<"trait"<<0<<"total death rate:"<<30000.+500.;
    QCOMPARE(Manager.Trait[1].TotalDeathRate, 25000.+500.);
    qDebug()<<"trait"<<1<<"total death rate:"<<25000.+500.;
    QCOMPARE(Manager.Trait[2].TotalDeathRate, 40000.+500.);
    qDebug()<<"trait"<<2<<"total death rate:"<<40000.+500.;
    Manager.clearData();
}

void TraitEventManagerTest::verifyTotalBirthRate()
{
    Manager.initWithFile("ValidateTests.txt");
    for(int i = 0; i < TraitClass::Size; ++i){
        Manager.calculateTotalBirthRates(i);
    }
    QVERIFY(TraitClass::Size == 3);
    qDebug()<<"verify total death rates ...";
    QCOMPARE(Manager.Trait[0].TotalBirthRate, 1050.);
    qDebug()<<"trait"<<0<<"total birth rate:"<<1050.<<"verified";
    QCOMPARE(Manager.Trait[1].TotalBirthRate, 1100.);
    qDebug()<<"trait"<<1<<"total birth rate:"<<1100.<<"verified";
    QCOMPARE(Manager.Trait[2].TotalBirthRate, 1050.);
    qDebug()<<"trait"<<2<<"total birth rate:"<<1050.<<"verified";
    Manager.clearData();
}

void TraitEventManagerTest::verifyEventRates()
{
    Manager.initWithFile("ValidateTests.txt");
    Manager.calculateEventRates();
    // birth: 3200
    // death: 96500
    // = 99700
    qDebug()<<"verify: Total Event Rate = 99700 ...";
    QCOMPARE(TraitClass::TotalEventRate,99700.);
    Manager.clearData();
}

// ------------------ section 2: Sample Eventime -------------------

void TraitEventManagerTest::verifyRandomnessOfTimeSamples()
{
    QSKIP("--- not ready for testing ---");
//    int itterations = 3;
//    for(int i = 0; i < itterations; ++i){
//        Manager.sampleEventTime();
//    }
//    for(int i = 1; i < itterations; ++i){
////        QVERIFY(Manager.Events.EventTimes[i-1] != Manager.Events.EventTimes[i]);
//    }
}

void TraitEventManagerTest::sampleEventTimeTest()
{
    QSKIP("--- not ready for testing ---");
//    Manager.Stream.initializeWithFile(QString::fromStdString("ValidateTests.txt"),Manager.Trait);
//    Manager.calculateEventRates();
//    qDebug()<<"verify randomness of timesamples...";
//    verifyRandomnessOfTimeSamples();
//    Manager.Trait.clear();
////    Manager.Events.EventTimes.clear();
}

// ------------------ section 3: Changes -------------------------

void TraitEventManagerTest::choseTraitToChangeTest()
{
    QSKIP("--- not ready for testing ---");
//    Manager.Stream.initializeWithFile(QString::fromStdString("ValidateTests.txt"),Manager.Trait);
//    Manager.calculateEventRates();
//    double iterations = 100000.;
//    std::vector<int> ChosenTraitHistory(TraitClass::Size,0.);
//    for(int i = 0; i < iterations; i++){
//        Manager.choseTraitToChange();
////        ChosenTraitHistory[Manager.Events.ChosenTrait[i]]++;
//    }
//    for(int i = 0; i < TraitClass::Size; ++i){
//        double expected = Manager.Trait[i].TotalTraitRate/TraitClass::TotalEventRate;
//        double actual = ChosenTraitHistory[i]/iterations;
//        qDebug()<< "verify chosen trait hist. of trait" << i << "~" << actual << ":" << expected << "...";
//        QVERIFY((actual > expected - 0.01) && (actual < expected + 0.01));
//    }
////    Manager.Events.EventTimes.clear();
//    Manager.clearData();
}

void TraitEventManagerTest::choseEventTypeTest()
{
    QSKIP("--- not ready for testing ---");
//    Manager.Stream.initializeWithFile(QString::fromStdString("ValidateTests.txt"),Manager.Trait);
//    Manager.calculateEventRates();
//    Manager.choseTraitToChange();

//    double actualBirths = 0, itterations = 100000;
//    for(int i = 0; i < itterations; i++){
//        Manager.choseEventType();
////        actualBirths += Manager.Events.isBirth[i];
//    }
//    actualBirths /= itterations;

////    int ChosenTrait = Manager.Events.ChosenTrait.back();
//    double TotBirthRate = Manager.Trait[ChosenTrait].TotalBirthRate;
//    double TotTraitRate = Manager.Trait[ChosenTrait].TotalTraitRate;
//    double ExpectedBirths = TotBirthRate/TotTraitRate;
//    qDebug()<< "for the chosen trait" << ChosenTrait << "we ...";
//    qDebug()<< "verify expected event type ~" << actualBirths << ":" << ExpectedBirths << "...";
//    QVERIFY((actualBirths > ExpectedBirths - 0.01) && (actualBirths < ExpectedBirths + 0.01));
////    Manager.Events.EventTimes.clear();
//    Manager.clearData();
}

void TraitEventManagerTest::executeEventTypeOnTraitTest()
{
    QSKIP("--- not ready for testing ---");

//    Manager.Stream.initializeWithFile(QString::fromStdString("ValidateTests.txt"),Manager.Trait);
//    Manager.calculateEventRates();
//    Manager.sampleEventTime();
//    Manager.choseTraitToChange();
//    Manager.choseEventType();

////    int ChosenTrait = Manager.Events.ChosenTrait.back();
//    int MembersBefore = Manager.Trait[ChosenTrait].Members;
//    Manager.executeEventTypeOnTrait();

//    qDebug()<< "verify expected trait changes ...";
////    if(Manager.Events.isBirth.back()){
////        QCOMPARE(Manager.Trait[ChosenTrait].Members,MembersBefore+1.);
////    }
//    else{
//        QVERIFY(MembersBefore > 0);
//        QCOMPARE(Manager.Trait[ChosenTrait].Members,MembersBefore-1.);
//    }
////    Manager.Events.EventTimes.clear();
//    Manager.clearData();
}

void TraitEventManagerTest::changeATraitTest()
{
    QSKIP("--- not ready for testing ---");
//    Manager.Stream.initializeWithFile(QString::fromStdString("ValidateTests.txt"),Manager.Trait);
//    Manager.calculateEventRates();
//    Manager.sampleEventTime();
//    Manager.changeATrait();
//    int ChosenTrait = Manager.Events.ChosenTrait.back();
//    qDebug()<< "verify full step changes ...";
//    if(Manager.Events.isBirth.back())
//        QCOMPARE(Manager.Trait[ChosenTrait].Members,101.);
//    else
//        QCOMPARE(Manager.Trait[ChosenTrait].Members,99.);
//    Manager.Events.EventTimes.clear();
//    Manager.clearData();
}

// ------------------ section 4: Utilities ------------------------

void TraitEventManagerTest::randomDicesTesting()
{
        double DiceResult = 0;
        double sum = 0;
        double DiceParameter = 1000;
        double LowerBound = 800;
        double compaire = LowerBound/DiceParameter;
        for(int i = 0; i < 10000; i++){
            DiceResult = Manager.Dice.rollContUnifDist(DiceParameter);
            if(DiceResult <= LowerBound)
                sum += 1;
        }
        sum/= 10000; //

        bool test = (sum < compaire +0.03) && (sum > compaire -0.03);
        QVERIFY(test);//QCOMPARE(sum, compaire);
}

void TraitEventManagerTest::finalTestMono()
{
    QSKIP("--- not ready for testing ---");
//    QString FName = "TestInit.txt";
//    Manager.Stream.initializeWithFile(FName, Manager.Trait);
//    double itterations = 100000.;
//    std::vector<double> average;
//    std::vector<double> TraitChanges;
//    for(int j = 0; j < TraitClass::Size; j++)
//        average.push_back(Manager.Trait[j].Members);
//    for(int i = 0; i < itterations; i++){
//        Manager.EvolutionStep();
//        average[Manager.Events.ChosenTrait[i]]
//                += Manager.Trait[Manager.Events.ChosenTrait[i]].Members;
//    }
//    TraitChanges = Manager.getAmoutOfTraitChanges();
//    for(int j = 0; j < TraitClass::Size; j++)
//        average[j] /= TraitChanges[j];
//    qDebug()<< "verify expected convergence of ...";
//    for(int j = 0; j < TraitClass::Size; j++)
//        qDebug()<< "trait" << j << "with" << average[j] << ":" << Manager.getStableDimorphStateOf(j) << "...";
//    Manager.clearData();
//    //QVERIFY((average > expected - 4.) && (average < expected + 4.));
}

void TraitEventManagerTest::finalTestDimorph()
{
    Manager.initWithFile("TestInstanceK10.txt");
    qDebug()<< "verify expected convergence for K = 10 ...";
    makeEvolutionVerifyConv(1000000);
    Manager.clearData();
}

void TraitEventManagerTest::finalTestDimorph2()
{
    Manager.initWithFile("TestInstanceK10000.txt");
    qDebug()<< "verify expected convergence for K = 10000 ...";
    makeEvolutionVerifyConv(1000000);
    Manager.clearData();
}

void TraitEventManagerTest::printAndCheckDifference()
{
    for(int i = 0; i < TraitClass::Size; ++i){
        qDebug() << "trait " << i << " error:"
                 << Manager.getKMembers(i) - Manager.retStableDimorphOf(i)
                 << "from" << Manager.retStableDimorphOf(i);
    }
}

void TraitEventManagerTest::makeEvolutionVerifyConv(double iterations)
{
    time_t start = clock();
    for(int i = 0; i < iterations; i++)
        Manager.EvolutionStep();
    qDebug() << "elapsed time:" << (clock() - start)/1000. << "s";
    printAndCheckDifference();
}

void TraitEventManagerTest::testDataStorage()
{
    FileStreaming stream;
    time_t start = clock();
    Manager.initWithFile("TestInstanceK10000.txt");
    int lengh = stream.storeEvolution(Manager,1000000);
    QFile Storage("Storage.txt");
    QTextStream out(&Storage);
    if(!Storage.open(QFile::ReadOnly | QFile::Text))
        qDebug()<< "File not found!";
    QString line;
    for(int i = 0; i < lengh; i++)
        line = out.readLine();
    qDebug()<< "last line: " << line;
    qDebug()<< "terminated after: " << lengh;
    qDebug() << "elapsed time:" << (clock() - start)/1000. << "s";
    printAndCheckDifference();
    Storage.close();
    Manager.clearData();
}

void TraitEventManagerTest::testResizeDataVector()
{
    GraphClass Graph("TestInit_stable", true);
    qDebug() << "Make sure 100000000 iterations can be made...";
    int maxIt = 100000000;
    Graph.calcJumpedSteps(maxIt);
    Graph.reserveSize(maxIt);
    for(int i = 0; i < TraitClass::Size; ++i){
        QCOMPARE(Graph.getTimesOf(i).capacity(),1000000);
        QCOMPARE(Graph.getTraitHistOf(i).capacity(),1000000);
    }
}

QTEST_APPLESS_MAIN(TraitEventManagerTest)

#include "tst_traiteventmanagertest.moc"

