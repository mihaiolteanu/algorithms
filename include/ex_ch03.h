/* ex_ch03 - exercises for skiena algorithms chapter 3 */

#ifndef EX_CH03_H
#define EX_CH03_H

/* 3-1. [3] A common problem for compilers and text editors is determining 
whether the parentheses in a string are balanced and properly nested. For 
example, the string ((())())() contains properly nested pairs of parentheses, 
which the strings )()( and ()) do not. Give an algorithm that returns true if a 
string contains properly nested and balanced parentheses, and false if 
otherwise. For full credit, identify the position of the first offending 
parenthesis if the string is not properly nested and balanced. */
extern void ex_03_01(char *parens);

//#endif // EX_CH03_H
