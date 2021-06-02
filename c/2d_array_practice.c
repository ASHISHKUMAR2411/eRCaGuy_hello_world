/*

This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
www.ElectricRCAircraftGuy.com
2 June 2021

Learn and practice a few ways to use and pass multi-dimensional (ex: 2D) arrays in C.

I'm trying to help someone on Stack Overflow...
See: https://stackoverflow.com/questions/67811354/passing-a-pointer-to-array-to-my-function

To compile and run (assuming you've already `cd`ed into this dir):
1. In C:
    mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj 2d_array_practice.c \
    -o bin/2d_array_practice && bin/2d_array_practice
2. In C++
    mkdir -p bin && g++ -Wall -Wextra -Werror -O3 -std=c++17 -save-temps=obj 2d_array_practice.c \
    -o bin/2d_array_practice && bin/2d_array_practice

References:
1. The Q I'm answering: https://stackoverflow.com/questions/67811354/passing-a-pointer-to-array-to-my-function
1. [my ans to another Q] https://stackoverflow.com/questions/6567742/passing-an-array-as-an-argument-to-a-function-in-c/51527502#51527502
1. another Q & A (where I should answer instead): https://stackoverflow.com/questions/2828648/how-to-pass-a-multidimensional-array-to-a-function-in-c-and-c
1. https://www.geeksforgeeks.org/pass-2d-array-parameter-c/


--------------------------------
CONCLUSIONS AND RECOMMENDATIONS:
--------------------------------

ALL APPROACHES BELOW ARE VALID. However, here are my recommendations:

Assume you have the following array:
```
int arr[][2] =
{
    {1, 2},
    {5, 6},
    {7, 8},
};
```

1. If the 2D array is ALWAYS the same size each time (3x2 rows x columns in this case), do this:
    ```
    void printArray2(int (*a)[3][2]) {}
    // NB: `&` is REQUIRED! See my answer for why: https://stackoverflow.com/a/51527502/4561887
    printArray2(&arr);
    ```
2. If the 2D array has a VARIABLE number of rows, but a FIXED number of columns (2 in this case),
    do this:
    ```
    void printArray3(int a[][2], size_t num_rows) {}
    printArray3(arr, NUM_ROWS(arr));
    ```
3. If the 2D array has a VARIABLE number of rows AND a VARIABLE number of columns, do this (this
   approach is the most-versatile and is generally my go-to approach for multidimensional arrays):
    ```
    void printArray4(int *a, size_t num_rows, size_t num_cols) {}
    printArray4((int *)arr, NUM_ROWS(arr), NUM_COLS(arr));
    // OR: alternative call technique:
    printArray4(&arr[0][0], NUM_ROWS(arr), NUM_COLS(arr));
    ```

If you have the following array, however, you must do something different:
```
// Each row is an array of `int`s.
int row1[] = {1, 2};
int row2[] = {5, 6};
int row3[] = {7, 8};
// This is an array of `int *`, or "pointer to int". The blob of all rows together does NOT
// have to be in contiguous memory. This is very different from the `arr` array above, which
// contains all data in contiguous memory.
int* all_rows[] = {row1, row2, row3};
```

4. If the 2D array is actually built up of a bunch of ptrs to other arrays (as shown just above),
   do this:
    ```
    void printArray5(int* a[], size_t num_rows, size_t num_cols) {}
    printArray5(all_rows, ARRAY_LEN(all_rows), ARRAY_LEN(row1));
    ```


*/

#include <stdint.h>
#include <stdio.h>

// Get the number of elements in any C array
// - from my repo here:
//   https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/utilities.h#L42
// - Usage example: [my own answer]:
//   https://arduino.stackexchange.com/questions/80236/initializing-array-of-structs/80289#80289
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))

/// Definitions: `rows` = "rows"; `cols` = "columns"

/// Get number of rows in a 2D array
#define NUM_ROWS(array_2d) ARRAY_LEN(array_2d)

/// Get number of columns in a 2D array
#define NUM_COLS(array_2d) ARRAY_LEN(array_2d[0])


