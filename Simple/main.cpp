#include <cstdlib>
#include <cmath>
#include <cassert>
#include <numeric>
#include <QSize>
#include <QImage>


#define MAX_BRIGHTNESS 255

/*
 * Loading part taken from
 * http://www.vbforums.com/showthread.php?t=261522
 * BMP info:
 * http://en.wikipedia.org/wiki/BMP_file_format
 *
 * Note: the magic number has been removed from the bmpfile_header_t
 * structure since it causes alignment problems
 *     bmpfile_magic_t should be written/read first
 * followed by the
 *     bmpfile_header_t
 * [this avoids compiler-specific alignment pragmas etc.]
 */

class PixelsMatrix
{
public:
    typedef short int pixel_t;

    pixel_t* data = nullptr;
    QSize size;

    PixelsMatrix(const QSize &size):size(size)
    {
        allocateMemory();
    }
    ~PixelsMatrix()
    {
//        delete [] data;
    }
    PixelsMatrix(PixelsMatrix &&) = default;
    PixelsMatrix(const PixelsMatrix &) = delete;
    PixelsMatrix &operator = (const PixelsMatrix &) = delete;

    pixel_t &operator[] (int i)
    {
        return data[i];
    }
    const pixel_t &operator[] (int i) const
    {
        return data[i];
    }

    void clear()
    {
        std::fill(data, data + (size.width() * size.height()), 0);
    }

protected:
    void allocateMemory()
    {
        data = new pixel_t[size.width() * size.height()];
    }
private:
};


// Use short int instead `unsigned char' so that we can
// store negative values.


// if normalize is true, map pixels to range 0..MAX_BRIGHTNESS
template <int KernelSize>
PixelsMatrix &&convolution(const PixelsMatrix &in, const float kernel[], const bool normalize)
{
//    std::assert(KernelSize % 2 == 1);
    //@todo: привести в соответсвие
    //std::assert(nx > kn && ny > kn);
    const int nx = in.size.width(), ny = in.size.height();
    const int khalf = KernelSize / 2;
    float min = std::numeric_limits<float>::min(), max = -std::numeric_limits<float>::max();

    if (normalize)
        for (int m = khalf; m < nx - khalf; m++)
            for (int n = khalf; n < ny - khalf; n++) {
                float pixel = 0.0;
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
            float pixel = 0.0;
            size_t c = 0;
            for (int j = -khalf; j <= khalf; j++)
                for (int i = -khalf; i <= khalf; i++) {
                    pixel += in[(n - j) * nx + m - i] * kernel[c];
                    c++;
                }

            if (normalize)
                pixel = MAX_BRIGHTNESS * (pixel - min) / (max - min);
            out.data[n * nx + m] = static_cast<PixelsMatrix::pixel_t>(pixel);
        }
    return std::move(out);
}

/*
 * gaussianFilter:
 * http://www.songho.ca/dsp/cannyedge/cannyedge.html
 * determine size of kernel (odd #)
 * 0.0 <= sigma < 0.5 : 3
 * 0.5 <= sigma < 1.0 : 5
 * 1.0 <= sigma < 1.5 : 7
 * 1.5 <= sigma < 2.0 : 9
 * 2.0 <= sigma < 2.5 : 11
 * 2.5 <= sigma < 3.0 : 13 ...
 * kernelSize = 2 * int(2*sigma) + 3;
 */
