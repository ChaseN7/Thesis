#include <QString>
#include <QtTest>
#include <graphclass.h>
#include <traiteventmanager.h>
#include <cmath>

class TSS_UnitTestTest : public QObject
{
    Q_OBJECT

public:
    TSS_UnitTestTest();
    void validateTSSTestsData(TraitEventManager &Manager);
    void makeEvolutionVerifyConv(double iterations, TraitEventManager& Manager);
    void printAndCheckDifference(TraitEventManager Manager);

    const int speedIterations = 1000000;
private Q_SLOTS:
    void readAndClearStandardInput();

    void verifyTotalIntrinsicDeathRate(); // ------------ Section 1
    void verifyTotalCompDeathRate();
    void verifyTotalDeathRate();
    void verifyTotalBirthRate();
    void verifyEventRates();
    void sampleEventTimeTest();     // ------------ Section 2
    void sampleMutationTime();
//    void choseTraitToChangeTest();  // ------------ Section 3
//    void choseEventTypeTest();
//    void executeEventTypeOnTraitTest();
//    void changeATraitTest();

    void randomUniformDiceTesting();   // ---------- Section 4 - Final Test
    void returnStableMonomorphTest();
/*    void randomExpDiceTesting();
    void finalTestMono();
    void finalTestDimorph();
    void finalTestDimorph2();
    void testDataStorage();
    void testResizeDataVector();
    void testFitnessCalculation();

    void verifyExpectedTSS();*/       // ---------- Section 4 - Final Test

};

TSS_UnitTestTest::TSS_UnitTestTest()
{
}

void TSS_UnitTestTest::validateTSSTestsData(TraitEventManager& Manager)
{
    QCOMPARE(TraitClass::Size,3.);
    QCOMPARE(TraitClass::K,100.);
    /// 0.2 * 1/(TraitClass::K * sqrt(TraitClass::K))
    /// 0.2 * 1/(K * sqrt(K)) = 0.2 * 1/1000
    /// 0.0002
    QCOMPARE(TraitClass::Mutation,0.0002);
    QCOMPARE(Manager.Trait[0].BirthRate,6.);
    QCOMPARE(Manager.Trait[1].BirthRate,5.);
    QCOMPARE(Manager.Trait[2].BirthRate,4.);
    QCOMPARE(Manager.Trait[0].Members,2. * TraitClass::K);
    QCOMPARE(Manager.Trait[1].Members,0.* TraitClass::K);
    QCOMPARE(Manager.Trait[2].Members,1.* TraitClass::K);
    for(int i = 0; i < TraitClass::Size; ++i){
        QCOMPARE(Manager.Trait[i].DeathRate,2.);
        QCOMPARE(TraitClass::CompDeathRate[i][i],2. / TraitClass::K);
    }
}

// -------------------------- section 1: Rates ------------------------------------
/// Unit Tests for INPUT VALIDATION

void TSS_UnitTestTest::readAndClearStandardInput()
{
    TraitEventManager Manager("ValidateTSSTests.txt");
    validateTSSTestsData(Manager);
    Manager.clearData();
    QVERIFY(TraitClass::Size == 0.);
    QVERIFY(Manager.Trait.size() == 0.);
    QVERIFY(TraitClass::CompDeathRate.size() == 0.);
    QVERIFY(Manager.Trait.size() == 0.);
}

void TSS_UnitTestTest::verifyTotalIntrinsicDeathRate()
{
    TraitEventManager Manager("ValidateTSSTests.txt");
    for(int i = 0; i < TraitClass::Size; ++i){
        Manager.Trait[i].TotalDeathRate = 0;
        Manager.addTotalIntrisicDeathRateOf(i);
    }
    QCOMPARE(Manager.Trait[0].TotalDeathRate, 400.);
    QCOMPARE(Manager.Trait[1].TotalDeathRate, 0.);
    QCOMPARE(Manager.Trait[2].TotalDeathRate, 200.);

    Manager.clearData();
}

