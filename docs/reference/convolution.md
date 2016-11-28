# `convolution`

Функция вычисляющая свертку матрицы.

```C++
template<int KernelSize>
PixelsMatrix convolution(const PixelsMatrix &in, const double kernel[], bool normalize = false)
{
    const int nx = in.size.height(), ny = in.size.width();
    const int khalf = KernelSize / 2;
    double min = std::numeric_limits<double>::max(), max = std::numeric_limits<double>::min();

    if (normalize)
        for (int m = khalf; m < nx - khalf; m++)
            for (int n = khalf; n < ny - khalf; n++) {
                double pixel = 0.0;
                size_t c = 0;
                for (int j = -khalf; j <= khalf; j++)
                    for (int i = -khalf; i <= khalf; i++) {
                        pixel += in[(n - j) * nx + m - i] * kernel[c];
                        c++;
                    }
                if (pixel < min)
                    min = pixel;
                if (pixel > max)
                    max = pixel;
                }

    PixelsMatrix out(in.size);

    for (int m = khalf; m < nx - khalf; m++)
        for (int n = khalf; n < ny - khalf; n++) {
            double pixel = 0.0;
            size_t c = 0;
            for (int j = -khalf; j <= khalf; j++)
                for (int i = -khalf; i <= khalf; i++) {
                    pixel += in[(n - j) * nx + m - i] * kernel[c];
                    c++;
                }

            if (normalize)
                pixel = PixelsMatrix::MAX_BRIGHTNESS * (pixel - min) / (max - min);
            out[n * nx + m] = static_cast<PixelsMatrix::pixel_t>(pixel);
        }
    return out;
}
```

Свертка вычисляется проходя скользящим окном с ядром свертки по входной матрице суммируя произведение наложивщихся значений.

Третьим параметром фунции передается значение необходимо ли нормализоавть значения свертки. 
Если такая необходимость нужна, в начале выполняется проход по матрице для получения максимального и минимального значения. 
После чего выполняется второй проход, где учитываются максимальное и минимальное значение, 
а итоговое значение вычисляется по формуле `pixel = PixelsMatrix::MAX_BRIGHTNESS * (pixel - min) / (max - min);`