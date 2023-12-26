/**
 * @file    utils.h - Set of utilities
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.4
 * @date    2023-12-23
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef UTILS_H
#define UTILS_H

#pragma once

#define min(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })

/**
 * Functions exit codes
 */
enum exit_codes {
    VALUE_ERROR = -1,
    SUCCESS,
    FAILURE
};

/**
 * Boolean constants
 */
enum boolean {
    false,
    true
};

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
    if (a && b && size > 0)
    {
        status = SUCCESS;
        const unsigned char* bytes_a = (const unsigned char*) a;
        const unsigned char* bytes_b = (const unsigned char*) b;
        int i = 0;
        while (i < size && !status)
        {
            status = (bytes_a[i] != bytes_b[i]);
            i++;
        }
    }
    return status;
}

/**
 * Copies N bytes of memory from src to dst
 *
 * @param dst  pointer to destination
 * @param src  pointer to source
 * @param size number of bytes to copy
 * @return status
 */
int copy(const void* dst, const void* src, size_t size)
{
    int status = FAILURE;
    if (dst && src && size > 0)
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
    return status;
}

/**
 * Sets all bytes in the interval [start, end) to the specified value
 *
 * @param start pointer to the first byte
 * @param end pointer after the last byte
 * @param value value to copy
 * @param value_size size of the value
 * @return status - number of copies which went wrong
 */
int set(const void* start, const void* end, const void* value, size_t value_size)
{
    int status = FAILURE;
    if (start && end && value)
    {
        status = SUCCESS;
        long long bytes = end - start;
        size_t i;
        for (i = 0; i < bytes; i += value_size)
        {
            value_size = min(value_size, bytes - i);
            status += copy(start + i, value, value_size);
        }
    }
    return status;
}

/**
 * Swaps two elements
 *
 * @param a first element to swap
 * @param b second element to swap
 * @param size number of bytes to consider
 * @return status
 */
int swap(void* a, void* b, int size)
{
    int status = FAILURE;
    if (a && b && size > 0)
    {
        status = SUCCESS;
        void* temp;
        status |= copy(temp, a, size);
        status |= copy(a, b, size);
        status |= copy(b, temp, size);
    }
    return status;
}

#endif