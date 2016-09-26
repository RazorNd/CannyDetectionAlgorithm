#include <QString>
#include <QtTest>
#include <QCoreApplication>

class RangeIteratorTest : public QObject
{
    Q_OBJECT

public:
    RangeIteratorTest(){};

private Q_SLOTS:
    void iteratorTest_data();
    void iteratorTest();
};

void RangeIteratorTest::iteratorTest_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void RangeIteratorTest::iteratorTest()
{
    QFETCH(QString, data);
    QVERIFY2(false, "Failure");
}

QTEST_MAIN(RangeIteratorTest)

#include "tst_rangeiteratortest.moc"
