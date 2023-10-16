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
 * <type> pop_back(x) - removes the last element the vector
 * void insert(x, i) - inserts an element at the i-th position [0, N[
 * void erase_element(x) - deletes such element and adjusts indexes
 * void erase_index(i) - deletes element at i-th position
 * 
 */

typedef struct members {
    size_t size;
    size_t capacity;
    size_t item_size;
    void** items;
} members;

typedef struct SVector vector;
struct SVector {
    members members;
    
    void* (*at)(vector*, size_t);
    void* (*back)(vector*);
    size_t (*capacity)(vector*);
    void (*clear)(vector*);
    int (*empty)(vector*);
    void (*free)(vector*);
    void* (*front)(vector*);
    void* (*pop_back)(vector*);
    size_t (*push_back)(vector*, const void*);
    size_t (*resize)(vector*, size_t);
    size_t (*shrink)(vector*, size_t);
    size_t (*size)(vector*);
};

int update_capacity(vector* v, size_t new_capacity)
{
    int status = FAILURE;
    void** temp = malloc(new_capacity * v -> members.item_size);
    if (temp)
    {
        v -> members.capacity = new_capacity;
        for (int i = 0; i < v -> members.size; i++)
        {
            temp[i] = v -> members.items[i];
        }
        free(v -> members.items);
        v -> members.items = temp;
        status = SUCCESS;
    }
    return status;
}

void* vat(vector* v, size_t index)
{
    if (v)
    {
        if (index < v -> members.size)
        {
            return v -> members.items + index;
        }
    }
    return NULL;
}

void* vback(vector* v)
{
    return v -> at(v, v -> size(v) - 1);
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

int vempty(vector* v)
{
    return (v -> members.size == 0);
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

void* vpop_back(vector* v)
{
    void* item = NULL;
    if (v)
    {
        if (v -> members.items != NULL)
        {
//            size_t index = (v -> size(v) - 1) * v -> members.item_size;
//            item = v -> at(v, index);
//            void* destination = (char*) v -> members.items + index;
//            const void* value = 0;
//            memcpy(destination, value, v -> members.item_size);
            v -> members.size--;
            v -> shrink(v, v -> size(v));
        }
    }
    return item;
}

size_t vpush_back(vector* v, const void* value)
{
    int status = FAILURE;
    if (v)
    {
        if (v -> members.size == v -> members.capacity)
        {
            v -> resize(v, v -> members.size * 2);
            update_capacity(v, v -> members.capacity);
        }

        if (v -> members.items != NULL)
        {
            void* position = (char*) v -> members.items + (v -> members.size * v -> members.item_size);
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
        status = update_capacity(v, v -> members.capacity);
    }
    return status;
}

size_t vshrink(vector* v, size_t new_capacity)
{
    int status = FAILURE;
    if (v)
    {
        status = update_capacity(v, new_capacity);
    }
    return status;
}

size_t vsize(vector* v)
{
    return v -> members.size;
}

void vector_init(vector *v, size_t item_size, size_t initialCapacity)
{
    // Methods
    v -> at = vat;
    v -> back = vback;
    v -> capacity = vcapacity;
    v -> clear = vclear;
    v -> empty = vempty;
    v -> free = vfree;
    v -> front = vfront;
    v -> pop_back = vpop_back;
    v -> push_back = vpush_back;
    v -> resize = vresize;
    v -> shrink
    = vshrink;
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

    if (item_size > 0)
    {
        v -> members.item_size = item_size;
    }
    else
    {
        v -> members.item_size = VECTOR_DEFAULT_ITEMSIZE;
    }
    v -> members.items = malloc(v -> members.capacity * v -> members.item_size);
}