template <int KernelSize>
PixelsMatrix &&gaussian_filter(const PixelsMatrix &in, const float sigma)
{
    using namespace std;
    const int n = KernelSize;
    const double mean = floor(n / 2.0);
    float kernel[n * n]; // variable length array

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

/*
 * Links:
 * http://en.wikipedia.org/wiki/Canny_edge_detector
 * http://www.tomgibara.com/computer-vision/CannyEdgeDetector.java
 * http://fourier.eng.hmc.edu/e161/lectures/canny/node1.html
 * http://www.songho.ca/dsp/cannyedge/cannyedge.html
 *
 * Note: T1 and T2 are lower and upper thresholds.
 */
PixelsMatrix canny_edge_detection(const PixelsMatrix &in, const int tmin, const int tmax, const float sigma)
{
    const int nx = in.size.width();
    const int ny = in.size.height();

    PixelsMatrix out = gaussian_filter<5>(in, sigma);

    const float Gx[] = {-1, 0, 1,
                        -2, 0, 2,
                        -1, 0, 1};

    PixelsMatrix after_Gx = convolution<3>(out, Gx, false);

    const float Gy[] = { 1, 2, 1,
                         0, 0, 0,
                        -1,-2,-1};

    PixelsMatrix after_Gy = convolution<3>(out, Gy, false);

    PixelsMatrix G(in.size);
    PixelsMatrix nms(in.size);
    for (int i = 1; i < nx - 1; i++)
        for (int j = 1; j < ny - 1; j++) {
            const int c = i + nx * j;
            // G[c] = abs(after_Gx[c]) + abs(after_Gy[c]);
            G[c] = static_cast<PixelsMatrix::pixel_t>(std::hypot(after_Gx[c], after_Gy[c]));
        }

    // Non-maximum suppression, straightforward implementation.
    for (int i = 1; i < nx - 1; i++)
        for (int j = 1; j < ny - 1; j++) {
            const int c = i + nx * j;
            const int nn = c - nx;
            const int ss = c + nx;
            const int ww = c + 1;
            const int ee = c - 1;
            const int nw = nn + 1;
            const int ne = nn - 1;
            const int sw = ss + 1;
            const int se = ss - 1;

            const float dir = (float)(std::fmod(std::atan2(after_Gy[c],
                                                 after_Gx[c]) + M_PI,
                                           M_PI) / M_PI) * 8;

            if (((dir <= 1 || dir > 7) && G[c] > G[ee] &&
                 G[c] > G[ww]) || // 0 deg
                ((dir > 1 && dir <= 3) && G[c] > G[nw] &&
                 G[c] > G[se]) || // 45 deg
                ((dir > 3 && dir <= 5) && G[c] > G[nn] &&
                 G[c] > G[ss]) || // 90 deg
                ((dir > 5 && dir <= 7) && G[c] > G[ne] &&
                 G[c] > G[sw]))   // 135 deg
                nms[c] = G[c];
            else
                nms[c] = 0;
        }

    int edges[nx * ny];
    std::fill(edges, edges + (nx * ny), 0);
    out.clear();

    // Tracing edges with hysteresis . Non-recursive implementation.
    int c = 1;
    for (int j = 1; j < ny - 1; j++)
        for (int i = 1; i < nx - 1; i++) {
            if (nms[c] >= tmax && out[c] == 0) { // trace edges
                out[c] = MAX_BRIGHTNESS;
                int nedges = 1;
                edges[0] = c;

                do {
                    nedges--;
                    const int t = edges[nedges];

                    int nbs[8]; // neighbours
                    nbs[0] = t - nx;     // nn
                    nbs[1] = t + nx;     // ss
                    nbs[2] = t + 1;      // ww
                    nbs[3] = t - 1;      // ee
                    nbs[4] = nbs[0] + 1; // nw
                    nbs[5] = nbs[0] - 1; // ne
                    nbs[6] = nbs[1] + 1; // sw
                    nbs[7] = nbs[1] - 1; // se

                    for (int k = 0; k < 8; k++)
                        if (nms[nbs[k]] >= tmin && out[nbs[k]] == 0) {
                            out[nbs[k]] = MAX_BRIGHTNESS;
                            edges[nedges] = nbs[k];
                            nedges++;
                        }
                } while (nedges > 0);
            }
            c++;
        }

    return out;
}

PixelsMatrix load(const QString &fileName)
{
    QImage image(fileName);

    PixelsMatrix out(image.size());

    const int nx = image.size().width(), ny = image.size().height();

    for(int x = 0, i = 0; x < nx; x++)
    {
        for(int y = 0; y < ny; y++, i++)
        {
            out[i] = static_cast<PixelsMatrix::pixel_t>(qGray(image.pixel(x, y)));
        }
    }
    return out;
}

bool save(const QString &fileName, const PixelsMatrix &in)
{
    QImage image(in.size, QImage::Format_RGB32);
    const int nx = image.size().width(), ny = image.size().height();

    for(int x = 0, i = 0; x < nx; x++)
    {
        for(int y = 0; y < ny; y++, i++)
        {
            int value = static_cast<int>(in[i]);
            image.setPixelColor(x, y, QColor::fromHsv(0, 0, 255 - value, 0));
//            image.setPixel(x, y, value <= 0);
        }
    }
    return image.save(fileName, nullptr, 100);
}

int main(const int argc, const char ** const argv)
{
    if (argc < 2) {
        printf("Usage: %s image.bmp\n", argv[0]);
        return 1;
    }

    const PixelsMatrix in = load(argv[1]);

    const PixelsMatrix out = canny_edge_detection(in, 45, 70, 1.0f);


    if (!save("out.png", out)) {
        fprintf(stderr, "main: PNG image not saved.\n");
        return 1;
    }
    return 0;
}
