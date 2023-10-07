/**
 * @file    vector.c - Struct for dynamic array in C
 * @author  Vincenzo Cardea (vincenzo.cardea.05@gmail.com)
 * @brief 
 * @version 0.1
 * @date    2023-10-06
 * 
 * @copyright Copyright (c) 2023
 */

/**
 * pointer* begin() - iterator
 * pointer* end() - iterator
 * 
 * int size() - number of elements
 * void resize(N) - resize the vector
 * int capacity() - amount of memory allocated
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

typedef struct {
    short value = 0;
    *short self_iterator;
} element;

typedef struct {
    
    
} vector_short;
