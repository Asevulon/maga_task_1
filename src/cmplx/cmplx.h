#pragma once
#include <cmath>
#include <vector>

class cmplx
{
public:
    double re;
    double im;

    cmplx() { re = im = 0.; }
    cmplx(const cmplx &src)
    {
        re = src.re;
        im = src.im;
    }
    cmplx(double x, double y)
    {
        re = x;
        im = y;
    }
    cmplx &operator=(cmplx &c)
    {
        re = c.re;
        im = c.im;
        return *this;
    }
    cmplx &operator=(cmplx &&c)
    {
        re = c.re;
        im = c.im;
        return *this;
    }
};

inline cmplx operator*(const cmplx &x, const cmplx &y)
{
    return cmplx(x.re * y.re - x.im * y.im,
                 x.re * y.im + y.re * x.im);
}
inline cmplx operator/(const cmplx &x, const cmplx &y)
{
    cmplx z;
    double y2 = y.re * y.re + y.im * y.im;
    if (y2 < 10e-40)
        return z;
    z.re = (x.re * y.re + x.im * y.im) / y2;
    z.im = (y.re * x.im - x.re * y.im) / y2;
    return z;
}
inline cmplx operator/(const cmplx &x, double y)
{
    cmplx z;
    if (y < 10e-40)
        return z;
    z.re = x.re / y;
    z.im = x.im / y;
    return z;
}
inline cmplx operator+(const cmplx &x, const cmplx &y)
{
    cmplx z;
    z.re = x.re + y.re;
    z.im = x.im + y.im;
    return z;
}
inline cmplx operator-(const cmplx &x, const cmplx &y)
{
    cmplx z;
    z.re = x.re - y.re;
    z.im = x.im - y.im;
    return z;
}
inline double abs(const cmplx &x)
{
    return sqrt(x.re * x.re + x.im * x.im);
}

void fourea(std::vector<cmplx> &F, double is);

template <template <typename...> typename container_type>
container_type<double> cmplx_re(container_type<cmplx> &src)
{
    container_type<double> res;
    for (auto &item : src)
        res.emplace_back(item.re);
    return res;
}
template <template <typename...> typename container_type>
container_type<double> cmplx_im(container_type<cmplx> &src)
{
    container_type<double> res;
    for (auto &item : src)
        res.emplace_back(item.im);
    return res;
}