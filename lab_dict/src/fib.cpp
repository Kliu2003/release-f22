/**
 * @file fib.cpp
 * Contains Fibonacci-number generating functions both utilizing and not
 * utilizing memoization.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "fib.h"

#include <map>
#include <iostream>

using std::map;

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long fib(unsigned long n)
{
    /* Your code goes here! */
    if(n == 0){
        return 0;
    }
    long prev0 = 0;
    long prev1 = 1;
    for(unsigned i = 2; i <= n; i++){
        long temp = prev0;
        prev0 = prev1;
        prev1 = temp + prev1;
    }
    return prev1;
}

/**
 * Calculates the nth Fibonacci number where the zeroth is defined to be
 * 0. This version utilizes memoization.
 * @param n Which number to generate.
 * @return The nth Fibonacci number.
 */
unsigned long memoized_fib(unsigned long n)
{
    /* Your code goes here! */
    long prev0 = 0;
    long prev1 = 1;
    for(unsigned i = 2; i <= n; i++){
        long temp = prev0;
        prev0 = prev1;
        prev1 = temp + prev1;
    }
    return prev1;
}
