# `PixelsMatrix`

Класс для внутреннего представления значения яркости пикселей:

```C++
class PixelsMatrix
{
public:
    typedef short pixel_t;

    const static pixel_t MAX_BRIGHTNESS = 255;

    PixelsMatrix(QSize size);
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
```

Содержит методы для получения и модификации значений конретных пикселей:

```C++
pixel_t &operator[] (const int i);
const pixel_t &operator[] (const int i) const;
```

Метод преобразования из внутреннего представления к классу `QImage`

```C++
QImage PixelsMatrix::toImage() const
{
    QImage image(size, QImage::Format_RGB32);
    const int nx = image.size().width(), ny = image.size().height();

    size_t i = 0;
    for(int x = 0; x < nx; x++)
    {
        for(int y = 0; y < ny; y++, i++)
        {
            image.setPixelColor(x, y, QColor::fromHsv(0, 0, 255 - data[i], 0));
        }
    }
    return image;
}
```

А также статический метод создания `PixelsMatrix` из класса `QImage`

```C++
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
```
где используется функциональный объект для преобразования RGB значения к `pixel_t`. По умолчанию используется фунция преобразования к градациям серого `toGray`.



