# `gaussianFilter`

Функция выполняюющая сглаживание от шумов изображения методом Гауса.

```C++
template <int KernelSize>
PixelsMatrix gaussianFilter(const PixelsMatrix &in, const double sigma)
{
    using namespace std;
    const int n = KernelSize;
    const double mean = floor(n / 2.0);
    double kernel[n * n];

    size_t c = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            kernel[c] = exp(-0.5 * (pow((i - mean) / sigma, 2.0) +
                                    pow((j - mean) / sigma, 2.0)))
                        / (2 * M_PI * sigma * sigma);
            c++;
        }

    return convolution<n>(in, kernel, true);
}
```

Функция вычисляет матрицу размера `KernelSize` с распеределением Гауса с заданной `sigma`. После чего вычисляется [свертка](convolution.md) входной матрицы, где ядром свертки выступает вычисленная матрица с Гаусовским распределением.