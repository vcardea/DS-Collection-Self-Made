/**
 * @file    vector.h - Dynamic array in C
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.2
 * @date    2023-11-06
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef VECTOR_H
#define VECTOR_H

#pragma once

#include <stdlib.h>
#include <limits.h>
#include "../utils.h"

#define VECTOR_INIT_CAPACITY 1
#define VECTOR_INIT_SIZE 0
#define VECTOR_DEFAULT_ITEMSIZE 8
#define VECTOR_DEFAULT_TYPESIZE 8

/**
* Members of the vector
*/
typedef struct members {

    /**
     * Number of elements
     */
    int size;

    /**
     * Memory allocated for the elements
     */
    int capacity;

    /**
     * Size of an element in Bytes
     */
    int item_size;

    /**
     * Size of the value pointed to in Bytes
     */
    int type_size;

    /**
     * Array of pointers to elements
     */
    void** items;
} members;

/**
 * Dynamic array
 */
typedef struct SVector vector;
struct SVector {
    /**
     * Contains attributes of the vector
     */
    members members;

    /**
     * Assigns a value to a specified index
     *
     * @param v pointer to the vector
     * @param value to assign
     * @param index where to assign
     * @return status
     */
    int (*assign)(vector*, const void*, int);

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
     * @return status
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
     * @return status
     */
    int (*erase_element)(vector*, const void*);

    /**
     * Deletes the element at the i-th position
     *
     * @param  v pointer to the vector
     * @param  index of the element to remove
     * @return status
     */
    int (*erase_index)(vector*, int);

    /**
     * Finds the first occurrence of a value within the vector
     *
     * @param v pointer to the vector
     * @param value to find
     * @return index of the first value
     */
    int (*find)(vector*, const void*);

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
     * Returns the size of an elements in bytes
     *
     * @param v pointer to the vector
     * @return size of an element [bytes]
     */
    int (*get_item_size)(vector*);

