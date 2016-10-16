#include <QtTest>
#include <QtConcurrent>

#include "ImagePixelIterator.h"

class PixelImageIteratorTest : public QObject
{
    Q_OBJECT
public:

private slots:
    void iterateTest();
    void endTest();
    void concurrentTest();
};

void PixelImageIteratorTest::iterateTest()
{
    QImage image(2, 2, QImage::Format_RGB32);
    image.setPixel(1, 0, qRgb(255, 0, 0));

    ImagePixelIterator it(&image);
    it += 2;

    QCOMPARE(*it, qRgb(255, 0, 0));
}

void PixelImageIteratorTest::endTest()
{
    QImage image(2, 2, QImage::Format_RGB32);
    image.setPixel(1, 0, Qt::red);

    ImagePixelIterator it(&image);
    auto end = it.end();

    QVERIFY(it != end);

    size_t dif = end - it;

    QCOMPARE(dif, 4ul);

    it += dif;
    QCOMPARE(it, end);
}

int gray(QRgb color)
{
    return qGray(color);
}

void PixelImageIteratorTest::concurrentTest()
{
    QImage image(2, 2, QImage::Format_RGB32);

    const QRgb pixels[4] = { qRgb(20, 60, 90), qRgb(87, 35, 47), qRgb(25, 240, 13), qRgb(167, 142, 15) };

    image.setPixel(0, 0, pixels[0]);
    image.setPixel(0, 1, pixels[1]);
    image.setPixel(1, 0, pixels[2]);
    image.setPixel(1, 1, pixels[3]);

    ImagePixelIterator it(&image);
    auto end = it.end();
    QVector<int> results = QtConcurrent::blockingMapped<QVector<int>>(it, end, gray);

    for(int i = 0; i < 4; i++)
    {
        QCOMPARE(results[i], qGray(pixels[i]));
    }
}

QTEST_MAIN(PixelImageIteratorTest)
#include "tst_image_iterator.moc"
