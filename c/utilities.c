
// This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


/*

These are my favorite macros and other utility functions I frequently need in both C and C++.

See the .h file for details.

*/

#include "utilities.h"

#include <math.h> // fabs() [for double], fabsf() [for float]


// floating point comparisons

/// @brief      Get a scaled version of epsilon, which is scaled to work with any size
///             `a` and `b` floating point values so that it doesn't fall out in numerical error.
////
// Todo: rename to `get_epsilon_scaled_float()`??
// For background info behind this, see: http://realtimecollisiondetection.net/blog/?p=89
static float scale_float_epsilon(float a, float b, float epsilon)
{
    // float scaling_factor;

    // // For very large `a` and `b`, scale epsilon UP, or else it will eventually become so small
    // // relative to `a` and `b` that if falls out in the numerical error.
    // scaling_factor = MAX(fabsf(a), fabsf(b));

    // // For very small `a` and `b`, however, ensure `scaling_factor` doesn't get too small, or again,
    // // `epsilon_scaled` will fall out in numerical error, so let's clip the scaling factor to be a
    // // minimum value of 1.0f, which means the exact `epsilon` passed in is used.
    // scaling_factor = MAX(scaling_factor, (float)1.0);

    /////// TODO: clean this up; apply to the double func below too.

    // The end result is that you have `scaling_factor = MAX(fabsf(a), fabsf(b), (float)1.0)`.

    float scaling_factor = MAX3(fabsf(a), fabsf(b), (float)1.0);
    float epsilon_scaled = epsilon*scaling_factor;
    return epsilon_scaled;
}

// For background info behind this, see: http://realtimecollisiondetection.net/blog/?p=89
static double scale_double_epsilon(double a, double b, double epsilon)
{
    double scaling_factor;

    // For very large `a` and `b`, scale epsilon UP, or else it will eventually become so small
    // relative to `a` and `b` that if falls out in the numerical error.
    scaling_factor = MAX(fabs(a), fabs(b));

    // For very small `a` and `b`, however, ensure `scaling_factor` doesn't get too small, or again,
    // `epsilon_scaled` will fall out in numerical error, so let's clip the scaling factor to be a
    // minimum value of 1.0f, which means the exact `epsilon` passed in is used.
    scaling_factor = MAX(scaling_factor, (double)1.0);

    // The end result is that you have `scaling_factor = MAX(fabs(a), fabs(b), (double)1.0)`.

    double epsilon_scaled = epsilon*scaling_factor;
    return epsilon_scaled;
}


bool is_float_eq(float a, float b, float epsilon)
{
    float diff = a - b; // note: `-diff` is the same as `b - a`
    float epsilon_scaled = scale_float_epsilon(a, b, epsilon);

    return diff <= epsilon_scaled && -diff <= epsilon_scaled;
}
bool is_double_eq(double a, double b, double epsilon)
{

}

bool is_float_ne(float a, float b, float epsilon)
{
    /////
    // float diff = a - b; // note: `-diff` is the same as `b - a`
    // float epsilon_scaled = scale_float_epsilon(a, b, epsilon);

    // return diff >= epsilon_scaled || -diff >= epsilon_scaled;

    return !is_float_eq(a, b, epsilon);
}
bool is_double_ne(double a, double b, double epsilon)
{

}

bool is_float_lt(float a, float b, float epsilon)
{
    return a < b - scale_float_epsilon(a, b, epsilon);
}
bool is_double_lt(double a, double b, double epsilon)
{

}

bool is_float_le(float a, float b, float epsilon)
{
    return a <= b + scale_float_epsilon(a, b, epsilon);
}
bool is_double_le(double a, double b, double epsilon)
{

}

bool is_float_gt(float a, float b, float epsilon)
{
    return a > b + scale_float_epsilon(a, b, epsilon);
}
bool is_double_gt(double a, double b, double epsilon)
{

}

bool is_float_ge(float a, float b, float epsilon)
{
    return a >= b - scale_float_epsilon(a, b, epsilon);
}
bool is_double_ge(double a, double b, double epsilon)
{

}


// From Arduino's WMath.cpp:
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void* utils_get_aligned_address(void* base_addr, size_t alignment)
{
    if ((size_t)base_addr % alignment == 0)
    {
        // `base_addr` is already aligned
        return base_addr;
    }

    // Else we must force `base_addr` to become aligned
    void* aligned_addr = (void*)((size_t)base_addr + (alignment - (size_t)base_addr % alignment));
    return aligned_addr;
}

uint64_t millis()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    uint64_t ms = SEC_TO_MS((uint64_t)ts.tv_sec) + NS_TO_MS((uint64_t)ts.tv_nsec);
    return ms;
}

uint64_t micros()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    uint64_t us = SEC_TO_US((uint64_t)ts.tv_sec) + NS_TO_US((uint64_t)ts.tv_nsec);
    return us;
}

uint64_t nanos()
{
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    uint64_t ns = SEC_TO_NS((uint64_t)ts.tv_sec) + (uint64_t)ts.tv_nsec;
    return ns;
}

int utils_rand(int min, int max)
{
    static bool first_run = true;
    if (first_run)
    {
        // seed the pseudo-random number generator with the seconds time the very first run
        time_t time_now_sec = time(NULL);
        srand(time_now_sec);
        first_run = false;
    }

    int range = max - min + 1;
    int random_num = rand();  // random num from 0 to RAND_MAX, inclusive

    if (range > RAND_MAX)
    {
        static_assert(
            sizeof(long int) > sizeof(int),
            "This must be true or else the below mapping/scaling may have undefined overflow "
            "and not work properly. In such a case, try casting to `long long int` instead of "
            "just `long int`, and update this static_assert accordingly.");

        random_num = UTILS_MAP((long int)random_num, (long int)0, (long int)RAND_MAX, (long int)min,
                               (long int)max);
        return random_num;
    }

    // This is presumably a faster approach than the map/scaling function above, so do this faster
    // approach below whenever you don't **have** to do the more-complicated approach above.
    random_num %= range;
    random_num += min;

    return random_num;
}
