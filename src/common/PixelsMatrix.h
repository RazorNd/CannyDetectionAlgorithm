#ifndef PIXELSMATRIX_H
#define PIXELSMATRIX_H

#include "common_global.h"
#include <vector>
#include <functional>
#include <QSize>
#include <QImage>

int toGray(QRgb in);

class PixelsMatrix
{
public:
    typedef short pixel_t;

    const static pixel_t MAX_BRIGHTNESS = 255;

    explicit PixelsMatrix(QSize size);
    PixelsMatrix(PixelsMatrix &&) = default;
    PixelsMatrix(const PixelsMatrix &) = delete;
    PixelsMatrix &operator = (const PixelsMatrix &) = delete;

    const QSize size;

    pixel_t &operator[] (const int i);
    const pixel_t &operator[] (const int i) const;

    QImage toImage() const;

    static PixelsMatrix fromImage(const QImage &in, std::function<int(QRgb)> mapFunction = toGray);
private:
    std::vector<pixel_t> data;
};

#endif // PIXELSMATRIX_H