void TSS_UnitTestTest::verifyTotalCompDeathRate()
{
    TraitEventManager Manager("ValidateTSSTests.txt");
    for(int i = 0; i < TraitClass::Size; ++i){
        Manager.Trait[i].TotalDeathRate = 0;
        Manager.addTotalCompDeathRateOf(i);
    }
    QCOMPARE(Manager.Trait[0].TotalDeathRate, 1400.);   /// (200*2 + 100*3)*200*0.01 = 1400
    QCOMPARE(Manager.Trait[1].TotalDeathRate, 0.);      /// (200*1 + 100*2)*0 = 0
    QCOMPARE(Manager.Trait[2].TotalDeathRate, 400.);    /// (200*1 + 100*2)*100*0.01 = 400
    Manager.clearData();
}

void TSS_UnitTestTest::verifyTotalDeathRate()
{
    qDebug()<<"verify total death rates ...";
    TraitEventManager Manager("ValidateTSSTests.txt");

    time_t start = clock();
    for(int k = 0; k < speedIterations; ++k){
        Manager.calculateTotalDeathRateOf(0);
        Manager.calculateTotalDeathRateOf(1);
        Manager.calculateTotalDeathRateOf(2);
    }
    qDebug()<<"elapsed time:"<< clock()- start<<"ms";

    QCOMPARE(Manager.Trait[0].TotalDeathRate, 400.+ 1400.);
    qDebug()<<"trait 0 total death rate:"<< 400.+ 1400.;
    QCOMPARE(Manager.Trait[1].TotalDeathRate, 0.+ 0.);
    qDebug()<<"trait 1 total death rate:"<< 0.+ 0.;
    QCOMPARE(Manager.Trait[2].TotalDeathRate, 200.+400.);
    qDebug()<<"trait 2 total death rate:"<< 200.+400.;

    Manager.clearData();
}

void TSS_UnitTestTest::verifyTotalBirthRate()
{
    qDebug()<<"verify total birth rates ...";
    TraitEventManager Manager("ValidateTSSTests.txt");
    time_t start = clock();
    for(int k = 0; k < speedIterations; ++k)
        Manager.calculateTotalBirthRates();
    qDebug()<<"elapsed time:"<< clock()- start<<"ms";

    QVERIFY(TraitClass::Size == 3);
    /// 6 * 2 * 100 = 1200
    QCOMPARE(Manager.Trait[0].TotalBirthRate, 1200.);
    qDebug()<<"trait"<<0<<"total birth rate:"<<1200.<<"verified";
    double BirthRateOf1 = (Manager.Trait[0].TotalBirthRate + Manager.Trait[2].TotalBirthRate)
            * 0.2 * 1/(TraitClass::K * sqrt(TraitClass::K)) * 0.5;
    QCOMPARE(Manager.Trait[1].TotalBirthRate, BirthRateOf1);
    qDebug()<<"trait"<<1<<"total birth rate:"<< BirthRateOf1 <<"(only mutations) verified";
    QCOMPARE(Manager.Trait[2].TotalBirthRate, 400.);
    qDebug()<<"trait" << 2 << "total birth rate:" << 400 << "verified";
    Manager.clearData();
}

void TSS_UnitTestTest::verifyEventRates()
{
    TraitEventManager Manager("ValidateTSSTests.txt");
    Manager.calculateEventRates();
    // birth: 1200 + 0.16 + 400
    // death: 1800 + 0 + 600
    // = 4000.16
    qDebug()<<"verify: Total Event Rate = 4000.16 ...";
    QCOMPARE(TraitClass::TotalEventRate,4000.16);
    Manager.clearData();
}

//// ------------------ section 2: Sample Eventime -------------------


void TSS_UnitTestTest::sampleEventTimeTest()
{
    TraitEventManager Manager("ValidateTSSTests.txt");
    Manager.calculateEventRates();
    double actual = 0;
    double expected = 1./TraitClass::TotalEventRate;
    time_t start = clock();
    for(int i = 0; i < speedIterations; ++i){
        Manager.sampleEventTime();
        actual += Manager.Events.EventTimes;
    }
    qDebug()<<"elapsed time:"<< clock()- start<<"ms";
    actual /= speedIterations;
    actual = fabs(actual - expected);
    qDebug() << "error:" << actual/expected << "%";
    QVERIFY(actual < pow(10,-3.));
}