    /**
     * Returns the size of the type of data stored
     *
     * @param v pointer to the vector
     * @return size of the type of data stored
     */
    int (*get_type_size)(vector*);

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
    void** temp = malloc(new_capacity * v -> get_item_size(v));
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
 * Assigns a value to a specified index
 *
 * @param v pointer to the vector
 * @param value to assign
 * @param index where to assign
 * @return status
 */
int vassign(vector* v, const void* value, int index)
{
    int status = FAILURE;
    if (v != NULL && v -> members.items != NULL && value != NULL)
    {
        if (index >= 0 && index < v -> size(v))
        {
            void* destination = v -> members.items + index;
            int type_size = v -> get_type_size(v);
            if (destination != NULL && type_size != -1)
            {
                status = SUCCESS;
                //memcpy(destination, value, type_size);
                status |= copy(destination, value, type_size);
                //status = memcmp(destination, value, size);
                status |= compare(destination, value, type_size);
            }
        }
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
    void* value = NULL;
    if (v != NULL && v -> members.items != NULL)
    {
        if (index >= 0 && index < v -> size(v))
        {
            value = v -> members.items + index;
        }
    }
    return value;
}

/**
 * Returns the last element
 *
 * @param  v pointer to the vector
 * @return last element
 */
void* vback(vector* v)
{
    void* value = NULL;
    if (v != NULL && v -> members.items != NULL)
    {
        value = v -> at(v, v -> size(v) - 1);
    }
    return value;
}

/**
 * Returns the current capacity
 *
 * @param  v pointer to the vector
 * @return current capacity
 */
int vcapacity(vector* v)
{
    int capacity = VALUE_ERROR;
    if (v != NULL)
    {
        capacity = v -> members.capacity;
    }
    return capacity;
}

/**
 * Deletes all elements. Doesn't modify size and capacity
 *
 * @param v pointer to the vector
 * @return status
 */
int vclear(vector* v)
{
    int status = FAILURE;
    if (v != NULL && v -> members.items != NULL)
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
    int bool = false;
    if (v != NULL)
    {
        bool = (v -> size(v) == 0);
    }
    return bool;
}

/**
 * Deletes the first occurrence of the element
 *
 * @param v pointer to the vector
 * @param element to delete
 * @return status
 */
int verase_element(vector* v, const void* element)
{
    int status = FAILURE;
    if (v != NULL && v -> members.items != NULL && element != NULL)
    {
        int index = v -> find(v, element);
        if (index != VALUE_ERROR)
        {
            void* source = NULL;
            void* destination = NULL;
            int type_size = v -> get_type_size(v);
            if (type_size != -1)
            {
                status = SUCCESS;
                int i;
                for (i = index + 1; i < v -> size(v); ++i)
                {
                    source = v -> members.items + i;
                    destination = v -> members.items + (i - 1);
                    //memcpy(destination, source, type_size);
                    status |= copy(destination, source, type_size);
                }
                status |= v -> resize(v, v -> size(v) - 1);
            }
        }
    }
    return status;
}

/**
 * Deletes the element at the i-th position
 *
 * @param  v pointer to the vector
 * @param  index of the element to remove
 * @return status
*/
int verase_index(vector* v, int index)
{
    int status = FAILURE;
    if (v != NULL && v -> members.items != NULL)
    {
        if (index >= 0 && index < v -> size(v))
        {
            void* destination = NULL;
            void* source = NULL;
            int type_size = v -> get_type_size(v);
            if (type_size != -1)
            {
                status = SUCCESS;
                int i;
                for (i = index; i < v -> size(v) - 1; ++i)
                {
                    source = v -> members.items + (i + 1);
                    destination = v -> members.items + i;
                    //memcpy(destination, source, type_size);
                    status |= copy(destination, source, type_size);
                }
                status |= v -> resize(v, v -> size(v) - 1);
            }
        }
    }
    return status;
}

/**
 * Finds the first occurrence of a value within the vector
 *
 * @param v pointer to the vector
 * @param value to find
 * @return index of the first value
 */
int vfind(vector* v, const void* value)
{
    int index = VALUE_ERROR;
    if (v != NULL && v -> members.items != NULL && value != NULL)
    {
        int type_size = v -> get_type_size(v);
        if (type_size != -1)
        {
            int found = false;
            void* item = NULL;
            int i = 0;
            while (i < v -> size(v) && !found)
            {
                item = v -> members.items + i;
                //found = (memcmp(item, value, size) == 0);
                found = (compare(item, value, type_size) == 0);
                ++i;
            }

            if (found)
            {
                index = i - 1;
            }
        }
    }
    return index;
}

/**
 * Clears the vector and resets initial size and capacity
 *
 * @param v pointer to the vector
 */
void vfree(vector* v)
{
    if (v != NULL)
    {
        free(v -> members.items);
        v -> members.size = VECTOR_INIT_SIZE;
        v -> members.capacity = VECTOR_INIT_CAPACITY;
    }
}

/**
 * Returns the first element
 *
 * @param  v pointer to the vector
 * @return first element
 */
void* vfront(vector* v)
{
    void* value = NULL;
    if (v != NULL)
    {
        value = v -> at(v, 0);
    }
    return value;
}

/**
 * Returns the size of an elements in bytes
 *
 * @param v pointer to the vector
 * @return size of an element [bytes]
 */
int vget_item_size(vector* v)
{
    int item_size = VALUE_ERROR;
    if (v != NULL)
    {
        item_size = v -> members.item_size;
    }
    return item_size;
}

/**
 * Returns the size of the type of data stored
 *
 * @param v pointer to the vector
 * @return size of the type of data stored
 */
int vget_type_size(vector* v)
{
    int type_size = VALUE_ERROR;
    if (v != NULL)
    {
        type_size = v -> members.type_size;
    }
    return type_size;
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
            int type_size = v -> get_type_size(v);
            if (type_size != -1)
            {
                status = SUCCESS;
                int i;
                for (i = v -> size(v) - 1; i >= pos; --i)
                {
                    source = v -> members.items + i;
                    destination = v -> members.items + (i + 1);
                    //memcpy(destination, source, type_size);
                    status |= copy(destination, source, type_size);
                }
                destination = v -> members.items + pos;
                //memcpy(destination, item, type_size);
                status |= copy(destination, item, type_size);
            }
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
    if (v != NULL && v -> members.items != NULL)
    {
        int size = v -> size(v) - 1;
        item = v -> members.items + size;
        v -> resize(v, size);
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
    if (v != NULL && value != NULL)
    {
        int size = v -> size(v);
        status = v -> resize(v, size + 1);
        if (v -> members.items != NULL && !status)
        {
            status = SUCCESS;
            void* position = (char*) v -> members.items + (size * v -> get_item_size(v));
            if (position != NULL)
            {
                //memcpy(position, value, v -> get_item_size(v));
                status |= copy(position, value, v -> get_type_size(v));
            }
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
 * @param v pointer to the vector
 * @return current size
 */
int vsize(vector* v)
{
    int size = VALUE_ERROR;
    if (v != NULL)
    {
        size = v -> members.size;
    }
    return size;
}

/**
 * Vector initialization function
 *
 * @param v v pointer to the vector
 * @param item_size size of the elements
 * @param initialCapacity allocated amount memory for elements
 */
void vector_init(vector *v, long long item_size, long long type_size, long long initialCapacity)
{
    if (v != NULL)
    {
        // Methods
        v -> assign = vassign;
        v -> at = vat;
        v -> back = vback;
        v -> capacity = vcapacity;
        v -> clear = vclear;
        v -> empty = vempty;
        v -> erase_element = verase_element;
        v -> erase_index = verase_index;
        v -> find = vfind;
        v -> free = vfree;
        v -> front = vfront;
        v -> get_item_size = vget_item_size;
        v -> get_type_size = vget_type_size;
        v -> insert = vinsert;
        v -> pop_back = vpop_back;
        v -> push_back = vpush_back;
        v -> resize = vresize;
        v -> shrink = vshrink;
        v -> size = vsize;

        // Members
        v -> members.size = VECTOR_INIT_SIZE;

        if (item_size > 0 && item_size <= INT_MAX)
        {
            v -> members.item_size = item_size;
        }
        else
        {
            v -> members.item_size = VECTOR_DEFAULT_ITEMSIZE;
        }

        if (type_size > 0 && type_size <= INT_MAX)
        {
            v -> members.type_size = type_size;
        }
        else
        {
            v -> members.type_size = sizeof(type_size);
        }

        if (initialCapacity > 0 && initialCapacity <= INT_MAX)
        {
            v -> members.capacity = initialCapacity;
        }
        else
        {
            v -> members.capacity = VECTOR_INIT_CAPACITY;
        }

        long long size = v -> size(v);
        if (size > v -> capacity(v))
        {
            v -> members.capacity = size;
        }

        v -> members.items = malloc(v -> members.capacity * v -> members.item_size);
    }
}

#endif
