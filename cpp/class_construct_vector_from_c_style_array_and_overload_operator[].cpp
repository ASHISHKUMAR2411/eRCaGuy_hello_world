/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
22 Aug. 2022

Practice constructing a `std::vector<>` from a C-style array in C++.
STATUS: done!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# NB: you may need to use `-std=gnu++17` instead of `-std=c++17` in order to obtain extra GNU
# gcc features, including gcc extensions, POSIX cmds, and Linux sytem cmds.
# See: [my answer]: https://stackoverflow.com/a/71801111/4561887

# 1. In C++
g++ -Wall -Wextra -Werror -O3 -std=c++17 class_construct_vector_from_c_style_array_and_overload_operator[].cpp -o bin/a && bin/a
```

References:
1. [my answer] [probably deleted, so you will require > 10000 reputation to see it]
   https://stackoverflow.com/a/73450642/4561887
1. How to initialize std::vector from C-style array? - https://stackoverflow.com/a/2434404/4561887
1. Constructor #5 in this cppreference community wiki documentation here:
   https://en.cppreference.com/w/cpp/container/vector/vector
    > ```
    > template< class InputIt >
    > vector( InputIt first, InputIt last,
    >         const Allocator& alloc = Allocator() );
    > ```

*/

// C and C++ includes
#include <cstdio>
#include <iostream>
#include <vector>

// See: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/blob/master/c/utilities.h
#define ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))


class Test
{
private:
    std::vector<int> _data;

public:

    Test(int in_data[], size_t len):
        // See: https://stackoverflow.com/a/2434404/4561887
        _data(in_data, in_data + len)
    {
    }

    void printData()
    {
        for (int element : _data)
        {
            printf("%i  ", element);
        }
        printf("\n");
    }

    /// Write `value` to the element at index `i`
    /// - Note: cause the vector to automatically grow if the index would otherwise be
    ///   out of bounds.
    void setData(size_t i, int value)
    {
        if (i >= _data.size())
        {
            printf("setData(): Growing the vector from %zu to %zu elements.\n",
                _data.size(), i + 1);
            _data.resize(i + 1);
        }

        _data[i] = value;
    }

    /// Overload the `[]` operator to allow reading or writing directly from or to the
    /// private array in this class.
    /// See: https://en.cppreference.com/w/cpp/language/operators and search the page for
    /// "operator[]" and the "Array subscript operator" section.
    /// - Note: cause the vector to automatically grow if the index would otherwise be
    ///   out of bounds.
    int& operator[](std::size_t i)
    {
        if (i >= _data.size())
        {
            printf("operator[](): Growing the vector from %zu to %zu elements.\n",
                _data.size(), i + 1);
            _data.resize(i + 1);
        }

        return _data[i];
    }
};

int main()
{
    int data[] = {1, 2, 3};
    Test test(data, ARRAY_LEN(data));
    test.printData();

    // Update the array's data
    test.setData(0, 10);
    test.setData(1, 11);
    test.setData(2, 12);
    test.setData(3, 13); // causes the vector to automatically grow
    test.printData();
    test.setData(10, 99); // causes the vector to automatically grow
    test.printData();

    test[0] = 22;
    test[1] = 23;
    test[2] = 24;
    std::cout << "test[1] = " << test[1] << "\n";
    test.printData();
    test[12] = 33; // causes the vector to automatically grow
    test.printData();


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 class_construct_vector_from_c_style_array_and_overload_operator[].cpp -o bin/a && bin/a
    1  2  3
    setData(): Growing the vector from 3 to 4 elements.
    10  11  12  13
    setData(): Growing the vector from 4 to 11 elements.
    10  11  12  13  0  0  0  0  0  0  99
    test[1] = 23
    22  23  24  13  0  0  0  0  0  0  99
    operator[](): Growing the vector from 11 to 13 elements.
    22  23  24  13  0  0  0  0  0  0  99  0  33

*/
