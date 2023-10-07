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

/**
 * pointer* begin() - iterator
 * pointer* end() - iterator
 * 
 * void resize(N) - resize the vector
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
    
    int (*capacity)(vector *);
    void (*resize)(vector *, int);
    int (*size)(vector *);
};

int update_capacity(int size)
{
    return (sizeof(void *) * size + VECTOR_INIT_CAPACITY);
}

void* alloc_items(int capacity)
{
    return malloc(sizeof(void *) * capacity);
}

int vcapacity(vector* v)
{
    return v -> members.capacity;
}

void vresize(vector* v, int new_size)
{
    v -> members.size = new_size;
    v -> members.capacity = update_capacity(new_size);
}

int vsize(vector* v)
{
    return v -> members.size;
}


void vector_init(vector *v)
{
    // Methods
    v -> capacity = vcapacity;
    v -> resize = vresize;
    v -> size = vsize;
 
    // Members
    v -> members.size = VECTOR_INIT_SIZE;
    v -> members.capacity = update_capacity(v -> members.size);
    v -> members.items = alloc_items(v -> members.capacity);
}
