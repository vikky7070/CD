Aim: To design predictive parser for the given language.

Description : 
A Predictive Parser is a type of top-down parser that efficiently analyzes input strings without 
backtracking.It is typically used for LL(1) grammars, meaning it processes input left to right, derives the leftmost 
derivation, and makes decisions based on a single lookahead symbol. Predictive parsing can be implemented using 
either a recursive descent approach or a table-driven method. The parser starts with the grammars start symbol and 
uses the lookahead symbol to select the appropriate production rule from a parsing table
It then replaces the non-terminal on the stack with the chosen production and continues 
the process until the entire input string is parsed. This method ensures efficient and 
deterministic parsing, making it ideal for simple, unambiguous grammars. However, it does not work well 
with left-recursive or ambiguous grammars, which require modifications like left recursion elimination and left factoring.


Algorithm:
Step 1: Start
Step 2: Read the input string.
Step 3: X symbol on top of stack, a current input symbol
Step 4: Stack contents and remaining input called parser configuration (initially $S on stack and
complete input string)
Step 5: If X=a=$ halt and announce success
Step 6: If X=a≠$ pop X off stack advance input to next symbol
Step 7: If X is a non-terminal use M[X ,a] which contains production
Step 8: X->RHS or error replace X on stack with rhs or call error routine, respectively.
EX: X->UVW replace X with WVU(U on top) output the production (or augment parse
tree)
Step 9: Stop


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char a[10];  // Stack
int top = -1, i;

void error() {
    printf("\nSyntax Error");
}

void push(char k[]) {  // Pushes a string onto the stack
    for (i = 0; k[i] != '\0'; i++) {
        if (top < 9)
            a[++top] = k[i];
    }
}

char TOS() {  // Returns Top of the Stack
    return (top >= 0) ? a[top] : '\0';
}

void pop() {  // Pops 1 element from the Stack
    if (top >= 0)
        a[top--] = '\0';
}

void display() {  // Displays Elements of Stack
    for (i = 0; i <= top; i++)
        printf("%c", a[i]);
}

void display1(char p[], int m) {  // Displays Present Input String
    int l;
    printf("\t");
    for (l = m; p[l] != '\0'; l++)
        printf("%c", p[l]);
}

char *stack() {  // Returns stack content
    return a;
}

void reverseString(char *str) {  // Custom function to reverse a string
    int len = strlen(str);
    int start = 0, end = len - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

int main() {
    char ip[20], r[20], st, an;
    int ir, ic, j = 0, k;

    char t[5][6][10] = {  // LL(1) Parsing Table
        {"$", "$", "TH", "$", "TH", "$"},
        {"+TH", "$", "e", "e", "$", "e"},
        {"$", "$", "FU", "$", "FU", "$"},
        {"e", "*FU", "e", "e", "$", "e"},
        {"$", "$", "(E)", "$", "i", "$"}
    };

    printf("\nEnter any string (Append with $): ");
    fgets(ip, sizeof(ip), stdin);
    ip[strcspn(ip, "\n")] = '\0';  // Remove newline character

    printf("\nStack\tInput\tOutput\n\n");
    push("$E");
    display();
    printf("\t%s\n", ip);

    for (j = 0; ip[j] != '\0';) {
        an = ip[j];  // Assign an before using it
        if (TOS() == an) {
            pop();
            display();
            display1(ip, j + 1);
            printf("\tPOP\n");
            j++;
        }
        
        st = TOS();
        if (st == 'E') ir = 0;
        else if (st == 'H') ir = 1;
        else if (st == 'T') ir = 2;
        else if (st == 'U') ir = 3;
        else if (st == 'F') ir = 4;
        else {
            error();
            break;
        }

        if (an == '+') ic = 0;
        else if (an == '*') ic = 1;
        else if (an == '(') ic = 2;
        else if (an == ')') ic = 3;
        else if ((an >= 'a' && an <= 'z') || (an >= 'A' && an <= 'Z')) {
            ic = 4;
            an = 'i';
        }
        else if (an == '$') ic = 5;
        else {
            error();
            break;
        }

        strcpy(r, t[ir][ic]);
        if (strcmp(r, "$") == 0 || strcmp(r, "e") == 0) {
            pop();
            display();
            display1(ip, j);
            printf("\t%c -> %c\n", st, 238);
        } else {
            reverseString(r);
            pop();
            push(r);
            display();
            display1(ip, j);
            printf("\t%c -> %s\n", st, t[ir][ic]);
        }

        if (TOS() == '$' && an == '$')
            break;

        if (TOS() == '$') {
            error();
            break;
        }
    }

    k = strcmp(stack(), "$");
    if (k == 0)
        printf("\nGiven string is accepted\n");
    else
        printf("\nGiven string is not accepted\n");

    return 0;
}
