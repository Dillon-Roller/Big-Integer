/* @file
 * @brief This file contains functions to handle using available space list
 * */
#include "largeint.h"

/*!
* @brief pointer to the top of ASL stack
*/
static ListNode* g_asl = nullptr; 

/********************************************************
 * @author Chezka Gaddi, Dillon Roller
 *
 * @par Description: 
 * Pops a node from the ASL stack and uses this node instead of calling
 * the new operator. If nothing is on the stack, the new operator is called
 *
 * @params[in]  coeff - number to be stored into node
 * @params[in]  power - 10^power of the coeff
 * @params[in]  next  - pointer to next number in ListNode
 * @params[in]  prev  - pointer to previous number in ListNode
 *
 * @returns newnode - node popped from stack
 * @returns new ListNode - returns a new ListNode using new operator if 
 *                         nothing to pop
 *
 * *****************************************************/
ListNode* asl_new( int coeff, int power, ListNode* next, ListNode* prev )
{
    if( g_asl != nullptr )
    {
        ListNode* newnode = g_asl;

        newnode ->coeff = coeff;
        newnode ->power = power;
        newnode ->next = next;
        newnode ->prev = prev;
        g_asl = g_asl ->next;

        return newnode;
    }

    return new ( nothrow ) ListNode ( coeff, power, next, prev );
}

/********************************************************
 * @author Chezka Gaddi, Dillon Roller
 *
 * @par Description: 
 * Pushes node onto ASL stack so that it can be used later on in the 
 * program by calling asl_new
 *
 * @params[in]  delnode - node to be pushed to ASL stack
 *
 * @returns none
 *
 * *****************************************************/
void asl_delete ( ListNode* delnode ) 
{
    delnode ->next = g_asl;
    g_asl = delnode;
} 
