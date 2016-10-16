#include "SobelOperator.h"
#include "util.h"

PixelsMatrix SobelOperator::operator ()(const PixelsMatrix &in) const
{
    const int nx = in.size.height();
    const int ny = in.size.width();
    const static double GxKernel[] = {-1, 0, 1,
                                      -2, 0, 2,
                                      -1, 0, 1};
    const static double GyKernel[] = { 1, 2, 1,
                                       0, 0, 0,
                                       -1,-2,-1};

    PixelsMatrix Gx = convolution<3>(in, GxKernel);
    PixelsMatrix Gy = convolution<3>(in, GyKernel);

    PixelsMatrix G(in.size);
    for (int i = 1; i < nx - 1; i++)
        for (int j = 1; j < ny - 1; j++) {
            const int c = i + nx * j;
            G[c] = static_cast<PixelsMatrix::pixel_t>(std::sqrt(Gx[c] * Gx[c] + Gy[c] * Gy[c]));
        }

    // Non-maximum suppression, straightforward implementation.
    PixelsMatrix nms(in.size);
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

            const double dir = (std::fmod(std::atan2(Gy[c],
                                                 Gx[c]) + M_PI,
                                           M_PI) / M_PI) * 8;

            if (((dir <= 1 || dir > 7) && G[c] > G[ee] && G[c] > G[ww]) || // 0 deg
                ((dir > 1 && dir <= 3) && G[c] > G[nw] && G[c] > G[se]) || // 45 deg
                ((dir > 3 && dir <= 5) && G[c] > G[nn] && G[c] > G[ss]) || // 90 deg
                ((dir > 5 && dir <= 7) && G[c] > G[ne] && G[c] > G[sw]))   // 135 deg
                nms[c] = G[c];
            else
                nms[c] = 0;
        }
    return nms;
}
