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
#define VECTOR_DEFAULT_TYPESIZE 8

/**
 * Exit codes of functions
 */
enum exit_codes {
    SUCCESS,
    FAILURE
};

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
    if (v != NULL && value != NULL)
    {
        if (index >= 0 && index < v -> size(v))
        {
            void* destination = v -> members.items + index;
            size_t size = v -> get_item_size(v);
            memcpy(destination, value, size);
            status = memcmp(destination, value, size);
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
    if (v != NULL)
    {
        if (index >= 0 && index < v -> size(v))
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
    void* value = NULL;
    if (v != NULL)
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
    int capacity = -1;
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
    int bool = 0;
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
    if (v != NULL && element != NULL && !v -> empty(v))
    {
        int index = v -> find(v, element);
        if (index != -1)
        {
            void* source = NULL;
            void* destination = NULL;
            int i;
            for (i = index + 1; i < v -> size(v); ++i)
            {
                source = v -> members.items + i;
                destination = v -> members.items + (i - 1);
                memcpy(destination, source, v -> get_item_size(v));
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
 * @param  index of the element to remove
 * @return status
*/
int verase_index(vector* v, int index)
{
    int status = FAILURE;
    if (v != NULL && index >= 0 && index < v -> size(v))
    {
        void* destination = NULL;
        void* source = NULL;
        size_t size = v -> get_item_size(v);
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
 * Finds the first occurrence of a value within the vector
 *
 * @return index of the first value
 */
int vfind(vector* v, const void* value)
{
    int index = -1;
    if (v != NULL && value != NULL)
    {
        size_t size = v -> get_type_size(v);
        int found = 0;
        int i = 0;
        void* item = NULL;
        while (i < v -> size(v) && !found)
        {
            item = v -> members.items + i;
            found = (memcmp(item, value, size) == 0);
            ++i;
        }

        if (found)
        {
            index = i - 1;
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
    void* value = NULL;
    if (v != NULL && !v -> empty(v))
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
    int item_size = -1;
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
    int type_size = -1;
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
            size_t size = v -> get_item_size(v);
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
    if (v != NULL)
    {
        int size = v -> size(v);
        status = v -> resize(v, size + 1);
        if (v -> members.items != NULL && !status)
        {
            void* position = (char*) v -> members.items + (size * v -> get_item_size(v));
            memcpy(position, value, v -> get_item_size(v));
            status = SUCCESS;
        }
        else
        {
            status = FAILURE;
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
    int size = -1;
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
void vector_init(vector *v, int item_size, int type_size, int initialCapacity)
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

        if (item_size > 0)
        {
            v -> members.item_size = item_size;
        }
        else
        {
            v -> members.item_size = VECTOR_DEFAULT_ITEMSIZE;
        }

        if (type_size > 0)
        {
            v -> members.type_size = type_size;
        }
        else
        {
            v -> members.type_size = VECTOR_DEFAULT_TYPESIZE;
        }

        if (initialCapacity > 0)
        {
            v -> members.capacity = initialCapacity;
        }
        else
        {
            v -> members.capacity = VECTOR_INIT_CAPACITY;
        }

        if (v -> members.capacity > 0 && v -> members.type_size)
        {
            v -> members.items = malloc(v -> members.capacity * v -> members.item_size);
        }
    }
}
