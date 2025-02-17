// Austin Henley and Stephen Marz
// See the explanation and benchmarks at http://austinhenley.com/blog/cosine.html
// Various methods of calculating cosine without math.h
// For educational purposes only :)

#include "costable_1.h"
#include "costable_0_1.h"
#include "costable_0_01.h"
#include "costable_0_001.h"
#include "costable_0_0001.h"
#include <math.h>

#define CONST_PI  3.14159265358979323846264338327950288419716939937510
#define CONST_2PI 6.28318530717958623199592693708837032318115234375000

#define modd(x, y) ((x) - (int)((x) / (y)) * (y))
#define lerp(w, v1, v2) ((1.0 - (w)) * (v1) + (w) * (v2))

double absd(double a) { *((unsigned long *)&a) &= ~(1UL << 63); return a; }

//
// Naive Taylor series functions.
//

double cos_taylor_literal_4terms_naive(double x)
{
    return 1 - ((x * x) / (2)) + ((x * x * x * x) / (24)) - ((x * x * x * x * x * x) / (720)) + ((x * x * x * x * x * x * x * x) / (40320));
}

double cos_taylor_literal_6terms_naive(double x)
{
    return 1 - ((x * x) / (2)) + ((x * x * x * x) / (24)) - ((x * x * x * x * x * x) / (720)) + ((x * x * x * x * x * x * x * x) / (40320)) - ((x * x * x * x * x * x * x * x * x * x) / (3628800)) + ((x * x * x * x * x * x * x * x * x * x * x * x) / (479001600));
}

// Taylor series with literals.

double cos_taylor_literal_6terms_2pi(double x)
{
    x = modd(x, CONST_2PI);
    return 1 - ((x * x) / (2)) + ((x * x * x * x) / (24)) - ((x * x * x * x * x * x) / (720)) + ((x * x * x * x * x * x * x * x) / (40320)) - ((x * x * x * x * x * x * x * x * x * x) / (3628800)) + ((x * x * x * x * x * x * x * x * x * x * x * x) / (479001600));
}

double cos_taylor_literal_6terms_pi(double x)
{
    x = modd(x, CONST_2PI);
    char sign = 1;
    if (x > CONST_PI)
    {
        x -= CONST_PI;
        sign = -1;
    }
    return sign * (1 - ((x * x) / (2)) + ((x * x * x * x) / (24)) - ((x * x * x * x * x * x) / (720)) + ((x * x * x * x * x * x * x * x) / (40320)) - ((x * x * x * x * x * x * x * x * x * x) / (3628800)) + ((x * x * x * x * x * x * x * x * x * x * x * x) / (479001600)));
}

double cos_taylor_literal_6terms(double x)
{
    x = modd(x, CONST_2PI);
    char sign = 1;
    if (x > CONST_PI)
    {
        x -= CONST_PI;
        sign = -1;
    }
    double xx = x * x;

    return sign * (1 - ((xx) / (2)) + ((xx * xx) / (24)) - ((xx * xx * xx) / (720)) + ((xx * xx * xx * xx) / (40320)) - ((xx * xx * xx * xx * xx) / (3628800)) + ((xx * xx * xx * xx * xx * xx) / (479001600)));
}

double cos_taylor_literal_10terms(double x)
{
    x = modd(x, CONST_2PI);
    char sign = 1;
    if (x > CONST_PI)
    {
        x -= CONST_PI;
        sign = -1;
    }
    double xx = x * x;

    return sign * (1 - ((xx) / (2)) + ((xx * xx) / (24)) - ((xx * xx * xx) / (720)) + ((xx * xx * xx * xx) / (40320)) - ((xx * xx * xx * xx * xx) / (3628800)) + ((xx * xx * xx * xx * xx * xx) / (479001600)) - ((xx * xx * xx * xx * xx * xx * xx) / (87178291200)) + ((xx * xx * xx * xx * xx * xx * xx * xx) / (20922789888000)) - ((xx * xx * xx * xx * xx * xx * xx * xx * xx) / (6402373705728000)) + ((xx * xx * xx * xx * xx * xx * xx * xx * xx * xx) / (2432902008176640000)));
}

//
// Taylor series with running product.
//

double cos_taylor_running_6terms(double x)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 6; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double cos_taylor_running_8terms(double x)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 8; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double cos_taylor_running_10terms(double x)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 10; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double cos_taylor_running_16terms(double x)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 16; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

double cos_taylor_running_yterms(double x, int y)
{
    int div = (int)(x / CONST_PI);
    x = x - (div * CONST_PI);
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;

    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= y; i++)
    {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

//
// Lookup table.
//

double cos_table_1(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_1[(int)(x + 0.5)];
}

double cos_table_0_1(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_1[(int)(x * 10 + 0.5)];
}


double cos_table_0_01(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_01[(int)(x * 100 + 0.5)];
}

double cos_table_0_001(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_001[(int)(x * 1000 + 0.5)];
}

double cos_table_0_0001(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    return costable_0_0001[(int)(x * 10000 + 0.5)];
}

//
// Lookup table with LERP.
//

double cos_table_1_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 1.0;
    int index = (int)i;
    return lerp(i - index,             /* weight      */
                costable_1[index],     /* lower value */
                costable_1[index + 1]  /* upper value */
                );
}

double cos_table_0_1_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 10.0;
    int index = (int)i;
    return lerp(i - index,               /* weight      */
                costable_0_1[index],     /* lower value */
                costable_0_1[index + 1]  /* upper value */
                );
}

double cos_table_0_01_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 100.0;
    int index = (int)i;
    return lerp(i - index,                /* weight      */
                costable_0_01[index],     /* lower value */
                costable_0_01[index + 1]  /* upper value */
                );
}

double cos_table_0_001_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 1000.0;
    int index = (int)i;
    return lerp(i - index,                 /* weight      */
                costable_0_001[index],     /* lower value */
                costable_0_001[index + 1]  /* upper value */
                );
}

double cos_table_0_0001_LERP(double x)
{
    x = absd(x);
    x = modd(x, CONST_2PI);
    double i = x * 10000.0;
    int index = (int)i;
    return lerp(i - index,                  /* weight      */
                costable_0_0001[index],     /* lower value */
                costable_0_0001[index + 1]  /* upper value */
                );
}

double cos_math_h(double x) {
    return cos(x);
}

// cubic curve
// input limit: -pi ~ pi
double fast_acc_sine(double x) {
  double y = x * (1.273239545 + -0.405284735 * absd(x));
  return y * (absd(y) * (0.0192 * absd(y) + 0.1951) + 0.7857);
}

// input limit: -pi-M_PI_2 ~ pi-M_PI_2
double fast_acc_cosine(double x) { return fast_acc_sine(x + M_PI_2); }

// input limit: -pi ~ pi
double fast_acc_cosine_v2(double x) {
  x = absd(x);
  double y = x * (0.636619772 + -0.101321184 * x);
  double y1 = y * (y * (0.0271529 * y + 0.275913066) + 1.111147596);
  return 1.0 - y1 * y1;
}

// quadratic curve
#define EXTRA_PRECISION
// -pi ~ pi
double fast_sine(double x) {
  const double B = 4 / M_PI;
  const double C = -4 / (M_PI * M_PI);
  double y = B * x + C * x * fabs(x);
#ifdef EXTRA_PRECISION
  //  const double Q = 0.775;
  const double P = 0.225;
  y = P * (y * fabs(y) - y) + y;  // Q * y + P * y * fabs(y), Q + P = 1
#endif
  return y;
}

// -pi-M_PI_2 ~ pi-M_PI_2
double fast_cosine(double x) { return fast_sine(x + M_PI_2); }