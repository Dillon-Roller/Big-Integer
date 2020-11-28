/* @file
 * @brief Contains LargeInt and Polynomial class interface
 * */

/*
    ***** largeint.h *****

Interface for a large integer class in C++.
Large integers are implemented using polynomials stored in linked lists.

Author: John M. Weiss, Ph.D.
Class:  CSC 315 Data Structures & Algorithms (PA#1)
Date:   Spring 2018

Note:
This file contains the class interfaces for a base Polynomial class and
an inherited LargeInt class. Do not change these class interfaces!
You must write the implementation, notably the Polynomial functions
copyPoly() and freePoly(), the LargeInt function compare(), and the
LargeInt operator functions +, *, >>, <<.
*/

//-----------------------------------------------------------------------------

// prevent multiple includes
#ifndef _LARGEINT_
#define _LARGEINT_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//-----------------------------------------------------------------------------

/*!
* @brief Struct to hold information for each polynomial
*/
struct ListNode
{
    int coeff, power;
    ListNode *next, *prev;
    // constructor makes node initialization easier
    ListNode( int c = 0, int p = 0, ListNode *n = nullptr, 
    ListNode *pr = nullptr ) : coeff( c ), power( p ), next( n ), prev( pr ) { }
};

//-----------------------------------------------------------------------------

/*!
* @brief Polynomial class that holds the polynomial in a Linked List 
*/

class Polynomial
{
    protected:                 // private except for inherited classes
        // data members
        ListNode* head = nullptr; /*!< Pointer to beginning of number in LL*/
        ListNode* tail = nullptr; /*!< Pointer to end of number in LL*/      

        // member functions that are only called by other member functions
        void copyPoly( const Polynomial & );
        void freePoly();

    public:                   // public class interface
        // constructor and destructor functions
        Polynomial( unsigned value = 0 );       // constructor: initialize Polynomial to int (default 0)
	    Polynomial ( string value );            // constructor: takes in string and converts to polynomial
        Polynomial( const Polynomial & );       // copy constructor: initialize Polynomial to Polynomial
        ~Polynomial();                          // destructor: deallocate linked list nodes

        // print() method (for debugging purposes)
        void print() const;
};

//-----------------------------------------------------------------------------

/*!
* @brief LargeInt class that can store really big integers using Polynomial
*/
class LargeInt : public Polynomial
{
    private:                   // only accessible to member functions
        // compare function is called by relational operators
        int compare( const LargeInt& ) const;

    public:                    // class interface
        // constructors and destructors are inherited from Polynomial class,
        // but we need to pass arguments to Polynomial constructors:
        LargeInt( unsigned value = 0 ) : Polynomial( value ) { }
        LargeInt( string value ) : Polynomial( value ) { }
        LargeInt( const LargeInt& Q ) : Polynomial( Q ) { }

        // addition and multiplication operators: P + Q, P * Q
        // use friend functions to allow P + 43, 43 + P, etc.
        friend const LargeInt& operator+( const LargeInt&, const LargeInt& );
        friend const LargeInt& operator*( const LargeInt&, const LargeInt& );

        // assignment operators: P = Q, P += Q, P *= Q
        
        
        const LargeInt& operator=( const LargeInt& );
        const LargeInt& operator+=( const LargeInt& );
        const LargeInt& operator*=( const LargeInt& );

        // relational comparison operators: P == Q, P < Q, etc.
        // use friend functions to allow P == 43, 43 == P, etc.
        
        friend bool operator==( const LargeInt&, const LargeInt& );
        friend bool operator!=( const LargeInt&, const LargeInt& );
        friend bool operator<=( const LargeInt&, const LargeInt& );
        friend bool operator>=( const LargeInt&, const LargeInt& );
        friend bool operator<( const LargeInt&, const LargeInt& );
        friend bool operator>( const LargeInt&, const LargeInt& );
        
        // input/output operators: cin >> P, cout << P
        friend istream & operator>>( istream &, LargeInt& );
        friend ostream & operator<<( ostream &, const LargeInt& );
        
        
//-------------------------------------
        
};



// end of the multiple includes preprocessor directive
#endif

//-----------------------------------------------------------------------------#pragma once
