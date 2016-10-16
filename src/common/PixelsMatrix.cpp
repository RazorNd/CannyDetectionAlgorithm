#include "PixelsMatrix.h"

PixelsMatrix::PixelsMatrix(QSize size):
    size(size)
{
    const size_t s = static_cast<size_t>(size.width() * size.height());
    data.resize(s);
}

PixelsMatrix::pixel_t &PixelsMatrix::operator[](const int i)
{
    return data[static_cast<size_t>(i)];
}

const PixelsMatrix::pixel_t &PixelsMatrix::operator[](const int i) const
{
    return data[static_cast<size_t>(i)];
}

QImage PixelsMatrix::toImage() const
{
    QImage image(size, QImage::Format_RGB32);
    const int nx = image.size().width(), ny = image.size().height();

    size_t i = 0;
    for(int x = 0; x < nx; x++)
    {
        for(int y = 0; y < ny; y++, i++)
        {
//            int value = static_cast<int>(data[i]);
//            image.setPixelColor(x, y, QColor::fromHsv(0, 0, 255 - value, 0));
            image.setPixelColor(x, y, QColor::fromHsv(0, 0, 255 - data[i], 0));
        }
    }
    return image;
}

PixelsMatrix PixelsMatrix::fromImage(const QImage &image, std::function<int(QRgb)> mapFunction)
{
    PixelsMatrix out(image.size());

    const int nx = image.size().width(), ny = image.size().height();

    int i = 0;
    for(int x = 0; x < nx; x++)
    {
        for(int y = 0; y < ny; y++, i++)
        {
            out[i] = static_cast<PixelsMatrix::pixel_t>(mapFunction(image.pixel(x, y)));
        }
    }
    return out;
}

int toGray(QRgb in)
{
    return qGray(in);
}
