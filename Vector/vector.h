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
#define SUCCESS 0
#define FAILURE 1

/*
 * void erase_index(i) - deletes element at i-th position
 */

/**
 * Members of the vector
 */
typedef struct members {
    int size;
    int capacity;
    int item_size;
    void** items;
} members;

/**
 * Dynamic array
 */
typedef struct SVector vector;
struct SVector {
    members members;

    /**
     * Returns the i-th element
     *
     * @param  v pointer to the vector
     * @param  index of the element
     * @return element at i-th position
     */
    void* (*at)(vector*, int);

    /**
     * Returns the last element
     *
     * @param  v pointer to the vector
     * @return last element
     */
    void* (*back)(vector*);

    /**
     * Returns the current capacity
     *
     * @param  v pointer to the vector
     * @return current capacity
     */
    int (*capacity)(vector*);

    /**
     * Deletes all elements. Doesn't modify size and capacity
     *
     * @param v pointer to the vector
     */
    int (*clear)(vector*);

    /**
     * Checks if the vector is empty
     *
     * @param  v pointer to the vector
     * @return if vector is empty
     */
    int (*empty)(vector*);

    /**
     * Deletes the first occurrence of the element
     *
     * @param v pointer to the vector
     * @param element to delete
     */
    int (*erase_element)(vector*, const void*);

    /**
     * Deletes the element at the i-th position
     *
     * @param  v pointer to the vector
     * @param  element to delete
     * @return status
     */
    int (*erase_index)(vector*, int);

    /**
     * Clears the vector and resets initial size and capacity
     *
     * @param v pointer to the vector
     */
    void (*free)(vector*);

    /**
     * Returns the first element
     *
     * @param  v pointer to the vector
     * @return first element
     */
    void* (*front)(vector*);

    /**
     * Inserts an element at the i-th index
     *
     * @param  v pointer to the vector
     * @param  item to insert
     * @param  pos index
     * @return status
     */
    int (*insert)(vector*, const void*, int);

    /**
     * Removes the last element
     *
     * @param  v pointer to the vector
     * @return value of the removed element
     */
    void* (*pop_back)(vector*);

    /**
     * Add an element at the end of the vector
     *
     * @param  v pointer to the vector
     * @param  value to add
     * @return status
     */
    int (*push_back)(vector*, const void*);

    /**
     * Properly upgrades size and capacity
     *
     * @param v v pointer to the vector
     * @param new_size to set
     * @return status
     */
    int (*resize)(vector*, int);

    /**
     * Shrinks capacity to the size
     *
     * @param v v pointer to the vector
     * @return status
     */
    int (*shrink)(vector*);

    /**
     * Returns the current size
     *
     * @param v v pointer to the vector
     * @return current size
     */
    int (*size)(vector*);
};

/**
 * Updates vector's capacity according to specific needs.
 *
 * @param  v pointer to the vector
 * @param  new_capacity of the vector
 * @return status
 */
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

/**
 * Returns the i-th element
 *
 * @param  v pointer to the vector
 * @param  index of the element
 * @return element at i-th position
 */
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

/**
 * Returns the last element
 *
 * @param  v pointer to the vector
 * @return last element
 */
void* vback(vector* v)
{
    return v -> at(v, v -> size(v) - 1);
}

/**
 * Returns the current capacity
 *
 * @param  v pointer to the vector
 * @return current capacity
 */
int vcapacity(vector* v)
{
    return v -> members.capacity;
}

/**
 * Deletes all elements. Doesn't modify size and capacity
 *
 * @param v pointer to the vector
 */
int vclear(vector* v)
{
    int status = FAILURE;
    if (v != NULL)
    {
        status = v -> resize(v, 0);
    }
    return status;
}

/**
 * Checks if the vector is empty
 *
 * @param  v pointer to the vector
 * @return if vector is empty
 */
int vempty(vector* v)
{
    return (v -> members.size == 0);
}

/**
 * Deletes the first occurrence of the element
 *
 * @param v pointer to the vector
 * @param element to delete
 */
int verase_element(vector* v, const void* element)
{
    int status = FAILURE;
    if (v != NULL && element != NULL)
    {
        size_t size = v -> members.size;
        int i = 0;
        do {
            if (memcmp(v -> at(v, i), element, size) == 0)
            {
                status = SUCCESS;
            }
            else
            {
                ++i;
            }
        } while (i < v -> size(v) && !status);

        if (status)
        {
            void* source = NULL;
            void* destination = NULL;
            for (i = i + 1; i < v -> size(v); ++i)
            {
                source = v -> members.items + i;
                destination = v -> members.items + (i - 1);
                memcpy(destination, source, size);
            }
            status = v -> resize(v, v -> size(v) - 1);
        }
    }
    return status;
}

