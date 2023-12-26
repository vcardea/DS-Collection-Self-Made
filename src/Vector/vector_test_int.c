/**
 * @file    vector_test_int.h - Main program for testing the vector with integers
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.4
 * @date    2023-12-26
 *
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include "./vector.h"

int custom_compare(const void* a, const void* b, int size)
{
    return (compare(a, b, size) == 0);
}

int main()
{
    vector v;
    vector_init(&v, sizeof(int), 3, 5);

    printf("Initial size:                %5d\n", v.size(&v));
    printf("Initial capacity:            %5d\n", v.capacity(&v));
    printf("Empty:                  (status %d)\n", v.empty(&v));
    printf("item_size:                   %5d\n", v.get_item_size(&v));
    printf("type_size:                   %5d\n", v.get_type_size(&v));

    int i;
    int status;
    printf("\n");
    for (i = 3; i <= 6; ++i)
    {
        status = v.push_back(&v, &i);
        printf("Push Back %d:            (status %d)\n", i, status);
    }
    printf("\n");

    // Operations
    status = *(int*) v.pop_back(&v);
    printf("Pop Back:                    %5d\n", status);

    i = 104;
    status = v.insert(&v, &i, 0);
    printf("Insert %d:             (status %d)\n", i, status);

    i = 4;
    status = v.find(&v, &i);
    printf("Find %d Index:                %5d\n", i, status);

    i = 4;
    status = v.count(&v, &i);
    printf("Count value %d:               %5d\n", i, status);

    i = 4;
    status = v.erase_element(&v, &i);
    printf("Erase Element %d:        (status %d)\n", i, status);

    i = 4;
    status = v.count(&v, &i);
    printf("Count value %d:               %5d\n", i, status);

    i = 2;
    status = v.erase_index(&v, i);
    printf("Erase Index %d:          (status %d)\n", i, status);

    i = 42;
    status = v.assign(&v, &i, v.size(&v) - 1);
    printf("Assign %d:              (status %d)\n", i, status);

    i = 73;
    status = v.assign(&v, &i, v.size(&v) - 1);
    printf("Assign %d:              (status %d)\n", i, status);

    printf("Empty?                  (status %d)\n", v.empty(&v));
    printf("Front:                       %5d\n", *(int*) v.front(&v));
    printf("Back:                        %5d\n", *(int*) v.back(&v));
    printf("Shrink:                 (status %d)\n", v.shrink(&v));
    printf("Current size:                %5d\n", v.size(&v));
    printf("Current capacity:            %5d\n", v.capacity(&v));

    printf("\n");
    for (i = 0; i < v.size(&v); ++i)
    {
        printf("v[%d] = %d\n", i, *(int*) v.at(&v, i));
    }
    printf("\n");

    i = 3;
    status = v.remove_if(&v, 0, v.size(&v), &i, sizeof(int), custom_compare);
    printf("Remove If v[i] == 0:    (status %d)\n", status);

    printf("\n");
    for (i = 0; i < v.size(&v); ++i)
    {
        printf("v[%d] = %d\n", i, *(int*) v.at(&v, i));
    }
    printf("\n");

    i = 68;
    status = v.fill(&v, &i);
    printf("Fill %d:                (status %d)\n", i, status);

    i = *(int*) v.back(&v) + 1;
    status = v.assign(&v, &i, v.size(&v) - 1);
    printf("Assign %d:              (status %d)\n", i, status);

    i = *(int*) v.front(&v) - 1;
    status = v.assign(&v, &i, 0);
    printf("Assign %d:              (status %d)\n", i, status);

    i = *(int*) v.begin(&v);
    printf("Begin:                       %5d\n", i);

    i = *(int*) (v.end(&v) - sizeof(void*));
    printf("End:                         %5d\n", i);

    i = *(int*) v.rbegin(&v);
    printf("Reversed begin:              %5d\n", i);

    i = *(int*) (v.rend(&v) + sizeof(void*));
    printf("Reversed end:                %5d\n", i);

    status = swap(v.begin(&v), v.rbegin(&v), sizeof(int));
    printf("Swap %d %d:             (status %d)\n", *(int*)v.begin(&v), *(int*)v.rbegin(&v), status);

    printf("\n");
    for (i = 0; i < v.size(&v); ++i)
    {
        printf("v[%d] = %d\n", i, *(int*) v.at(&v, i));
    }
    printf("\n");

    printf("Clear:                  (status %d)\n", v.clear(&v));

    v.free(&v);

    return 0;
}