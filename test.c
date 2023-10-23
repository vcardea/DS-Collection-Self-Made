#include <stdio.h>
#include "./Vector/vector.h"

int main()
{
    // Declaration and initialization
    vector v;
    vector_init(&v, sizeof(int), sizeof(int), 1);

    // Beginning
    printf("Initial size:     %d\n", v.size(&v));
    printf("Initial capacity: %d\n", v.capacity(&v));
    printf("Empty?            %d\n", v.empty(&v));
    printf("Item size:        %d\n\n", v.get_item_size(&v));

    // Fills the vector up
    int i;
    int status;
    for (i = 1; i <= 6; ++i)
    {
        status = v.push_back(&v, &i);
        printf("v[%d] = %d\n", i, *(int*) v.at(&v, i - 1));
    }
    printf("\n");

    // Operations
//    int value = 1;
//    int find_index = v.find(&v, &value);
//    printf("Find %d Status:   %d\n", value, find_index);
//
//    int element_to_erase = 1;
//    int erase_element_status = v.erase_element(&v, &element_to_erase);
//    printf("Erase Element %d Status: %d\n", element_to_erase, erase_element_status);
//
//    int index_to_erase = 2;
//    int erase_index_status = v.erase_index(&v, index_to_erase);
//    printf("Erase Index %d Status:    %d\n", index_to_erase, erase_index_status);
//
//    int new_value = 42;
//    int assign_status = v.assign(&v, &new_value, v.size(&v) - 1);
//    printf("Assign Status:    %d\n", assign_status);

    printf("Empty?            %d\n", v.empty(&v));
    printf("Front:            %d\n", *((int*) v.front(&v)));
    printf("Back:             %d\n", *((int*) v.back(&v)));
    printf("Shrink Status:    %d\n", v.shrink(&v));
    printf("Current size:     %d\n", v.size(&v));
    printf("Current capacity: %d\n", v.capacity(&v));
    printf("Clear Status:     %d\n\n", v.clear(&v));

    v.free(&v);

    return 0;
}