/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

Gabriel Staples
www.ElectricRCAircraftGuy.com
26 Sept. 2020

empirically_determine_max_thread_stack_size

You can run this as a C OR C++ program!

References:
1. https://stackoverflow.com/questions/1825964/c-c-maximum-stack-size-of-program/1826072#1826072
2. [MY OWN ANS]
   https://stackoverflow.com/questions/1825964/c-c-maximum-stack-size-of-program/64085509#64085509
3. https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html
    Originally by Bruno Haible, here, 24 Oct. 2009

I've added some minor changes to it for readability, clarity, and efficiency.

Build and run command:

As a C program:

    mkdir -p bin && \
    gcc -Wall -Werror -g3 -O3 -std=c11 -pthread -o bin/stack_size_gs_c \
    onlinegdb--empirically_determine_max_thread_stack_size_GS_version.c && \
    time bin/stack_size_gs_c

As a C++ program:

    mkdir -p bin && \
    g++ -Wall -Werror -g3 -O3 -std=c++17 -pthread -o bin/stack_size_gs_cpp \
    onlinegdb--empirically_determine_max_thread_stack_size_GS_version.c && \
    time bin/stack_size_gs_cpp

*******************************************************************************/

// =============== Program for determining the default thread stack size =========

// Modified by Gabriel Staples, 26 Sept. 2020

// Originally by Bruno Haible
// 24 Oct. 2009
// Source: https://lists.gnu.org/archive/html/bug-coreutils/2009-10/msg00262.html

#include <alloca.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h> // sleep

/// Thread function to repeatedly allocate memory within a thread, printing
/// the total memory allocated each time, until the program crashes. The last
/// value printed before the crash indicates how big a thread's stack size is.
///
/// Note: passing in a `uint32_t` as a `void *` type here is for practice,
/// to learn how to pass in ANY type to a func by using a `void *` parameter.
/// This is also the required function prototype, as required by the
/// `pthread_create()` function, for the callback function (this function)
/// passed to `pthread_create()`. See:
/// https://www.man7.org/linux/man-pages/man3/pthread_create.3.html
void* threadfunc(void* bytes_to_allocate_each_loop)
{
    const uint32_t BYTES_TO_ALLOCATE_EACH_LOOP =
            *(uint32_t*)bytes_to_allocate_each_loop;

    uint32_t bytes_allocated = 0;
    while (true)
    {
        printf("bytes_allocated = %u\n", bytes_allocated);
        fflush(stdout);
        // NB: it appears that you don't necessarily need `volatile` here,
        // but you DO definitely need to actually use (ex: write to) the
        // memory allocated by `alloca()`, as we do below, or else the
        // `alloca()` call does seem to get optimized out on some systems,
        // making this whole program just run infinitely forever without
        // ever hitting the expected segmentation fault.
        volatile uint8_t * byte_buff =
                (volatile uint8_t *)alloca(BYTES_TO_ALLOCATE_EACH_LOOP);
        byte_buff[0] = 0;
        bytes_allocated += BYTES_TO_ALLOCATE_EACH_LOOP;
    }
}

int main()
{
    const uint32_t BYTES_TO_ALLOCATE_EACH_LOOP = 128;

    pthread_t thread;
    pthread_create(&thread, NULL, threadfunc,
                   (void*)(&BYTES_TO_ALLOCATE_EACH_LOOP));
    while (true)
    {
        const unsigned int SLEEP_SEC = 10000;
        sleep(SLEEP_SEC);
    }

    return 0;
}