/// Don't use this approach at all, ever. It has a superfluous `num_cols` parameter that we don't
/// actually need! (see the `printArray3` approach below instead for how we can get rid of this).
/// So, this approach is shown here for demonstration purposes only.
/// This works, but there's a better way we will do later.
void printArray1(int a[][2], size_t num_rows, size_t num_cols)
{
    printf("printArray1:\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        for (size_t col = 0; col < num_cols; col++)
        {
            printf("a[%zu][%zu]=%i ", row, col, a[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

/// Better way (WITH array size type safety on array size)
/// `a` here is a ptr to an array of size[3][2]. This **forces** type safety in C based on array
/// size. See my answer here: https://stackoverflow.com/a/51527502/4561887
/// I think this is overly-complicated, however (again, read my answer just above), so let's
/// do another approach later withOUT type safety.
void printArray2(int (*a)[3][2])
{
    printf("printArray2:\n");
    for (size_t row = 0; row < NUM_ROWS(*a); row++)
    {
        for (size_t col = 0; col < NUM_COLS(*a); col++)
        {
            printf("a[%zu][%zu]=%i ", row, col, (*a)[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

/// Better way (withOUT array size type safety on array size) (my preferred approach between this
/// one and the one above, UNLESS all arrays are the same size, in which case use the one above)
void printArray3(int a[][2], size_t num_rows)
{
    printf("printArray3:\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        for (size_t col = 0; col < NUM_COLS(a); col++)
        {
            printf("a[%zu][%zu]=%i ", row, col, a[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

/// Much more-versatile approach. (My overall preferred approach since it's the most-versatile).
/// NB: `a` is a pointer to the start of a contiguous 2D array of `int`s. So, treat it as such.
void printArray4(int *a, size_t num_rows, size_t num_cols)
{
    printf("printArray4:\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        int *row_start = &a[row*num_cols];

        for (size_t col = 0; col < num_cols; col++)
        {
            // NB: THIS PART IS VERY DIFFERENT FROM THE OTHERS! Notice `row_start[col]`.
            printf("a[%zu][%zu]=%i ", row, col, row_start[col]);
        }
        printf("\n");
    }
    printf("\n");
}


/// Now let's force some code into the mold (prototype) style the OP requested for completeness. `a`
/// here is different from all of the cases above. It is NOT a contiguous 2D array of `int`s;
/// rather, it is an array of pointers to ints, where each pointer in the array can be thought of as
/// a sub-array. Therefore, the length of the outer array is the number of rows, and the length of
/// each sub-array, or inner array, is the number of columns. Each sub-array (a single row of
/// `int`s) DOES have to be in contiguous memory, and the array of _pointers_ DOES have to be in
/// contiguous memory, but the actual _storage space_ for each row can be in NON-contiguous memory.
/// Again, this is VERY different from every other function above.
void printArray5(int* a[], size_t num_rows, size_t num_cols)
{
    printf("printArray5:\n");
    for (size_t row = 0; row < num_rows; row++)
    {
        int *row_start = a[row]; // VERY DIFFERENT FROM `printArray4` above!
        for (size_t col = 0; col < num_cols; col++)
        {
            // Identical to `printArray4` above.
            printf("a[%zu][%zu]=%i ", row, col, row_start[col]);
        }
        printf("\n");
    }
    printf("\n");
}




int main()
{
    printf("hello\n\n");

    int arr[][2] =
    {
        {1, 2},
        {5, 6},
        {7, 8},
    };

    printf("num_rows = ARRAY_LEN(arr) = %zu\n", ARRAY_LEN(arr));
    printf("num_cols = ARRAY_LEN(arr[0]) = %zu\n", ARRAY_LEN(arr[0]));
    printf("\n");
    printf("NUM_ROWS(arr) = %zu\n", NUM_ROWS(arr));
    printf("NUM_COLS(arr) = %zu\n", NUM_COLS(arr));
    printf("\n");

    printArray1(arr, NUM_ROWS(arr), NUM_COLS(arr));

    // Better way WITH array type safety on array size. Notice you MUST pass the **address** of the
    // array here! `&arr` is of type `int (*)[3][2]`, which means: "pointer to a 3x2 array of ints".
    // See my answer here (https://stackoverflow.com/a/51527502/4561887) under the section
    // "Forcing type safety on arrays in C" for an explanation of this for 1D arrays.
    printArray2(&arr);
    // Better way withOUT array type safety on array size (my preferred approach)
    printArray3(arr, NUM_ROWS(arr));

    // more-versatile approach (can handle 2D arrays of any arbitrary number of rows and cols)
    printArray4((int *)arr, NUM_ROWS(arr), NUM_COLS(arr));
    // OR: alternate way to call this function: get the address of the array (ie: a ptr to an int)
    // at [row, col] = [0, 0]
    printArray4(&arr[0][0], NUM_ROWS(arr), NUM_COLS(arr));


    // ===========================
    printf("Now let's force some code into the mold (prototype) style the OP requested, "
           "for completeness:\n\n");
    // ===========================

    // Each row is an array of `int`s.
    int row1[] = {1, 2};
    int row2[] = {5, 6};
    int row3[] = {7, 8};
    // This is an array of `int *`, or "pointer to int". The blob of all rows together does NOT
    // have to be in contiguous memory. This is very different from the `arr` array above, which
    // contains all data in contiguous memory.
    int* all_rows[] = {row1, row2, row3};

    printArray5(all_rows, ARRAY_LEN(all_rows), ARRAY_LEN(row1));


    return 0;
}


/*
SAMPLE OUTPUT (ran on an x86-64 little endian Linux Ubuntu 20.04 machine):

    eRCaGuy_hello_world/c$ mkdir -p bin && gcc -Wall -Wextra -Werror -O3 -std=c11 -save-temps=obj 2d_array_practice.c     -o bin/2d_array_practice && bin/2d_array_practice
    hello

    num_rows = ARRAY_LEN(arr) = 3
    num_cols = ARRAY_LEN(arr[0]) = 2

    NUM_ROWS(arr) = 3
    NUM_COLS(arr) = 2

    printArray1:
    a[0][0]=1 a[0][1]=2
    a[1][0]=5 a[1][1]=6
    a[2][0]=7 a[2][1]=8

    printArray2:
    a[0][0]=1 a[0][1]=2
    a[1][0]=5 a[1][1]=6
    a[2][0]=7 a[2][1]=8

    printArray3:
    a[0][0]=1 a[0][1]=2
    a[1][0]=5 a[1][1]=6
    a[2][0]=7 a[2][1]=8

    printArray4:
    a[0][0]=1 a[0][1]=2
    a[1][0]=5 a[1][1]=6
    a[2][0]=7 a[2][1]=8

    printArray4:
    a[0][0]=1 a[0][1]=2
    a[1][0]=5 a[1][1]=6
    a[2][0]=7 a[2][1]=8

    Now let's force some code into the mold (prototype) style the OP requested, for completeness:

    printArray5:
    a[0][0]=1 a[0][1]=2
    a[1][0]=5 a[1][1]=6
    a[2][0]=7 a[2][1]=8

*/
