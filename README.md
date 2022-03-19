# Perfect_number
A positive integer N is a perfect number if the sum of all its factors excluding itself is N, where a factor is a perfect divisor of N. Let’s examine the following examples.
• Given number 6, we know its factors are 1, 2, and 3 excluding itself. Since 1 + 2 + 3 = 6, 6 is a perfect number.
• Given number 28, its factors are 1, 2, 4, 7, and 14 excluding itself, and since 1+2+4+7+14 = 28, 28 is also a perfect number.
• Given number 496, its factors are 1, 2, 4, 8, 16, 31, 62, 124, and 248 excluding itself, and since 496 = 1 + 2 + 4 + 8 + 16 + 31 + 62 + 124 + 248, 496 is too a perfect number.
• Given number 30, its factors are 1, 2, 3, 5, 6, 10, and 15 excluding itself, since 1 + 2 + 3 + 5 + 6 + 10 + 15 = 42 ̸= 30, 30 isn’t a perfect number.


Two programs are used to check whether a number is a perfect number:
1. A serial program which does the work in the program serially.
2. A parallel program which can run on one or multiple threads. This program can split the computation tasks to multiple parts, each thread can do different parts, and at last, the calling thread (parent thread) combines the results from different threads and get a conclusion about whether a number is a perfect number.
