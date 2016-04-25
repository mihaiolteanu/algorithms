/* e_03.h - exercises for chapter 3 */

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

/* 3-10. [5] In the bin-packing problem, we are given n metal objects, each 
weighing between zero and one kilogram. Our goal is to find the smallest number 
of bins that will hold the n objects, with each bin holding one kilogram at 
most.
• The best-fit heuristic for bin packing is as follows. Consider the objects 
in the order in which they are given. For each object, place it into the 
partially filled bin with the smallest amount of extra room after the object is 
inserted.. If no such bin exists, start a new bin. Design an algorithm that 
implements the best-fit heuristic (taking as input the n weights w1, w2, ...,wn 
and outputting the number of bins used) in O(n log n) time.
• Repeat the above using the worst-fit heuristic, where we put the next 
object in the partially filled bin with the largest amount of extra room after 
the object is inserted. */
extern int e_03_10(int nobjects, ...);

#endif // EX_CH03_H
