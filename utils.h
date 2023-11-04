/**
 * @file    utils.h - Set of utilities such as functions and structs
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @version 0.2
 * @date    2023-11-04
 * 
 * @copyright Copyright (c) 2023
 */

#ifndef UTILS_H
#define UTILS_H

#pragma once

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

#endif