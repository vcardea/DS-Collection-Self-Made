#include <stdio.h>
#include "./Vector/vector.h"

int main()
{
    vector v;
    vector_init(&v, sizeof(int*), sizeof(int), 1);

    printf("Initial size:             %3d\n", v.size(&v));
    printf("Initial capacity:         %3d\n", v.capacity(&v));
    printf("Empty?                    %3d\n", v.empty(&v));
    printf("item_size:                %3d\n", v.get_item_size(&v));
    printf("type_size:                %3d\n", v.get_type_size(&v));

    int i;
    int* ptr_int = &i;
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
    printf("Pop Back Status:          %3d\n", status);

    i = 104;
    status = v.insert(&v, &i, 0);
    printf("Insert %d Status:        %3d\n", i, status);

    i = 4;
    status = v.find(&v, &i);
    printf("Find %d Index:             %3d\n", i, status);

    i = 4;
    status = v.erase_element(&v, &i);
    printf("Erase Element %d Status:   %3d\n", i, status);

    i = 2;
    status = v.erase_index(&v, i);
    printf("Erase Index %2d Status:    %3d\n", i, status);

    i = 42;
    status = v.assign(&v, &i, v.size(&v) - 1);
    printf("Assign Status:            %3d\n", status);

    printf("Empty?                    %3d\n", v.empty(&v));
    printf("Front:                    %3d\n", *((int*) v.front(&v)));
    printf("Back:                     %3d\n", *((int*) v.back(&v)));
    printf("Shrink Status:            %3d\n", v.shrink(&v));
    printf("Current size:             %3d\n", v.size(&v));
    printf("Current capacity:         %3d\n", v.capacity(&v));

    printf("\n");
    for (i = 0; i < v.size(&v); ++i)
    {
        printf("v[%d] = %d\n", i, *(int*) v.at(&v, i));
    }
    printf("\n");

    printf("Clear Status:             %3d\n", v.clear(&v));

    v.free(&v);

    return 0;
}