void TSS_UnitTestTest::sampleMutationTime()
{
    double time = 0;
    GraphClass Graph("ValidateTSSTests.txt", false);
    const int chosen = 1;
    for(int i = 0; i < 100000; ++i){
        int tmp = chosen;
        Graph.Manager.Trait[0].Members = 0;
        Graph.Manager.Trait[1].Members = 0;
        Graph.Manager.Trait[2].Members = 0;

        Graph.Manager.Trait[tmp].Members = Graph.getExpMonomorphOf(tmp) * TraitClass::K;

        Graph.Manager.calculateEventRates();
        Graph.iterateMutationPoint(time, tmp);
    }
    double actual = time/100000;
    double expected = 1/(Graph.Manager.Trait[chosen].TotalBirthRate * TraitClass::Mutation);
    if(chosen == TraitClass::Size - 1 || chosen == 0)
        expected *= 2.;
    qDebug() << "actual:" << actual << "expected:" << expected
             << "absolute:" << fabs((actual - expected)/expected);
    QVERIFY(fabs((actual - expected)/expected) < 0.05);
//    QCOMPARE(actual, expected);
}


//// ------------------ section 3: Changes -------------------------

//void TSS_UnitTestTest::choseTraitToChangeTest()
//{
//    TraitEventManager Manager("ValidateTests.txt");
//    Manager.calculateEventRates();
//    double iterations = 100000.;
//    std::vector<int> ChosenTraitHistogram(TraitClass::Size,0.);
//    for(int i = 0; i < iterations; i++){
//        Manager.choseTraitToChange();
//        ChosenTraitHistogram[Manager.Events.ChosenTrait]++;
//    }
//    for(int i = 0; i < TraitClass::Size; ++i){
//        double expected = Manager.Trait[i].TotalTraitRate/TraitClass::TotalEventRate;
//        double actual = ChosenTraitHistogram[i]/iterations;
//        qDebug()<< "verify chosen trait hist. of trait" << i << "~" << actual << ":" << expected << "...";
//        actual = fabs(actual - expected);
//        qDebug() << "error:" << actual/expected << "%";
//        QVERIFY(actual < 0.005);
//    }
//    Manager.clearData();
//}

//void TSS_UnitTestTest::choseEventTypeTest()
//{
//    TraitEventManager Manager("ValidateTests.txt");
//    Manager.calculateEventRates();
//    Manager.choseTraitToChange();

//    double actual = 0, itterations = 100000;
//    double expected = Manager.Trait[Manager.Events.ChosenTrait].TotalBirthRate
//                    /Manager.Trait[Manager.Events.ChosenTrait].TotalTraitRate;
//    for(int i = 0; i < itterations; i++){
//        Manager.choseEventType();
//        actual += Manager.Events.isBirth;
//    }
//    actual /= itterations;

//    qDebug()<< "trait" << Manager.Events.ChosenTrait;
//    qDebug()<< "verify expected event type ~" << actual << ":" << expected << "...";
//    actual = fabs(actual - expected);
//    qDebug() << "error:" << actual/expected << "%";
//    QVERIFY(actual < 0.0025);

//    Manager.clearData();
//}

//void TSS_UnitTestTest::executeEventTypeOnTraitTest()
//{

//    TraitEventManager Manager("ValidateTests.txt");
//    Manager.calculateEventRates();
//    Manager.sampleEventTime();
//    Manager.choseTraitToChange();
//    Manager.choseEventType();

//    int ChosenTrait = Manager.Events.ChosenTrait;
//    int MembersBefore = Manager.Trait[ChosenTrait].Members;
//    Manager.executeEventTypeOnTrait();

//    qDebug()<< "verify expected trait changes ...";
//    if(Manager.Events.isBirth){
//        QCOMPARE(Manager.Trait[ChosenTrait].Members,MembersBefore+1.);
//    }
//    else{
//        QVERIFY(MembersBefore > 0);
//        QCOMPARE(Manager.Trait[ChosenTrait].Members,MembersBefore-1.);
//    }

