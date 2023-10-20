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
 * void insert(x, i) - inserts an element at the i-th position [0, N[
 * void erase_element(x) - deletes such element and adjusts indexes
 * void erase_index(i) - deletes element at i-th position
 * 
 */

typedef struct members {
    int size;
    int capacity;
    int item_size;
    void** items;
} members;

typedef struct SVector vector;
struct SVector {
    members members;
    
    void* (*at)(vector*, int);
    void* (*back)(vector*);
    int (*capacity)(vector*);
    void (*clear)(vector*);
    int (*empty)(vector*);
    void (*free)(vector*);
    void* (*front)(vector*);
    int (*insert)(vector*, const void*, int);
    void* (*pop_back)(vector*);
    int (*push_back)(vector*, const void*);
    int (*resize)(vector*, int);
    int (*shrink)(vector*);
    int (*size)(vector*);
};

int update_capacity(vector* v, int new_capacity)
{
    int status = FAILURE;
    void** temp = malloc(new_capacity * v -> members.item_size);
    if (temp != NULL)
    {
        v -> members.capacity = new_capacity;
        for (int i = 0; i < v -> members.size; ++i)
        {
            temp[i] = v -> members.items[i];
        }
        free(v -> members.items);
        v -> members.items = temp;
        status = SUCCESS;
    }
    return status;
}

void* vat(vector* v, int index)
{
    if (v != NULL)
    {
        if (index >= 0 && index < v -> members.size)
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

int vcapacity(vector* v)
{
    return v -> members.capacity;
}

void vclear(vector* v)
{
    for (int i = 0; i < v -> members.size; ++i)
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

int vinsert(vector* v, const void* item, int pos)
{
    int status = FAILURE;
    if (v != NULL && item != NULL)
    {
        if (pos >= 0 && pos < v -> size(v))
        {
            v -> members.size++;
        }
    }
    return status;
}

void* vpop_back(vector* v)
{
    void* item = NULL;
    if (v != NULL)
    {
        if (v -> members.items != NULL)
        {
            v -> members.size--;
            item = v -> members.items + (v -> size(v));
            v -> shrink(v);
        }
    }
    return item;
}

int vpush_back(vector* v, const void* value)
{
    int status = FAILURE;
    if (v != NULL)
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

int vresize(vector* v, int new_size)
{
    int status = FAILURE;
    if (v != NULL && new_size >= 0)
    {
        status = update_capacity(v, new_size * 2);
    }
    return status;
}

int vshrink(vector* v)
{
    int status = FAILURE;
    if (v != NULL)
    {
        status = update_capacity(v, v -> size(v));
    }
    return status;
}

int vsize(vector* v)
{
    return v -> members.size;
}

void vector_init(vector *v, int item_size, int initialCapacity)
{
    // Methods
    v -> at = vat;
    v -> back = vback;
    v -> capacity = vcapacity;
    v -> clear = vclear;
    v -> empty = vempty;
    v -> free = vfree;
    v -> front = vfront;
    v -> insert = vinsert;
    v -> pop_back = vpop_back;
    v -> push_back = vpush_back;
    v -> resize = vresize;
    v -> shrink = vshrink;
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

    if (item_size > 0)
    {
        v -> members.items = malloc(v -> members.capacity * v -> members.item_size);
    }
    else
    {
        v -> members.item_size = VECTOR_DEFAULT_ITEMSIZE;
    }
}
