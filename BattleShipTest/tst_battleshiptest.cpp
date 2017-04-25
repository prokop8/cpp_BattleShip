#include <QString>
#include <QtTest>

class BattleShipTest : public QObject
{
    Q_OBJECT

public:
    BattleShipTest();

private Q_SLOTS:
    void testCase1();
    void testCase1_data();
};

BattleShipTest::BattleShipTest()
{
}

void BattleShipTest::testCase1_data()
{
}

void BattleShipTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(BattleShipTest)

#include "tst_battleshiptest.moc"
