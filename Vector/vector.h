/**
 * @file    vector.h - Dynamic array in C
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-10-06
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdlib.h>
#include <string.h>

#define VECTOR_INIT_CAPACITY 1
#define VECTOR_INIT_SIZE 0
#define VECTOR_DEFAULT_ITEMSIZE 8
#define SUCCESS 1
#define FAILURE 0

/**
 * 
 * bool empty() - checks if the vector is empty
 * int shrink() - resize the vector to the minimum size. returns current size
 * <type> back() - returns the last element
 *
 * <type> pop_back(x) - removes the last element the vector
 * void insert(x, i) - inserts an element at the i-th position [0, N[
 * void erase_element(x) - deletes such element and adjusts indexes
 * void erase_index(i) - deletes element at i-th position
 * void clear() - deletes all elements
 * 
 */

typedef struct members {
    size_t size;
    size_t capacity;
    size_t itemSize;
    void** items;
} members;

typedef struct SVector vector;
struct SVector {
    members members;
    
    void* (*at)(vector*, size_t);
    size_t (*capacity)(vector*);
    void (*clear)(vector*);
    void (*free)(vector*);
    void* (*front)(vector*);
    void (*set_item_size)(vector*, size_t);
    size_t (*push_back)(vector*, const void*);
    size_t (*resize)(vector*, size_t);
    size_t (*size)(vector*);
};

void* vat(vector* v, size_t index)
{
    if (v)
    {
        if (index < v -> members.size)
        {
            return v -> members.items + (index * v -> members.itemSize);
        }
    }
    return NULL;
}

size_t vcapacity(vector* v)
{
    return v -> members.capacity;
}

void vclear(vector* v)
{
    for (size_t i = 0; i < v -> members.size; i++)
    {
        v -> members.items[i] = NULL;
    }
}

void vfree(vector* v)
{
    free(v -> members.items);
    v -> members.size = VECTOR_INIT_SIZE;
    v -> members.capacity = VECTOR_INIT_CAPACITY;
    v -> members.items = NULL;
}

void* vfront(vector* v)
{
    return v -> at(v, 0);
}

void vset_item_size(vector* v, size_t new_itemSize)
{
    if (v)
    {
        v -> members.itemSize = new_itemSize;
    }
}

size_t vpush_back(vector* v, const void* value)
{
    int status = FAILURE;
    if (v)
    {
        if (v -> members.size == v -> members.capacity)
        {
            v -> resize(v, v -> members.size * 2);
            v -> members.items = realloc(v -> members.items, v -> members.capacity * v -> members.itemSize);
        }

        if (v -> members.items != NULL)
        {
            void* position = (char*) v -> members.items + (v -> members.size * v -> members.itemSize);
            memcpy(position, value, sizeof(value));
            v -> members.size++;
            status = SUCCESS;
        }
    }
    return status;
}

size_t vresize(vector* v, size_t new_capacity)
{
    int status = FAILURE;
    if (v)
    {
        v -> members.capacity = new_capacity;
        void** new_items = malloc(v -> members.capacity * v -> members.itemSize);
        if (new_items)
        {
            for (int i = 0; i < v -> members.size; i++)
            {
                new_items[i] = v -> members.items[i];
            }
            free(v -> members.items);
            v -> members.items = new_items;
            status = SUCCESS;
        }
    }
    return status;
}

size_t vsize(vector* v)
{
    return v -> members.size;
}

void vector_init(vector *v, size_t itemSize, size_t initialCapacity)
{
    // Methods
    v -> at = vat;
    v -> capacity = vcapacity;
    v -> clear = vclear;
    v -> free = vfree;
    v -> front = vfront;
    v -> set_item_size = vset_item_size;
    v -> push_back = vpush_back;
    v -> resize = vresize;
    v -> size = vsize;
 
    // Members
    v -> members.size = VECTOR_INIT_SIZE;
    if (initialCapacity > 0)
    {
        v -> members.capacity = initialCapacity;
    }
    else
    {
        v -> members.capacity = VECTOR_INIT_CAPACITY;
    }

    if (itemSize > 0)
    {
        v -> members.itemSize = itemSize;
    }
    else
    {
        v -> members.itemSize = VECTOR_DEFAULT_ITEMSIZE;
    }
    v -> members.items = malloc(v -> members.capacity * v -> members.itemSize);
}
