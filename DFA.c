#include <stdio.h>
#include <string.h>

int Index(char* arr, char c, int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == c) {
            return i;
        }
    }
    return -1;
}

int main() {
    int states, inputs;
    printf("Enter the number of states: ");
    scanf("%d", &states);
    printf("Enter the number of inputs: ");
    scanf("%d", &inputs);

    char symbols[inputs];
    printf("Enter the input symbols: ");
    for (int i = 0; i < inputs; i++) {
        scanf(" %c", &symbols[i]);
    }

    int transitions[states][inputs];
    printf("Enter the transition table:\n");
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < inputs; j++) {
            printf("(q%d,%c)=q",i,symbols[j]);
            scanf("%d", &transitions[i][j]);
        }
    }
    printf("Enter the accepting state: q");
    int end;
    scanf("%d",&end);
    char string[100];
    printf("Enter the string: ");
    scanf(" %[^\n]%*c", string);
    printf("D\t");
    for (int i = 0; i < inputs; i++) {
        printf("%c\t",symbols[i]);
    }
    printf("\n");
    for (int i = 0; i < states; i++) {
        printf("q%d\t",i);
        for (int j = 0; j < inputs; j++) {
            printf("q%d\t",transitions[i][j]);
        }
        printf("\n");
    }
    int state = 0;
    for (int i = 0; i < strlen(string); i++) {
        int character = Index(symbols, string[i], inputs);
        if (character == -1) {
            printf("Invalid input symbol: %c\n", string[i]);
            return 0;
        }
        printf("(q%d,%c)-> ",state,string[i]);
        state = transitions[state][character];
    }

    if (state == end) {
        printf("(q%d) ",state);
        printf("\nString Accepted\n");
    } else {
        printf("\nString Rejected\n");
    }

    return 0;
}