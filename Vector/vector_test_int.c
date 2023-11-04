/**
 * @file    vector.h - Dynamic array in C
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.2
 * @date    2023-11-04
 *
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include "./vector.h"

int main()
{
    vector v;
    vector_init(&v, sizeof(int*), sizeof(int), 1);

    printf("Initial size:             %5d\n", v.size(&v));
    printf("Initial capacity:         %5d\n", v.capacity(&v));
    printf("Empty?                    %5d\n", v.empty(&v));
    printf("item_size:                %5d\n", v.get_item_size(&v));
    printf("type_size:                %5d\n", v.get_type_size(&v));

    int i;
    int status;
    printf("\n");
    for (i = 1; i <= 6; ++i)
    {
        status = v.push_back(&v, &i);
        printf("v[%d] = %d (status %d)\n", i - 1, *(int*) v.at(&v, i - 1), status);
    }
    printf("\n");

    // Operations
    status = *(int*) v.pop_back(&v);
    printf("Pop Back Status:          %5d\n", status);

    i = 104;
    status = v.insert(&v, &i, 0);
    printf("Insert %d Status:        %5d\n", i, status);

    i = 4;
    status = v.find(&v, &i);
    printf("Find %d Index:             %5d\n", i, status);

    i = 4;
    status = v.erase_element(&v, &i);
    printf("Erase Element %d Status:   %5d\n", i, status);

    i = 2;
    status = v.erase_index(&v, i);
    printf("Erase Index %d Status:     %5d\n", i, status);

    i = 42;
    status = v.assign(&v, &i, v.size(&v) - 1);
    printf("Assign Status:            %5d\n", status);

    printf("Empty?                    %5d\n", v.empty(&v));
    printf("Front:                    %5d\n", *((int*) v.front(&v)));
    printf("Back:                     %5d\n", *((int*) v.back(&v)));
    printf("Shrink Status:            %5d\n", v.shrink(&v));
    printf("Current size:             %5d\n", v.size(&v));
    printf("Current capacity:         %5d\n", v.capacity(&v));

    printf("\n");
    for (i = 0; i < v.size(&v); ++i)
    {
        printf("v[%d] = %d\n", i, *(int*) v.at(&v, i));
    }
    printf("\n");

    printf("Clear Status:             %5d\n", v.clear(&v));

    v.free(&v);

    return 0;
}