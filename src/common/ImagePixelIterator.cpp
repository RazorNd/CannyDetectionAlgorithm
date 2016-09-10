#include "ImagePixelIterator.h"

ImagePixelIterator::ImagePixelIterator(const QImage *image) :
    image(image)
{
}

ImagePixelIterator &ImagePixelIterator::operator ++()
{
    position++;
    return *this;
}

ImagePixelIterator &ImagePixelIterator::operator --()
{
    position--;
    return *this;
}

QRgb ImagePixelIterator::operator *() const
{
    return image->pixel(currentPosition());
}

ImagePixelIterator &ImagePixelIterator::operator +=(size_t position)
{
    this->position += position;
    return *this;
}

ImagePixelIterator &ImagePixelIterator::operator -=(size_t position)
{
    this->position -= position;
    return *this;
}

ImagePixelIterator ImagePixelIterator::operator +(size_t position) const
{
    ImagePixelIterator resut(image);
    return resut += position;
}

ImagePixelIterator ImagePixelIterator::operator -(size_t position) const
{
    ImagePixelIterator resut(image);
    return resut -= position;
}

size_t ImagePixelIterator::operator -(const ImagePixelIterator &other) const
{
    return position - other.position;
}

bool ImagePixelIterator::operator ==(const ImagePixelIterator &other) const
{
    return other.image == image && other.position == position;
}

bool ImagePixelIterator::operator !=(const ImagePixelIterator &other) const
{
    return !(other == *this);
}

ImagePixelIterator ImagePixelIterator::end() const
{
    ImagePixelIterator result(image);
    result.position = columnCount() * rowCount();
    return result;
}

size_t ImagePixelIterator::rowCount() const
{
    return static_cast<size_t>(image->height());
}

size_t ImagePixelIterator::columnCount() const
{
    return static_cast<size_t>(image->width());
}

QPoint ImagePixelIterator::currentPosition() const
{
    return QPoint(static_cast<int>(position / columnCount()),
                  static_cast<int>(position % columnCount()));
}
