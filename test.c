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
    vector_init(&v, sizeof(int*), 1);

    printf("Is vector empty:  %d\n", v.empty(&v));
    printf("Initial size:     %llu\n", v.size(&v));
    printf("Initial capacity: %llu\n\n", v.capacity(&v));

    int var = 2;
    int* ptr_int = &var;
    printf("Is vector empty:  %d\n", v.empty(&v));
    printf("Is push back ok?  %llu\n", v.push_back(&v, (int*) ptr_int));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n\n", *(int*) v.back(&v));

    var = 4;
    printf("Is vector empty:  %d\n", v.empty(&v));
    printf("Is push back ok?  %llu\n", v.push_back(&v, (int*) ptr_int));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n\n", *(int*) v.back(&v));

    var = 8;
    printf("Is vector empty:  %d\n", v.empty(&v));
    printf("Is push back ok?  %llu\n", v.push_back(&v, (int*) ptr_int));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n\n", *(int*) v.back(&v));

    var = 16;
    printf("Is vector empty:  %d\n", v.empty(&v));
    printf("Is push back ok?  %llu\n", v.push_back(&v, (int*) ptr_int));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n\n", *(int*) v.back(&v));

    var = 32;
    printf("Is vector empty:  %d\n", v.empty(&v));
    printf("Is push back ok?  %llu\n", v.push_back(&v, (int*) ptr_int));
    printf("Is shrink ok?     %d\n", v.shrink(&v));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n", *(int*) v.back(&v));
    printf("Item removed:     %d\n\n", *(int*) v.pop_back(&v));

    var = 64;
    printf("Is vector empty:  %d\n", v.empty(&v));
    printf("Is push back ok?  %llu\n", v.push_back(&v, (int*) ptr_int));
    printf("Is shrink ok?     %d\n", v.shrink(&v));
    printf("Current size:     %llu\n", v.size(&v));
    printf("Current capacity: %llu\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n\n", *(int*) v.back(&v));

    int i;
    for (i = 0; i < v.size(&v); i++)
    {
        printf("v[%d] = %d\n", i, *(int*) v.at(&v, i));
    }

    v.clear(&v);
    v.free(&v);

    return 0;
}