/**
 * @file    vector_test_float.h - Main program for testing the vector with float
 * @author  Vincenzo Cardea
 * @gmail   vincenzo.cardea.05
 * @version 0.4
 * @date    2024-04-11
 *
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include "./vector.h"

void print_vector(vector* v)
{
    int i;
    int size = v -> size(v);
    for (i = 0; i < size; ++i)
    {
        printf("V[%d] = %f\n", i, *(float*) v -> at(v, i));
    }
}

int main()
{
    vector v;
    vector_init(&v, sizeof(float), 2, 2);

    printf("Initial size:                %5d\n", v.size(&v));
    printf("Initial capacity:            %5d\n", v.capacity(&v));
    printf("Empty:                  (status %d)\n", v.empty(&v));
    printf("item_size:                   %5d\n", v.get_item_size(&v));
    printf("type_size:                   %5d\n", v.get_type_size(&v));

    int i;
    int status;
    float n;
    printf("\n");
    for (i = 1; i < 3; ++i)
    {
        n = (float) i;
        status = v.push_back(&v, &n);
        printf("Push Back %f:            (status %d)\n", n, status);
    }
    printf("\n");

    // Operations
    n = *(float*) v.pop_back(&v);
    printf("Pop Back:                    %5f\n", n);

    n = 104;
    status = v.insert(&v, &n, 0);
    printf("Insert %f:             (status %d)\n", n, status);

    n = 0;
    status = v.find(&v, &n);
    printf("Find %f Index:                %5d\n", n, status);

    n = 2;
    status = v.count(&v, &n);
    printf("Count value %f:               %5d\n", n, status);

    print_vector(&v);

    n = 104;
    status = v.erase_element(&v, &n);
    printf("Erase Element %f:        (status %d)\n", n, status);

    n = 2;
    status = v.count(&v, &n);
    printf("Count value %f:               %5d\n", n, status);

    print_vector(&v);

    i = 2;
    status = v.erase_index(&v, i);
    printf("Erase Index %d:          (status %d)\n", i, status);

    print_vector(&v);

    n = 42;
    status = v.assign(&v, &n, v.size(&v) - 1);
    printf("Assign %f:              (status %d)\n", n, status);

    print_vector(&v);

    return 0;
}