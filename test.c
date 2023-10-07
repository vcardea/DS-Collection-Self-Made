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
    vector_init(&v);

    printf("Initial size: %d\n", v.size(&v));
    printf("Initial capacity [Bytes]: %d\n", v.capacity(&v));

    v.resize(&v, 10);
    printf("New size: %d\n", v.size(&v));
    printf("New capacity [Bytes]: %d\n", v.capacity(&v));

    v.push_back(&v, (void*) 5);
    printf("First element: %d\n", v.front(&v));

    return 0;
}