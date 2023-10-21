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

    printf("Initial size:     %d\n", v.size(&v));
    printf("Initial capacity: %d\n", v.capacity(&v));
    printf("Is vector empty:  %d\n\n", v.empty(&v));

    int var = 2;
    int* ptr_int = &var;
    printf("Adding %d...\n", var);
    printf("Is push back ok?  %d\n", v.push_back(&v, (int*) ptr_int));
    printf("Current size:     %d\n", v.size(&v));
    printf("Current capacity: %d\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n", *(int*) v.back(&v));
    printf("Is vector empty:  %d\n\n", v.empty(&v));

    var = 4;
    printf("Adding %d...\n", var);
    printf("Is push back ok?  %d\n", v.push_back(&v, (int*) ptr_int));
    printf("Current size:     %d\n", v.size(&v));
    printf("Current capacity: %d\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n", *(int*) v.back(&v));
    printf("Is vector empty:  %d\n", v.empty(&v));
    printf("Is shrink ok?     %d\n\n", v.shrink(&v));

    printf("Pop back:         %d\n\n", *(int*) v.pop_back(&v));

    var = 8;
    printf("Adding %d...\n", var);
    printf("Is push back ok?  %d\n", v.push_back(&v, (int*) ptr_int));
    printf("Current size:     %d\n", v.size(&v));
    printf("Current capacity: %d\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n", *(int*) v.back(&v));
    printf("Is vector empty:  %d\n\n", v.empty(&v));

    var = 16;
    printf("Adding %d...\n", var);
    printf("Is insert ok?     %d\n", v.insert(&v, (int*) ptr_int, 1));
    printf("Current size:     %d\n", v.size(&v));
    printf("Current capacity: %d\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n", *(int*) v.back(&v));
    printf("Is vector empty:  %d\n\n", v.empty(&v));

    var = 2;
    printf("Removing %d...\n", var);
    printf("Is erase_elem ok? %d\n", v.erase_element(&v, (int*) ptr_int));
    printf("Current size:     %d\n", v.size(&v));
    printf("Current capacity: %d\n", v.capacity(&v));
    printf("Front:            %d\n", *(int*) v.front(&v));
    printf("Back:             %d\n", *(int*) v.back(&v));
    printf("Is vector empty:  %d\n\n", v.empty(&v));

    int i;
    for (i = 0; i < v.size(&v); i++)
    {
        printf("v[%d] = %d\n", i, *(int*) v.at(&v, i));
    }

    v.clear(&v);
    v.free(&v);

    return 0;
}