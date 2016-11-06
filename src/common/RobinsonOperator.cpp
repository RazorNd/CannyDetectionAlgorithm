#include "RobinsonOperator.h"
#include "util.h"
#include <vector>

const double masks[8][9] = {
    {-1, 0, 1,
     -2, 0, 2,
     -1, 0, 1 },
    { 0, 1, 2,
      -1, 0, 1,
      -2,-1, 0 },
    { 1, 2, 1,
      0, 0, 0,
      -1,-2,-1 },
    { 2, 1, 0,
      1, 0,-1,
      0,-1,-2 },
    { 1, 0,-1,
      2, 0,-2,
      1, 0,-1 },
    { 0,-1,-2,
      1, 0,-1,
      2, 1, 0 },
    {-1,-2,-1,
     0, 0, 0,
     1, 2, 1 },
    {-2,-1, 0,
     -1, 0, 1,
     0, 1, 2 },
};

PixelsMatrix RobinsonOperator::operator ()(const PixelsMatrix &in) const
{
    const int nx = in.size.height();
    const int ny = in.size.width();

    GradientCalculator gradientCalculator(in.size);
    gradientCalculator(in);

    PixelsMatrix G = gradientCalculator.getGradient();
    GradientCalculator::direction_vector directions = gradientCalculator.getGradientDirection();

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

            const Direction dir = directions[c];

            if (((dir == Direction::ee || dir == Direction::ww) && G[c] > G[ee] && G[c] > G[ww]) || // 0 deg
                ((dir == Direction::ne || dir == Direction::sw) && G[c] > G[nw] && G[c] > G[se]) || // 45 deg
                ((dir == Direction::nn || dir == Direction::ss) && G[c] > G[nn] && G[c] > G[ss]) || // 90 deg
                ((dir == Direction::nw || dir == Direction::se) && G[c] > G[ne] && G[c] > G[sw]))   // 135 deg
                nms[c] = G[c];
            else
                nms[c] = 0;
        }

    return nms;
}

RobinsonOperator::GradientCalculator::GradientCalculator(const QSize size):
    gradient(size),
    gradientDirection(static_cast<size_t>(size.width() * size.height()))
{
}

void RobinsonOperator::GradientCalculator::operator()(const PixelsMatrix &in) const
{
    const int nx = in.size.height();
    const int ny = in.size.width();


    PixelsMatrix on_direction[8] = {
        convolution<3>(in, masks[Direction::ee]),
        convolution<3>(in, masks[Direction::ne]),
        convolution<3>(in, masks[Direction::nn]),
        convolution<3>(in, masks[Direction::nw]),
        convolution<3>(in, masks[Direction::ww]),
        convolution<3>(in, masks[Direction::sw]),
        convolution<3>(in, masks[Direction::ss]),
        convolution<3>(in, masks[Direction::se])
    };

    for (int i = 0; i < nx; i++)
        for (int j = 0; j < ny; j++) {
            const int c = i + nx * j;
            double max = 0.0;
            Direction maxDirection = Direction::nn;

            for (int currentDirection = 0; currentDirection <= Direction::se; currentDirection++) {
                if (on_direction[currentDirection][c] > max) {
                    max = on_direction[currentDirection][c];
                    maxDirection = static_cast<Direction>(currentDirection);
                }
            }

            gradient[c] = static_cast<PixelsMatrix::pixel_t>(max);
            gradientDirection[c] = maxDirection;
        }
}

PixelsMatrix RobinsonOperator::GradientCalculator::getGradient() const
{
    return std::move(gradient);
}

RobinsonOperator::GradientCalculator::direction_vector RobinsonOperator::GradientCalculator::getGradientDirection() const
{
    return std::move(gradientDirection);
}
