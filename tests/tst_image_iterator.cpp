#include <QtTest>
#include "ImagePixelIterator.h"

class PixelImageIteratorTest : public QObject
{
    Q_OBJECT
public:

private slots:
    void iterateTest();
    void endTest();
};

void PixelImageIteratorTest::iterateTest()
{
    QImage image(2, 2, QImage::Format_RGB32);
    image.setPixelColor(1, 0, Qt::red);

    ImagePixelIterator it(&image);
    it += 2;

    QCOMPARE(QColor(*it), QColor(Qt::red));
}

void PixelImageIteratorTest::endTest()
{
    QImage image(2, 2, QImage::Format_RGB32);
    image.setPixelColor(1, 0, Qt::red);

    ImagePixelIterator it(&image);
    auto end = it.end();

    QVERIFY(it != end);

    size_t dif = end - it;

    QCOMPARE(dif, 4ul);

    it += dif;
    QVERIFY(it == end);
}

QTEST_MAIN(PixelImageIteratorTest)
#include "tst_image_iterator.moc"
