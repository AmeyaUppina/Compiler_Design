#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_EXPR_SIZE 100

struct node
{
    int info;
    struct node *ptr;
} *top, *temp;

void push(char data)
{
    if (top == NULL)
    {
        top = (struct node *)malloc(1 * sizeof(struct node));
        top->ptr = NULL;
        top->info = (int)data;
    }
    else
    {
        temp = (struct node *)malloc(1 * sizeof(struct node));
        temp->ptr = top;
        temp->info = (int)data;
        top = temp;
    }
}

char pop()
{
    temp = top;
    if (temp == NULL)
        return -1;
    else
        temp = temp->ptr;
    int popped = top->info;
    free(top);
    top = temp;
    return (char)popped;
}

char peek()
{
    return (char)top->info;
}

int isEmpty()
{
    if (top == NULL)
        return 1;
    return 0;
}

int precedence(char operator)
{
    switch (operator)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

char *infixToPostfix(char *infix)
{
    int i, j;
    int len = (int)strlen(infix);
    char *postfix = (char *)malloc(sizeof(char) * (len + 2));
    for (i = 0, j = 0; i < len; i++)
    {
        if (infix[i] == ' ' || infix[i] == '\t')
            continue;
        if (isalnum(infix[i]))
        {
            postfix[j++] = infix[i];
        }
        else if (infix[i] == '(')
        {
            push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty() && peek() != '(')
                postfix[j++] = pop();
            if (!isEmpty() && peek() != '(')
                return "Invalid Expression";
            else
                pop();
        }
        else if (isOperator(infix[i]))
        {
            while (!isEmpty() && precedence(peek()) >= precedence(infix[i]))
                postfix[j++] = pop();
            push(infix[i]);
        }
    }
    while (!isEmpty())
    {
        if (peek() == '(')
        {
            return "Invalid Expression";
        }
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
    return postfix;
}

void printInstruction(char oper)
{
    if (oper == '+')
    {
        printf("ADD ");
    }
    else if (oper == '-')
    {
        printf("SUB ");
    }
    else if (oper == '*')
    {
        printf("MUL ");
    }
    else if (oper == '/')
    {
        printf("DIV ");
    }
    else if (oper == '^')
    {
        printf("EXP ");
    }
}

int isAlpha(char c)
{
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

void printVal(char c)
{
    if (isAlpha(c))
    {
        printf("%c ", c);
    }
    else
    {
        printf("t%d ", c + 1);
    }
}

int main()
{
    char infix[MAX_EXPR_SIZE];
    printf("Enter an infix expression: ");
    fgets(infix, MAX_EXPR_SIZE, stdin);
    char *postfix = infixToPostfix(infix);
    printf("Postfix expression : %s\n", postfix);
    int n = (int)strlen(postfix);
    int count = 0;
    char t1, t2;
    char quad[50][4];
    top = NULL;
    for (int i = 0; i < n; i++)
    {
        if (isalnum(postfix[i]))
        {
            push(postfix[i]);
        }
        else
        {
            t1 = pop();
            t2 = pop();
            quad[count][0] = (char)(count);
            quad[count][1] = postfix[i];
            quad[count][2] = t2;
            quad[count][3] = t1;
            push((char)count);
            count++;
        }
    }
    printf("Quadruple table :\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d) ", i);
        printf("%c ", quad[i][1]);
        printVal(quad[i][2]);
        printVal(quad[i][3]);
        printf("t%d\n", i + 1);
    }
    top = NULL;
    int reg_count = 0;
    for (int i = 0; i < count; i++)
    {
        if (isAlpha(quad[i][2]))
        {
            printf("MOV R%d, %c\n", reg_count, quad[i][2]);
            push((char)reg_count);
            reg_count++;
        }
        if (isAlpha(quad[i][3]))
        {
            printf("MOV R%d, %c\n", reg_count, quad[i][3]);
            push((char)reg_count);
            reg_count++;
        }
        printInstruction(quad[i][1]);
        t1 = pop();
        t2 = pop();
        printf("R%d, R%d, R%d\n", reg_count, t2, t1);
        push((char)reg_count);
        reg_count++;
    }
    return 0;
}
