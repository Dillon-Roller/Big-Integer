/* @file
 * @brief cgfunc.cpp contains Polynomial and LargeInt class members functions
 * written by C Gaddi:
 * ~Polynomial(), Polynomial( const Polynomial& ), print(), Polynomial( string ),
 * Polynomial( const Polynomial& ), freePoly(), operator=( const LargeInt& ),
 * operator*=( const LargeInt& ), operator>>( istream&, LargeInt& ), and all 
 * of the overloaded comparison implemtations.
 * */

#include "largeint.h"

/*******************************************************
 *      Function Prototypes for ASL Functions
 *******************************************************/
ListNode* asl_new( int coeff = 0, int power = 0, ListNode* next = nullptr,
        ListNode* prev = nullptr );
void asl_delete( ListNode* delnode );


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Destructor for the class Polynomial. Calls the
 * freePoly() function.
 *
 * @params  none
 *
 * @returns none
 *
 * *****************************************************/
Polynomial::~Polynomial()
{
    freePoly();
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Copy constructor for the class Polynomial. Calls the
 * freePoly() function.
 *
 * @params[in]  poly - Polynomial object to be copied
 *
 * @returns none
 *
 * *****************************************************/
Polynomial::Polynomial ( const Polynomial& poly  )
{
    copyPoly ( poly );
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * print() traverses through all the nodes of the
 * Polynomial and prints out contents. Can only be called
 * by class objects.
 *
 * @params  none
 *
 * @returns none
 *
 * *****************************************************/
void Polynomial::print() const
{
    ListNode* temp = head;

    //prints all digits of the LargeInt
    while ( temp != nullptr )
    {
        cout << temp -> coeff;

        temp = temp -> next;
    }
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Polynomial constructor for string inputs. Converts
 * each character of the string into an integer and
 * stores into Polynomial. 
 *
 * @params[in]  value - string containing large integer
 *
 * @returns none
 *
 * *****************************************************/
Polynomial::Polynomial ( string value )
{
    //handles first node
    tail = asl_new ( atoi( &value.back() ) );
    value.pop_back();

    ListNode* curr = tail;
    int pow = 1;

    //creates the nodes for the Polynomial, storing the
    //integer converted characters
    while ( !value.empty() )
    {
        curr ->prev = asl_new( atoi( &value.back()), pow, curr );
        value.pop_back();
        pow++;
        curr = curr ->prev;
    }

    head = curr;
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * copyPoly frees up the polynomial that made the
 * function call and creates a hard copy of the data
 * passed in by poly. 
 *
 * @params[in]  poly - polynomial to be copied
 *
 * @returns none
 *
 * *****************************************************/
void Polynomial::copyPoly( const Polynomial & poly )
{
    freePoly();

    //handles first digit of integer
    head = asl_new( poly.head ->coeff, poly.head ->power );

    //handles one digit integers
    if ( poly.head == poly.tail )
    {
        tail = head;
        return;
    }

    //declaration of traversal nodes
    ListNode* curr = head;
    ListNode* curr2 = poly.head ->next;

    //copy contents of LargeInt p to *this
    while ( curr2 != nullptr )
    {
        curr ->next = asl_new( curr2 ->coeff, curr2 ->power, nullptr, curr );
        curr = curr ->next;
        curr2 = curr2 ->next;
    }

    //assigns tail to last digit of integer
    tail = curr;
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * freePoly traverses through the polynomial and calls
 * asl_delete to push nodes onto the asl stack and
 * remove them from the polynomial that called the
 * function.  
 *
 * @params  none
 *
 * @returns none
 *
 * *****************************************************/
void Polynomial::freePoly()
{
    //handles empty polynomials
    if ( head == nullptr && tail == nullptr )
        return;

    //declaration of traversal node pointer
    ListNode* temp = head ->next;
    
    //deletes all nodes
    while ( temp != nullptr )
    {
        asl_delete( temp ->prev );
        temp = temp ->next;
    }

    asl_delete( head );
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the = operator makes a copy of the passed
 * LargeInt and returns the LargeInt with the copied
 * values. 
 *
 * @params[in]  integer - integer to be copied
 *
 * @returns none
 *
 * *****************************************************/
const LargeInt& LargeInt::operator=( const LargeInt& integer )
{
    //makes copy of LargeInt and returns current object
    copyPoly ( integer );
    return *this;
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the >> operator inputs a string type from
 * the console and calls the overloaded string constructor
 * to create the object type and returns the istream.
 *
 * @params[in]  in - istream for input
 * @params[in]  p - object to store input
 *
 * @returns in - istream
 *
 * *****************************************************/
istream & operator>>( istream &in, LargeInt& p )
{
    //reads in integer creates LargeInt object and assigns p equal to object
    string num;

    cin >> num;

    LargeInt q ( num );

    p = q;

    return in;
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the * operator takes in two LargeInt objects to be multiplied.
 * and assigns pointers to traverse through each. It then creates two
 * temporary LargeInts to record current factor and a running sum. Starting
 * at the 0th power of the multiplier, it creates a factor and adds it to the
 * running sum of all the factors.
 *
 * @params[in]  lhs - LargeInt multiplicand
 * @params[in]  rhs - LargeInt multiplier
 *
 * @returns sumptr - pointer the the LargeInt holding the sum of all factors
 *
 * *****************************************************/
const LargeInt& operator*( const LargeInt& lhs, const LargeInt& rhs )
{
    //declaration of traversal nodes
    ListNode *cand = nullptr;
    ListNode *plier = rhs.tail;

    //declaration of temporary LargeInt and supporting variables to calculate
    //factors and addends
    LargeInt* factor = new ( nothrow ) LargeInt;
    LargeInt* sum = new ( nothrow ) LargeInt;
    ListNode* fact = nullptr;
    int carry, num, pow;

    //loops through and one digit of the multiplier at a time
    while ( plier != nullptr )
    {
        //initialize new factor
        carry = 0;
        cand = lhs.tail;
        pow = plier ->power;

        factor ->tail = asl_new();
        fact = factor ->tail;

        //if multiplier is not the last digit, create nodes with coefficient 0
        //to offset addend to correct position
        if ( pow != 0 )
        {
            for ( int i = 1; i < pow; i++ )
            {
                fact ->prev= asl_new( 0, i, fact );
                fact = fact ->prev;
            }
        }

        else
        {
            //calculate product
            num = plier -> coeff * cand -> coeff + carry;

            //calculate overflow to next product
            carry = num / 10;


            //calculate single digit to store as coefficient
            fact -> coeff = num - ( carry * 10 );

            //interate to next digit
            pow++;
            cand = cand -> prev;
        }
    
        //calculate products of each digit of the multicand
        while ( cand != nullptr )
        {
            //create product of the multiplier with each of the multicand's
            //digits and store into factor LargeInt
            num = plier -> coeff * cand -> coeff + carry;
            carry = num / 10;
            num = num - ( carry * 10 );

            fact -> prev = asl_new( num, pow, fact );

            fact = fact -> prev;
            pow++;
            cand = cand -> prev;
        }

        //create new node for the last carry of the factor
        if ( carry != 0 )
        {
            fact ->prev = asl_new( carry, pow, fact );
            fact = fact ->prev;
        }
    
        factor ->head = fact;

        //update sum
        *sum = *sum + *factor;

        factor ->freePoly();

        //iterate to next digit of the multiplier
        plier = plier -> prev;
    }

    //create new object to pass LargeInt back to main function
    LargeInt &sumptr = *sum;
    return sumptr;
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the == operator calls and compares the result from the compare
 * function and returns the boolean result.
 *
 * @params[in]  lhs - LargeInt to the left of the operator
 * @params[in]  rhs - LargeInt to the right of the operator
 *
 * @returns boolean result of the comparison
 *
 * *****************************************************/
bool operator==( const LargeInt& lhs, const LargeInt& rhs )
{
    return ( lhs.compare ( rhs ) == 0 );
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the > operator calls and compares the result from the compare
 * function and returns the boolean result.
 *
 * @params[in]  lhs - LargeInt to the left of the operator
 * @params[in]  rhs - LargeInt to the right of the operator
 *
 * @returns boolean result of the comparison
 *
 * *****************************************************/
bool operator>( const LargeInt& lhs, const LargeInt& rhs )
{
    return ( lhs.compare ( rhs ) == 1 );
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the >= operator calls and compares the result from the compare
 * function and returns the boolean result.
 *
 * @params[in]  lhs - LargeInt to the left of the operator
 * @params[in]  rhs - LargeInt to the right of the operator
 *
 * @returns boolean result of the comparison
 *
 * *****************************************************/
bool operator>=( const LargeInt& lhs, const LargeInt& rhs )
{
    return ( lhs.compare ( rhs ) >= 0 );
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the != operator calls and compares the result from the compare
 * function and returns the boolean result.
 *
 * @params[in]  lhs - LargeInt to the left of the operator
 * @params[in]  rhs - LargeInt to the right of the operator
 *
 * @returns boolean result of the comparison
 *
 * *****************************************************/
bool operator!=( const LargeInt& lhs, const LargeInt& rhs )
{
    return ( lhs.compare ( rhs ) != 0 );
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the < operator calls and compares the result from the compare
 * function and returns the boolean result.
 *
 * @params[in]  lhs - LargeInt to the left of the operator
 * @params[in]  rhs - LargeInt to the right of the operator
 *
 * @returns boolean result of the comparison
 *
 * *****************************************************/
bool operator<( const LargeInt& lhs, const LargeInt& rhs )
{
    return ( lhs.compare ( rhs ) == -1 );
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the <= operator calls and compares the result from the compare
 * function and returns the boolean result.
 *
 * @params[in]  lhs - LargeInt to the left of the operator
 * @params[in]  rhs - LargeInt to the right of the operator
 *
 * @returns boolean result of the comparison
 *
 * *****************************************************/
bool operator<=( const LargeInt& lhs, const LargeInt& rhs )
{
    return ( lhs.compare ( rhs ) <= 0 );
}


/********************************************************
 * @author Chezka Gaddi
 *
 * @par Description: 
 * Overloading the *= operator calls the overloaded * operator and assigns
 * the result to the the LargeInt that called the function.
 *
 * @params[in]  rhs - LargeInt to the right of the operator
 *
 * @returns *this - pointer to the LargeInt with the product of it and rhs
 *
 * *****************************************************/
const LargeInt& LargeInt::operator*=( const LargeInt& rhs )
{
    return *this = *this * rhs;
}
