/* @file
 * @brief This file contains all functions done by Dillon Roller. This 
 * includes: Polynomial constructor(unsigned value), operator+, operator+=, 
 * operator<<, and compare functions. 
 * */
#include "largeint.h"

/*******************************************************
 *      Function Prototypes for ASL Functions
 *******************************************************/
ListNode* asl_new( int coeff = 0, int power = 0, ListNode* next = nullptr, 
    ListNode* prev = nullptr );
void asl_delete( ListNode* delnode );


/********************************************************
 * @author Dillon Roller
 *
 * @par Description: Instantiates and initializes a polynomial
 *
 * @params[in]  value - integer passed in to be stored as polynomial
 *
 * @returns none
 *
 * *****************************************************/
Polynomial::Polynomial( unsigned value )
{
    vector<int> num; //store digit values
    
    //special case value = 0
    if ( value == 0 )
    {
        head = asl_new( 0, 0 );
        tail = head;
        return;
    }
    while( value != 0 )
    {
        num.push_back(value % 10);
        value /= 10;
    }
    //store number using linked list
    //store most significant digit 
    head = asl_new( num[num.size() - 1], num.size() - 1 );
    ListNode* cur = head;
    
    //store remaining digits
    for (int i = num.size() - 2; i >= 0; i--)
    {
        cur->next = asl_new( num[i], i, nullptr, cur );
        cur = cur->next;
    }
    tail = cur;
}

/********************************************************
 * @author Dillon Roller
 *
 * @par Description: Adds two LargeInts together by adding each coefficient
 * of each polynomial to each other that has the same power of 10, accounting 
 * for carries. The resultant sum is a polynomial that is stored in a newly
 * created LargeInt
 *
 * @params[in]  lhs - first LargeInt to be added
 * @params[in]  rhs - second LargeInt to be added
 *
 * @returns A reference to sum (LargeInt holding sum)
 *
 * *****************************************************/
const LargeInt& operator+( const LargeInt& lhs, const LargeInt& rhs )
{
    LargeInt* sum = new(nothrow) LargeInt();
    int pow = 1, carry = 0, coeff;
    ListNode *gtptr = lhs.tail;
    ListNode *ltptr = rhs.tail;
    
    
    //set greaterptr and lesserptr to appropriate LargeInts
    if ( rhs > lhs )
    {
        gtptr = rhs.tail;
        ltptr = lhs.tail;
    }

    ListNode* curr = sum->tail;

    //handles first digit
    coeff = gtptr->coeff + ltptr->coeff;
    carry = coeff / 10;
    curr->coeff = coeff - ( carry * 10 );
    gtptr = gtptr->prev;
    ltptr = ltptr->prev;
    
    //Add until we run out of digits in the lesser LargeInt
    while ( ltptr != nullptr )
    {
        coeff = gtptr->coeff + ltptr->coeff + carry;
        carry = coeff / 10;
        curr->prev = asl_new ( coeff - ( carry * 10 ), pow++, curr );
        
        gtptr = gtptr->prev;
        ltptr = ltptr->prev;
        curr = curr->prev;
    }
    
    //Add remaining digits of greater LargeInt onto new sum, accounting for
    //carry
    while ( gtptr != nullptr )
    {
        coeff = gtptr->coeff + carry;
        carry = coeff / 10;
        coeff = coeff - ( carry * 10 );

        curr->prev = asl_new( coeff, pow++, curr );
     
        gtptr = gtptr->prev;
        curr = curr->prev;
    }
    
    //allocate an additional new node if MSD needs a carry
    if ( carry != 0 )
    {
        curr->prev = asl_new( carry, pow, curr );
     
        curr = curr->prev;
    }
    
    //Associate new polynomial with LargeInt
    sum->head = curr;
    return *sum;
}

/********************************************************
 * @author Dillon Roller
 *
 * @par Description: Outputs LargeInt to given ostream
 *
 * @params[in]  out - ostream to output LargeInt to
 * @params[in]  num - LargeInt to output
 *
 * @returns a reference to out (for chaining purposes)
 *
 * *****************************************************/
ostream& operator<<( ostream& out, const LargeInt& num )
{ 
    ListNode* temp = num.head;
    while( temp != nullptr )
    {
        out << temp->coeff;
        temp = temp->next;
    }
    return out;
}

/********************************************************
 * @author Dillon Roller
 *
 * @par Description: Given a LargeInt, compares it to the current instance of
 * this LargeInt (*this) and determines if 'this' LargeInt is less than, greater
 * than, or equal to the one given. 
 *
 * @params[in]  num - LargeInt to compare to 'this' LargeInt
 *
 * @returns -1 - 'this' is less than LargeInt given
 * @returns 0 - 'this' is equal to LargeInt given
 * @returns 1 - 'this' is greater than LargeInt given
 *
 * *****************************************************/
int LargeInt::compare( const LargeInt& num ) const
{
    ListNode* lhs = this->head;
    ListNode* rhs = num.head;
    
    //if powers are equal, compare each coeff until one is less than another or 
    //until nullptr is reached
    if ( lhs->power == rhs->power )
    {
        while( lhs != nullptr && rhs != nullptr )
        {
            if ( lhs->coeff > rhs->coeff ) 
                return 1;
            if ( lhs->coeff < rhs->coeff )
                return -1;
            lhs = lhs->next;
            rhs = rhs->next;
        }
        return 0;
    }
    
    //if power are not equal, determine which is greater by comparing powers
    else if ( lhs->power > rhs->power )
        return 1;
    else
        return -1;
}

/********************************************************
 * @author Dillon Roller
 *
 * @par Description: Overloads += operator. Adds a LargeInt to 'this' LargeInt
 * and stores it back into 'this' 
 *
 * @params[in]  rhs - LargeInt to be added to 'this'
 *
 * @returns reference to new sum(for chaining purposes)
 *
 * *****************************************************/
const LargeInt& LargeInt::operator+=( const LargeInt& rhs )
{
    return *this = *this + rhs;
}


