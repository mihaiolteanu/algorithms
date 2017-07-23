/* e_03.h - exercises for chapter 3 */

#ifndef EX_CH03_H
#define EX_CH03_H

#include "bst.h"
#include "list.h"

/* 3-1. [3] A common problem for compilers and text editors is determining 
whether the parentheses in a string are balanced and properly nested. For 
example, the string ((())())() contains properly nested pairs of parentheses, 
which the strings )()( and ()) do not. Give an algorithm that returns true if a 
string contains properly nested and balanced parentheses, and false if 
otherwise. For full credit, identify the position of the first offending 
parenthesis if the string is not properly nested and balanced. */
extern int e03_01(char *parens);

extern void e03_02(list *l);

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

/* Take a number of objects and return the number of buckets filled with a
 * best-fit heuristic  For ease of implementation, consider the weights between
 * 1 and 10 units, not between 0 and 1. The implementation uses a normal bst
 * (non-balanced) and looks for the node to be filled. If no node is found, a
 * new node is inserted. If a node is found and filled, the found node and all
 * its children is detached from the tree and each node is reinserted into the
 * tree in a breadth-first order. */
extern int e_03_10_best_fit(int nobjects, ...);

/* 3-11. [5] Suppose that we are given a sequence of n values x1, x2, ..., xn
 * and seek to quickly answer repeated queries of the form: given i and j, find
 * the smallest value in xi, . . . , xj. 
 
 (a) Design a data structure that uses O(n2) space and answers queries in O(1) 
 time.
 (b) Design a data structure that uses O(n) space and answers queries in 
 O(log n) time. For partial credit, your data structure can use O(n log n) space
 and have O(log n) query time. */

/* Use a matrix. */
extern int e_03_11_a(int i, int j, int count, ...);

/* Use an interval bst. */
extern int e_03_11_b(int i, int j, int count, ...);


/* 3-13. [5] Let A[1..n] be an array of real numbers. Design an algorithm to
 * perform any sequence of the following operations:
 • Add(i,y) – Add the value y to the ith number.
 • Partial-sum(i) – Return the sum of the first i numbers, i.e.
 There are no insertions or deletions; the only change is to the values of the
 numbers. Each operation should take O(log n) steps. You may use one additional
 array of size n as a work space. */

extern void e_03_13_init(bst *b, int count, ...);
extern void e_03_13_add(bst *b, int y, int n);
extern int e_03_13_partial_sum(bst *b, int n);
#endif // EX_CH03_H