//    Manager.clearData();
//}

//void TSS_UnitTestTest::changeATraitTest()
//{
//    TraitEventManager Manager("ValidateTests.txt");
//    Manager.calculateEventRates();
//    Manager.sampleEventTime();
//    Manager.changeATrait();
//    int ChosenTrait = Manager.Events.ChosenTrait;
//    qDebug()<< "verify full step changes ...";
//    if(Manager.Events.isBirth)
//        QCOMPARE(Manager.Trait[ChosenTrait].Members,101.);
//    else
//        QCOMPARE(Manager.Trait[ChosenTrait].Members,99.);
//    Manager.clearData();
//}

//// ------------------ section 4: Utilities ------------------------

void TSS_UnitTestTest::randomUniformDiceTesting()
{
    GraphClass Graph("ValidateTSSTests.txt", false);
//    TraitEventManager Manager("ValidateTests.txt");
    double sum = 0, DiceParameter = 100, LowerBound = 80;
    double CDF = LowerBound/DiceParameter;
    /// CDF = F(800) = 0.8
    for(int i = 0; i < speedIterations; i++)
        sum += Graph.Manager.Dice.rollContUnifDist(DiceParameter) <= LowerBound ? 1 : 0;
    sum = fabs(sum/speedIterations - CDF)/CDF;
    QVERIFY(sum < 0.01);  /// 1% Abweichung
}


void TSS_UnitTestTest::returnStableMonomorphTest()
{
    GraphClass Graph("ValidateTSSTests.txt", false);
    QCOMPARE(Graph.getExpMonomorphOf(0), 2.);
    QCOMPARE(Graph.getExpMonomorphOf(1), 1.5);
    QCOMPARE(Graph.getExpMonomorphOf(2), 1.);
}

//void TSS_UnitTestTest::returnStableMonomorphTest()
//{
//    TraitEventManager Manager("ValidateTests.txt");
//}

//void TSS_UnitTestTest::randomExpDiceTesting()
//{
//    TraitEventManager Manager("ValidateTests.txt");
//    double LawOfLargeNum = 0, /*DiceResult,*/ lambda = 0.0379, expAverage = 1/lambda;

//    time_t start = clock();
//    for(int i = 0; i < speedIterations; i++)
//        LawOfLargeNum += Manager.Dice.rollExpDist(lambda);
//    qDebug()<<"elapsed time:"<< clock()- start<< "ms -- " << LawOfLargeNum/speedIterations << " -> " << expAverage;
//    LawOfLargeNum = fabs(LawOfLargeNum/speedIterations - expAverage)/expAverage;
//    QVERIFY(LawOfLargeNum < 0.01); /// 1% Abweichung
////    QCOMPARE(LawOfLargeNum/speedIterations, 1/lambda);
//}

//void TSS_UnitTestTest::finalTestMono()
//{
////    QSKIP("--- not ready for testing ---");
//    qDebug()<< "verify convergence for K = 1000";
//    TraitEventManager Manager("ValidateTests.txt");
//    makeEvolutionVerifyConv(speedIterations, Manager);
//    Manager.clearData();
//}

//void TSS_UnitTestTest::finalTestDimorph()
//{
//    qDebug()<< "verify convergence for K = 10 ...";
//    TraitEventManager Manager("ValidateTests.txt");
//    makeEvolutionVerifyConv(speedIterations, Manager);

//    Manager.clearData();
//}

//void TSS_UnitTestTest::finalTestDimorph2()
//{
//    qDebug()<< "verify convergence for K = 10000 ...";
//    TraitEventManager Manager("ValidateTests.txt");
//    makeEvolutionVerifyConv(speedIterations, Manager);
//    Manager.clearData();
//     qDebug()<< "finished";
//}

