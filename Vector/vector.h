/**
 * @file    vector.h - Dynamic array in C
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.1
 * @date    2023-10-06
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdlib.h>

#define VECTOR_INIT_CAPACITY 8
#define VECTOR_INIT_SIZE 0
#define SUCCESS 1
#define FAILURE 0

/**
 * pointer* begin() - iterator
 * pointer* end() - iterator
 * 
 * bool empty() - checks if the vector is empty
 * int shrink() - resize the vector to the minimum size. returns current size
 * <type> at(i) - accesses to the i-th element
 * <type> front() - returns the first element
 * <type> back() - returns the last element
 * 
 * void push_back(x) - adds an element to the end of the vector
 * <type> pop_back(x) - removes the last element the vector
 * void insert(x, i) - inserts an element at the i-th position [0, N[
 * void erase_element(x) - deletes such element and adjusts indexes
 * void erase_index(i) - deletes element at i-th position
 * void clear() - deletes all elements
 * 
 */

typedef struct members {
    int size;
    int capacity;
    void** items;
} members;

typedef struct SVector vector;
struct SVector {
    members members;
    
    void* (*at)(vector*, int);
    int (*capacity)(vector*);
    void* (*front)(vector*);
    int (*push_back)(vector*, void*);
    int (*resize)(vector*, int);
    int (*size)(vector*);
};

int update_capacity(int size)
{
    return (sizeof(void *) * size * 2);
}

void* alloc_items(int capacity)
{
    return malloc(sizeof(void *) * capacity);
}

void* vat(vector* v, int index)
{
    if (index >= 0 && index < v -> members.size)
    {
        return v -> members.items[index];
    }
    return NULL;
}

int vcapacity(vector* v)
{
    return v -> members.capacity;
}

void* vfront(vector* v)
{
    return v -> at(v, 0);
}

int vpush_back(vector* v, void* value)
{
    printf("Entro");
    int status = FAILURE;
    if (v)
    {
        if (v -> members.size == v -> members.capacity)
        {
            v -> resize(v, v -> members.size + 1);
        }
        v -> members.items[v -> members.size] = value;
        status = SUCCESS;
    }
    printf("Esco");
    return status;
}

int vresize(vector* v, int new_size)
{
    int status = FAILURE;
    if (v)
    {
        v -> members.size = new_size;
        v -> members.capacity = update_capacity(new_size);
        status = SUCCESS;
    }
    return status;
}

int vsize(vector* v)
{
    return v -> members.size;
}

void vector_init(vector *v)
{
    // Methods
    v -> at = vat;
    v -> capacity = vcapacity;
    v -> front = vfront;
    v -> resize = vresize;
    v -> size = vsize;
 
    // Members
    v -> members.size = VECTOR_INIT_SIZE;
    v -> members.capacity = VECTOR_INIT_CAPACITY;
    v -> members.items = alloc_items(v -> members.capacity);
}
