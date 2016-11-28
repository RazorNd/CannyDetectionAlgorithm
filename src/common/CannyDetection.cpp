#include "CannyDetection.h"
#include "PixelsMatrix.h"
#include "util.h"

CannyDetection::CannyDetection()
{
}

CannyDetection::CannyDetection(int tMin, int tMax, double sigma):
    sigma(sigma), tMin(tMin), tMax(tMax)
{
}

double CannyDetection::getSigma() const
{
    return sigma;
}

void CannyDetection::setSigma(double value)
{
    sigma = value;
}

int CannyDetection::getTMin() const
{
    return tMin;
}

void CannyDetection::setTMin(int value)
{
    tMin = value;
}

int CannyDetection::getTMax() const
{
    return tMax;
}

void CannyDetection::setTMax(int value)
{
    tMax = value;
}

QImage CannyDetection::operator()(const QImage &image) const
{
    PixelsMatrix in = gaussianFilter<5>(PixelsMatrix::fromImage(image), sigma);
    PixelsMatrix nms = supressOperator(in);

    const int nx = in.size.height();
    const int ny = in.size.width();
    const size_t size = static_cast<size_t>(nx * ny);

    std::vector<int> edges(size);
    std::fill(edges.begin(), edges.end(), 0);

    PixelsMatrix out(in.size);    
    for (int j = 1; j < ny - 1; j++)
        for (int i = 1; i < nx - 1; i++) {
            const int c = i + nx * j;
            if (nms[c] >= tMax && out[c] == 0) { // trace edges
                out[c] = PixelsMatrix::MAX_BRIGHTNESS;
                size_t nedges = 1;
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

                    for (size_t k = 0; k < 8; k++)
                        if (nms[nbs[k]] >= tMin && out[nbs[k]] == 0) {
                            out[nbs[k]] = PixelsMatrix::MAX_BRIGHTNESS;
                            edges[nedges] = nbs[k];
                            nedges++;
                        }
                } while (nedges > 0);
            }

        }

    return out.toImage();
}

void CannyDetection::setSupressOperator(SupressOperatorType &&value)
{
    supressOperator.swap(value);
}
