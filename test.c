/**
 * @file    test.c - Main function for testing DSs
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-10-06
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include "./Vector/vector.h"

int main()
{
    vector v;
    vector_init(&v, sizeof(char*), 1);

    printf("Initial size:     %llu\n", v.size(&v));
    printf("Initial capacity: %llu\n\n", v.capacity(&v));

    printf("Is push back ok?  %llu\n", v.push_back(&v, (char*) "123456789\0"));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n\n", v.capacity(&v));

    printf("Is push back ok?  %llu\n", v.push_back(&v, (char*) "2345678\0"));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n\n", v.capacity(&v));

    printf("Is push back ok?  %llu\n", v.push_back(&v, (char*) "3456789\0"));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n\n", v.capacity(&v));

    int i;
    for (i = 0; i < v.size(&v); i++)
    {
        printf("v[%d] = %s\n", i, (char*) v.at(&v, i));
    }

    v.clear(&v);
    v.free(&v);

    return 0;
}