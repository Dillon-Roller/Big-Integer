/***************************************************************************//**
 * @file 
 * @brief main function that test the Polynomial and LargeInt ADTs.
 *
 * @mainpage Programming Assignment # 1 - Large Integers in C++
 *
 * @section course_section Course Information
 *
 * @authors Chezka Gaddi
 * @authors	Dillon Roller
 *
 * @date February 19, 2018
 *
 * @par Instructor:
 *         Dr. Weiss
 *
 * @par Course:
 *         CSC 315 - 10:00
 *
 * @par Location:
 *         McLaury - Room 315
 *
 * @section program_section Program Information
 *
 * @details This programs creates a LargeInt ADT that is inherited from the
 * Polynomial ADT and tets various operations that can be done to a large
 * interger such as add, multiply, compare. 
 *
 * The Polynomial ADT contains two constructors, one that takes in an unsigned
 * intger value and one that takes in a string representation of the large
 * integer. Both of the contructor parses the data to individual digits and
 * stores the digits and its power in the form of a linked list. The Polynomial
 * ADT also had a copy contructor that creates a hard copy of the polynomial, a
 * destructor to free the object and also a print function that would output
 * the contents of the ADT to the screen.
 *
 * The LargeInt ADT is inherited from the Polynomial ADT and contains all of
 * functions that the Polynomial ADT has and in additon contains extra
 * operations that can be done to large integers. Operations like comparison,
 * addition, and multiplication. Other operations that can be done with the
 * LargeInt ADT includes inputing from the console into the object, assignments
 * of one LargeInt to another and also outputting the ADT to the console.
 *
 * Utilized in this program is an available space list. Called in replacement
 * for the new and delete operations of pointers, the available space list
 * pushed nodes to be deleted onto a stack and takes from that same stack when
 * a new node is needed to be created.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      $ make
 *		$ pa1
 *
 * @par Usage:
   @verbatim
   c:\> pa1
   d:\> c:\bin\pa1
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug  none
 *
 * @todo none
 *
 * @par Modifications and Development Timeline:
   @verbatim
   https://gitlab.mcs.sdsmt.edu/7180120/CSC315_PA1.git 
   @endverbatim
 *
 ******************************************************************************//*
    ***** pa1.cpp *****

Application to test the C++ large integer class.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures & Algorithms (PA#1)
Date:   Spring 2018

Modifications:
*/

//-----------------------------------------------------------------------------

#include <iostream>
using namespace std;

#include "largeint.h"

//-----------------------------------------------------------------------------
//          ***** main program to test LargeInt class *****
//-----------------------------------------------------------------------------

int main( int argc, char *argv[] )
{
    // test constructors
    LargeInt P( 10023 );
    LargeInt Q( P );
    cout << "P: " << P << endl;
    cout << "Q: " << Q << endl;
    cout << endl;

    // test input/output operators
    LargeInt value1, value2;
    cout << "Please enter two LargeInt values:" << endl;
    cin >> value1 >> value2;
    cout << endl;
    cout << "value1: " << value1 << endl;
    cout << "value2: " << value2 << endl;
    cout << endl;

    // test relational operators
    if ( value1 < value2 )
        cout << "value1 is less than value2" << endl;
    else if ( value1 == value2 )
        cout << "value1 is equal to value2" << endl;
    else
        cout << "value1 is greater than value2" << endl;
    cout << endl;

    // test addition and assignment operators
    LargeInt sum = value1 + value2;
    LargeInt product = value1 * value2;
    cout << "sum:     " << sum << endl;
    cout << "product: " << product << endl;
    cout << endl;

    sum = value1;
    sum += value2;
    cout << "value1 += value2: " << sum << endl;
    product = value1;
    product *= value2;
    cout << "value1 *= value2: " << product << endl;
    cout << endl;

    cout << "value1: " << value1 << endl;
    cout << "value2: " << value2 << endl;
    cout << endl;

    return 0;
}
