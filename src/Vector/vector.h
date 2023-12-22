/**
 * @file    vector.h - Dynamic array in C
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.3
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
     * Size of the value pointed by an element in Bytes
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
     * Counts the number of occurrences of a given value
     *
     * @param v pointer to the vector
     * @param value to count
     * @return number of occurrences of value
     */
    int (*count)(vector*, const void*);

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
     * Fills up the vector with the given value
     *
     * @param v pointer to the vector
     * @param value to fill the vector with
     * @return status
     */
     int (*fill)(vector*, const void*);

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
     * @return status
     */
    int (*free)(vector*);

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
    printf("CAPACITY??\n");
    int status = FAILURE;
    int bytes = new_capacity * v -> get_item_size(v);
    printf("\n%d * %d = %d\n", new_capacity, v -> get_item_size(v), bytes);
    void** temp = malloc(bytes);
    printf("\nPrima malloc\n");
    if (temp)
    {
        printf("\nEntra?\n");
        v -> members.capacity = new_capacity;
        status = copy(temp, v -> members.items, bytes);
        free(v -> members.items);
        v -> members.items = temp;
    }
    printf("CAPACITY?? siiiiiiii\n");
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
    if (v)
    {
        if (v -> members.items && value && index >= 0 && index < v -> size(v))
        {
            void* destination = v -> members.items + index;
            int type_size = v -> get_type_size(v);
            if (destination && type_size != VALUE_ERROR)
            {
                status = SUCCESS;
                //memcpy(destination, value, type_size);
                status |= copy(destination, value, type_size);
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
    if (v)
    {
        if (v -> members.items && index >= 0 && index < v -> size(v))
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
    if (v)
    {
        if (v -> members.items)
        {
            value = v -> at(v, v -> size(v) - 1);
        }
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
    if (v)
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
    if (v)
    {
        if (v -> members.items)
        {
            status = v -> resize(v, 0);
        }
    }
    return status;
}

/**
 * Counts the number of occurrences of a given value
 *
 * @param v pointer to the vector
 * @param value to count
 * @return number of occurrences of value
 */
int vcount(vector* v, const void* value)
{
    int count = VALUE_ERROR;
    if (v)
    {
        if (v -> members.items && value && !v -> empty(v))
        {
            int size = v -> get_type_size(v);
            const void* a = NULL;
            int i;
            for (i = 0; i < v -> size(v); ++i)
            {
                a = v -> members.items + i;
                if (compare(a, value, size) == SUCCESS)
                {
                    count++;
                }
            }
            count++;
        }
    }
    return count;
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
    if (v)
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
    if (v)
    {
        if (v -> members.items && element)
        {
            int index = v -> find(v, element);
            if (index != VALUE_ERROR)
            {
                void* source = NULL;
                void* destination = NULL;
                int type_size = v -> get_type_size(v);
                if (type_size != VALUE_ERROR)
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
    if (v)
    {
        if (v -> members.items && index >= 0 && index < v -> size(v))
        {
            void* destination = NULL;
            void* source = NULL;
            int type_size = v -> get_type_size(v);
            if (type_size != VALUE_ERROR)
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
 * Fills up the vector with the given value
 *
 * @param v pointer to the vector
 * @param value to fill the vector with
 * @return status
 */
int vfill(vector* v, const void* value)
{
    int status = FAILURE;
    if (v)
    {
        if (v -> members.items && value && !v -> empty(v))
        {
            status = SUCCESS;
            int size = v -> get_type_size(v);
            const void* destination = NULL;
            int i;
            for (i = 0; i < v -> size(v); ++i)
            {
                destination = v -> members.items + i;
                status |= copy(destination, value, size);
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
    if (v)
    {
        if (v -> members.items && value)
        {
            int type_size = v -> get_type_size(v);
            if (type_size != VALUE_ERROR)
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
    }
    return index;
}

/**
 * Clears the vector and resets initial size and capacity
 *
 * @param v pointer to the vector
 * @return status
 */
int vfree(vector* v)
{
    int status = FAILURE;
    if (v)
    {
        free(v -> members.items);
        v -> members.size = VECTOR_INIT_SIZE;
        v -> members.capacity = VECTOR_INIT_CAPACITY;
        status = SUCCESS;
    }
    return status;
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
    if (v)
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
    if (v)
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
    if (v)
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
    if (v)
    {
        if (item && pos >= 0 && pos < v -> size(v))
        {
            v -> resize(v, v -> size(v) + 1);

            void* source = NULL;
            void* destination = NULL;
            int type_size = v -> get_type_size(v);
            if (type_size != VALUE_ERROR)
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
    if (v)
    {
        if (v -> members.items)
        {
            int size = v -> size(v) - 1;
            item = v -> members.items + size;
            v -> resize(v, size);
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
    if (v)
    {
        if (value)
        {
            int size = v -> size(v);
            status = v -> resize(v, size + 1);
            if (v -> members.items && !status)
            {
                void* position = (char*) v -> members.items + (size * v -> get_item_size(v));
                if (position)
                {
                    //memcpy(position, value, v -> get_item_size(v));
                    status = copy(position, value, v -> get_type_size(v));
                }
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
    if (v)
    {
        if (new_size >= 0)
        {
            v -> members.size = new_size;
            status = SUCCESS;
            if (new_size > v -> capacity(v))
            {
                status = update_capacity(v, new_size * 2 + VECTOR_INIT_CAPACITY);
            }
        }
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
    if (v)
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
    if (v)
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
void vector_init(vector *v, int type_size, int initialSize, int initialCapacity)
{
    if (v)
    {
        // Methods
        v -> assign = vassign;
        v -> at = vat;
        v -> back = vback;
        v -> capacity = vcapacity;
        v -> clear = vclear;
        v -> count = vcount;
        v -> empty = vempty;
        v -> erase_element = verase_element;
        v -> erase_index = verase_index;
        v -> fill = vfill;
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
        v -> members.item_size = VECTOR_DEFAULT_ITEMSIZE;

        if (type_size > 0)
        {
            v -> members.type_size = type_size;
        }
        else
        {
            v -> members.type_size = VECTOR_DEFAULT_TYPESIZE;
        }

        if (initialSize > 0)
        {
            v -> members.size = initialSize;
        }
        else
        {
            v -> members.size = VECTOR_INIT_SIZE;
        }

        if (initialCapacity > 0)
        {
            v -> members.capacity = initialCapacity;
        }
        else
        {
            v -> members.capacity = VECTOR_INIT_CAPACITY;
        }

        int size = v -> size(v);
        int capacity = v -> capacity(v);
        if (size > capacity)
        {
            v -> members.capacity = size + 1;
        }

        v -> members.items = malloc(capacity * v -> get_type_size(v));

        // Initialize
        int value = 0;
        set(v -> members.items, v -> members.items + size, &value, sizeof(value));
    }
}

#endif