/**
 * Deletes the element at the i-th position
 *
 * @param  v pointer to the vector
 * @param  element to delete
 * @return status
*/
int verase_index(vector* v, int index)
{
    int status = FAILURE;
    if (v != NULL && index >= 0 && index < v -> size(v))
    {
        void* destination = NULL;
        void* source = NULL;
        size_t size = v -> members.item_size;
        int i;
        for (i = index; i < v -> size(v) - 1; ++i)
        {
            source = v -> members.items + (i + 1);
            destination = v -> members.items + i;
            memcpy(destination, source, size);
        }
        v -> resize(v, v -> size(v) - 1);
        status = SUCCESS;
    }
    return status;
}

/**
 * Clears the vector and resets initial size and capacity
 *
 * @param v pointer to the vector
 */
void vfree(vector* v)
{
    free(v -> members.items);
    v -> members.size = VECTOR_INIT_SIZE;
    v -> members.capacity = VECTOR_INIT_CAPACITY;
}

/**
 * Returns the first element
 *
 * @param  v pointer to the vector
 * @return first element
 */
void* vfront(vector* v)
{
    return v -> at(v, 0);
}

/**
 * Inserts an element at the i-th index
 *
 * @param  v pointer to the vector
 * @param  item to insert
 * @param  pos index
 * @return status
 */
int vinsert(vector* v, const void* item, int pos)
{
    int status = FAILURE;
    if (v != NULL && item != NULL)
    {
        if (pos >= 0 && pos < v -> size(v))
        {
            v -> resize(v, v -> size(v) + 1);

            void* source = NULL;
            void* destination = NULL;
            size_t size = v -> members.item_size;
            int i;
            for (i = v -> size(v) - 1; i >= pos; --i)
            {
                source = v -> members.items + i;
                destination = v -> members.items + (i + 1);
                memcpy(destination, source, size);
            }
            destination = v -> members.items + pos;
            memcpy(destination, item, size);

            status = SUCCESS;
        }
    }
    return status;
}

/**
 * Removes the last element
 *
 * @param  v pointer to the vector
 * @return value of the removed element
 */
void* vpop_back(vector* v)
{
    void* item = NULL;
    if (v != NULL)
    {
        if (v -> members.items != NULL)
        {
            v -> members.size--;
            item = v -> members.items + v -> size(v);
        }
    }
    return item;
}

/**
 * Add an element at the end of the vector
 *
 * @param  v pointer to the vector
 * @param  value to add
 * @return status
 */
int vpush_back(vector* v, const void* value)
{
    int status = FAILURE;
    if (v != NULL)
    {
        int size = v -> size(v);
        if (size == v -> capacity(v))
        {
            v -> resize(v, size);
            status = update_capacity(v, v -> capacity(v));
        }

        if (v -> members.items != NULL)
        {
            void* position = (char*) v -> members.items + (size * v -> members.item_size);
            memcpy(position, value, sizeof(value));
            v -> members.size++;
            status = SUCCESS;
        }
    }
    return status;
}

/**
 * Properly upgrades size and capacity
 *
 * @param v v pointer to the vector
 * @param new_size to set
 * @return status
 */
int vresize(vector* v, int new_size)
{
    int status = FAILURE;
    if (v != NULL && new_size >= 0)
    {
        v -> members.size = new_size;
        status = update_capacity(v, new_size * 2 + VECTOR_INIT_CAPACITY);
    }
    return status;
}

/**
 * Shrinks capacity to the size
 *
 * @param v v pointer to the vector
 * @return status
 */
int vshrink(vector* v)
{
    int status = FAILURE;
    if (v != NULL)
    {
        status = update_capacity(v, v -> size(v));
    }
    return status;
}

/**
 * Returns the current size
 *
 * @param v v pointer to the vector
 * @return current size
 */
int vsize(vector* v)
{
    return v -> members.size;
}

/**
 * Vector initialization function
 *
 * @param v v pointer to the vector
 * @param item_size size of the elements
 * @param initialCapacity allocated amount memory for elements
 */
void vector_init(vector *v, int item_size, int initialCapacity)
{
    // Methods
    v -> at = vat;
    v -> back = vback;
    v -> capacity = vcapacity;
    v -> clear = vclear;
    v -> empty = vempty;
    v -> erase_element = verase_element;
    v -> erase_index = verase_index;
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
