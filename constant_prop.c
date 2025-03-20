Aim: To write a program for constant propagation.

Description:

The algorithm we shall present basically tries to find for every statement in the program a
mapping between variables, and values of N T ∪⊥ { , } . If a variable is mapped to a constant
number, that number is the variables value in that statement on every execution. If a variable is
mapped to T (top), its value in the statement is not known to be constant, and in the variable is
mapped to ⊥ (bottom), its value is not initialized on every execution, or the statement is
unreachable. The algorithm for assigning the mappings to the statements is an iterative
algorithm, that traverses the control flow graph of the algorithm, and updates each mapping
according to the mapping of the previous statement, and the functionality of the statement. The
traversal is iterative, because non-trivial programs have circles in their control flow graphs, and it
ends when a “fixed-point” is reached – i.e., further iterations don’t change the mappings.


Algorithm:

Step 1: Start
Step 2: Declare a, b, c
Step 3: Initialize avalue and bvalue
Step 4: Display result of propagation
Step 5: Stop




#include <stdio.h>

// Function declaration
int constantpropagation();

int main()  // Changed from void main() to int main()
{
    printf("Result of constant propagation is %d", constantpropagation());
    return 0;  // Return statement for main()
}

int constantpropagation()
{
    int a = 30;
    int b = 3;
    int c;
    c = b * 4;  // c = 3 * 4 = 12
    if (c > 10)    
    {
        c = c - 10;  // c = 12 - 10 = 2
    }
    return c * 2;  // 2 * 2 = 4
}
