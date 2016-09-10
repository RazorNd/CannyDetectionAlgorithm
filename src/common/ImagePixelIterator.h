#ifndef IMAGEPIXELITERATOR_H
#define IMAGEPIXELITERATOR_H

#include <QImage>

class ImagePixelIterator
{
public:
    ImagePixelIterator(const QImage *image);

    ImagePixelIterator &operator ++ ();
    ImagePixelIterator &operator -- ();

    QRgb operator * () const;

    ImagePixelIterator &operator += (size_t position);
    ImagePixelIterator &operator -= (size_t position);

    ImagePixelIterator operator + (size_t position) const;
    ImagePixelIterator operator - (size_t position) const;

    size_t operator - (const ImagePixelIterator &other) const;

    bool operator == (const ImagePixelIterator &other) const;
    bool operator != (const ImagePixelIterator &other) const;

    ImagePixelIterator end() const;

protected:
    size_t rowCount() const;
    size_t columnCount() const;
    QPoint currentPosition() const;

private:
    size_t position = 0;
    const QImage *image;
};

#endif // IMAGEPIXELITERATOR_H
