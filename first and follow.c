#include <stdio.h>
#include <string.h>
#include <ctype.h>

char prod[10][10];
char first[10][10], follow[10][10];
int n;

int findIndex(char ch) {
    for (int i = 0; i < n; i++)
        if (prod[i][0] == ch) return i;
    return -1;
}

void addUnique(char *set, char ch) {
    if (!strchr(set, ch)) {
        int len = strlen(set);
        set[len] = ch;
        set[len + 1] = '\0';
    }
}

void computeFirst(char ch, char *result) {
    if (!isupper(ch)) {
        addUnique(result, ch);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (prod[i][0] == ch) {
            if (prod[i][3] == '0')
                addUnique(result, '0');
            else {
                computeFirst(prod[i][3], result);
            }
        }
    }
}

void computeFollow(char ch, char *result) {
    if (ch == prod[0][0]) addUnique(result, '$'); // start symbol

    for (int i = 0; i < n; i++) {
        for (int j = 3; j < strlen(prod[i]); j++) {
            if (prod[i][j] == ch) {
                if (prod[i][j + 1] != '\0') {
                    if (!isupper(prod[i][j + 1]))
                        addUnique(result, prod[i][j + 1]);
                    else {
                        char temp[10] = "";
                        computeFirst(prod[i][j + 1], temp);
                        for (int k = 0; k < strlen(temp); k++) {
                            if (temp[k] != '0')
                                addUnique(result, temp[k]);
                            else
                                computeFollow(prod[i][0], result);
                        }
                    }
                } else if (prod[i][0] != ch) {
                    computeFollow(prod[i][0], result);
                }
            }
        }
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    printf("Enter productions (e.g. A->aB or A->0 for epsilon):\n");
    for (int i = 0; i < n; i++)
        scanf("%s", prod[i]);

    for (int i = 0; i < n; i++) {
        first[i][0] = '\0';
        follow[i][0] = '\0';
    }

    for (int i = 0; i < n; i++)
        computeFirst(prod[i][0], first[i]);

    for (int i = 0; i < n; i++)
        computeFollow(prod[i][0], follow[i]);

    printf("\nFIRST Sets:\n");
    for (int i = 0; i < n; i++)
        printf("First(%c) = { %s }\n", prod[i][0], first[i]);

    printf("\nFOLLOW Sets:\n");
    for (int i = 0; i < n; i++)
        printf("Follow(%c) = { %s }\n", prod[i][0], follow[i]);

    return 0;
}


E -> TA
A -> +TA
T -> FB
B -> *FB
B -> ε
F -> (E)
F -> i

Non-Terminal | FIRST Set
E | { ( , i }
A | { + }
T | { ( , i }
B | { *, ε }
F | { ( , i }

Non-Terminal | FOLLOW Set
E | { $, ) }
A | { $, ) }
T | { +, $, ) }
B | { +, $, ) }
F | { *, +, $, ) 
