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
