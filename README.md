# DATA STRUCTURE COLLECTION SELF-MADE

General repository for collecting my own implementations of Data Structures using C.

## UTILS.H

During the creation of my DSs, I've been adding some common functions, structs and enumerations that may be found useful for many operations performed within the DSs I am writing. Therefore, here's an overview of what you can find:
+ [enum] exit_codes
+ [enum] boolean
+ [function] compare
+ [function] copy

### [enum] EXIT_CODES
```C
/**
 * Functions exit codes
 */
enum exit_codes {
    VALUE_ERROR = -1,
    SUCCESS,
    FAILURE
};
```

### [enum] BOOLEAN
```C
/**
 * Boolean constants
 */
enum boolean {
    false,
    true
};
```

### [function] COMPARE
```C
/**
 * Compares the first N bytes of the two buffers provided
 *
 * @param a    first buffer
 * @param b    second buffer
 * @param size number of bytes to compare
 * @return status
 */
int compare(const void* a, const void* b, int size)
{
    int status = FAILURE;
    if (a != NULL && b != NULL && size > 0)
    {
        if (sizeof(a) >= size && sizeof(b) >= size)
        {
            const unsigned char* bytes_a = (const unsigned char*) a;
            const unsigned char* bytes_b = (const unsigned char*) b;

            status = SUCCESS;
            int i = 0;
            do {
                if (bytes_a[i] != bytes_b[i])
                {
                    status = FAILURE;
                }
                i++;
            } while (i < size && !status);
        }
    }
    return status;
}
```

### [function] COPY
```C
/**
 * Copies N bytes of memory from src to dst
 *
 * @param dst  pointer to destination
 * @param src  pointer to source
 * @param size number of bytes to copy
 * @return status
 */
int copy(const void* dst, const void* src, int size)
{
    int status = FAILURE;
    if (dst != NULL && src != NULL && size > 0)
    {
        if (sizeof(dst) >= size && sizeof(src) >= size)
        {
            unsigned char* bytes_dst = (unsigned char*) dst;
            unsigned char* bytes_src = (unsigned char*) src;

            int i;
            for (i = 0; i < size; ++i)
            {
                bytes_dst[i] = bytes_src[i];
            }
            status = SUCCESS;
        }
    }
    return status;
}
```

## VECTOR.H

The first DS that I have implemented was a Vector.
A vector is a dinamic array that allows the programmer to dinamically add or remove elements from an array at runtime.
There are many operations you can perform using its functions, so here's an overview:
+ [constant] VECTOR_INIT_CAPACITY, VECTOR_INIT_SIZE, VECTOR_DEFAULT_ITEMSIZE, VECTOR_DEFAULT_TYPESIZE
+ [struct] members
+ [struct] SVector
+ 
+ 
+ 
+ 
+ 
+ 

### USEFUL CONSTANTS
```C
#define VECTOR_INIT_CAPACITY 1
#define VECTOR_INIT_SIZE 0
#define VECTOR_DEFAULT_ITEMSIZE 8
#define VECTOR_DEFAULT_TYPESIZE 8
```

### [struct] MEMBERS
```C
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
```

### [struct] SVECTOR
```C
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
```