//void TSS_UnitTestTest::printAndCheckDifference(TraitEventManager Manager)
//{
//    if(TraitClass::Size == 2){
//        for(int i = 0; i < TraitClass::Size; ++i){
//            qDebug() << "trait " << i << " error:"
//                     << Manager.getKMembers(i) - Manager.retStableDimorphKOf(i)
//                     << "from Dimorph:" << Manager.retStableDimorphKOf(i);
//        }
//    }
//    else{
//        for(int i = 0; i < TraitClass::Size; ++i){
//            qDebug() << "trait " << i << " error:"
//                     << Manager.getKMembers(i) - Manager.retStableKMonoOf(i)
//                     << "from Monomorph:" << Manager.retStableKMonoOf(i);
//        }
//    }
//}

//void TSS_UnitTestTest::makeEvolutionVerifyConv(double iterations, TraitEventManager& Manager)
//{
//    time_t start = clock();
//    for(int i = 0; i < iterations; i++)
//        Manager.EvolutionStep();
//    qDebug() << "elapsed time:" << (clock() - start)/1000. << "s";
//    printAndCheckDifference(Manager);
//}

//void TSS_UnitTestTest::testDataStorage()
//{
//    QSKIP("--- is near doesnt trigger ---");
//    qDebug() << "verify Data Storage work...";
//    FileStreaming stream;
//    time_t start = clock();
//    TraitEventManager Manager("TestInstanceK10000.txt");
//    int lengh = stream.storeEvolution(Manager,10000);
//    QFile Storage("Storage.txt");
//    QTextStream out(&Storage);
//    if(!Storage.open(QFile::ReadOnly | QFile::Text))
//        qDebug()<< "File not found!";
//    QString line;
//    for(int i = 0; i < lengh; i++)
//        line = out.readLine();
//    qDebug()<< "last line: " << line;
//    qDebug()<< "terminated after: " << lengh;
//    qDebug() << "elapsed time:" << (clock() - start)/1000. << "s";
//    printAndCheckDifference(Manager);
//    Storage.close();
//    Manager.clearData();
//}

//void TSS_UnitTestTest::testResizeDataVector()
//{
//    GraphClass Graph("TestInit_stable", true);
//    qDebug() << "Make sure 100000000 iterations can be made...";
//    qDebug() << "dont forget to test Jumped Steps";
//    int maxIt = 100000000;
//    Graph.calcJumpedSteps(maxIt);
//    Graph.reserveSize(maxIt);
//    for(int i = 0; i < TraitClass::Size; ++i){
//        QCOMPARE(Graph.getTimesOf(i).capacity(),1000000);
//        QCOMPARE(Graph.getTraitHistOf(i).capacity(),1000000);
//    }
//}

//void TSS_UnitTestTest::testFitnessCalculation()
//{
//    GraphClass Graph1("ValidateFitness.txt", true);
//    QCOMPARE(TraitClass::Fitness[0][0],0.);
//    QCOMPARE(TraitClass::Fitness[0][1],5.);
//    QCOMPARE(TraitClass::Fitness[1][0],5.);
//    QCOMPARE(TraitClass::Fitness[1][1],0.);

//    GraphClass Graph("ValidateTests.txt", true);
//    double expected;
//    for(int i = 0; i < TraitClass::Size; ++i){
//        for(int j = 0; j < TraitClass::Size; ++j){
//            expected = Graph.Manager.Trait[j].BirthRate - Graph.Manager.Trait[i].DeathRate
//                    - TraitClass::CompDeathRate[i][j] * Graph.Manager.retStableKMonoOf(i);
//            QCOMPARE(TraitClass::Fitness[i][j],expected);
//        }
//    }
//}

//// ------------------ section 5: GraphClassTests ------------------------

//void TSS_UnitTestTest::verifyExpectedTSS()
//{
//    GraphClass Graph("TSS2",false);
//    QVector<double> Invasions(TraitClass::Size, 0);
//    int maxIt = 1000000;
//    Graph.calcJumpedSteps(maxIt);
//    Graph.reserveSize(maxIt);
////    Graph.makeTSSIterWithMutCount(maxIt, Invasions);
//    for(int i = 0; i < TraitClass::Size; ++i){
//        qDebug() << "Invasions from" << i << ":" << Invasions[i];
//    }
//}

QTEST_APPLESS_MAIN(TSS_UnitTestTest)

#include "tst_TSS_unittesttest.moc"
