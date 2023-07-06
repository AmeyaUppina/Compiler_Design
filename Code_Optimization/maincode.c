#include <stdio.h>
#include <string.h>
int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '/' || c == '*' || c == '=' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}')
    {
        return 1;
    }
    return 0;
}

int isKeyword(char *buffer, int buff_count)
{
    if (!strcmp(buffer, ""))
    {
        return 0;
    }
    const char *keywords[] = {"print", "int", "void", "main"};
    for (int i = 0; i < 2; i++)
    {
        if (!strncmp(buffer, keywords[i], buff_count))
        {
            return 1;
        }
    }
    return 0;
}

int isConstant(char *buffer, int count)
{
    if (!strcmp(buffer, ""))
    {
        return 0;
    }
    int c = 1;
    for (int i = 0; i < count; i++)
    {
        if (!(buffer[i] >= 48 && buffer[i] <= 57))
        {
            c = 0;
        }
    }
    return c;
}

int main()
{
    char keywordList[20][255];
    int keyword_count = 0;
    char identList[20][255];
    int ident_count = 0;
    char constList[20][255];
    char const_count = 0;
    char symbols[20];
    char symb_count = 0;
    FILE *ptr = fopen("D:/Ameya/OneDrive/ProgramProjects/Compiler_Design/Code_Optimization/test.txt", "r");
    if (ptr == NULL)
    {
        printf("File Not Found");
    }
    char c = 0;
    char buffer[255];
    int buff_count;
    int temp;
    while (fscanf(ptr, "%c", &c) == 1)
    {
        buff_count = 0;
        strcpy(buffer, "");
        while (c != ' ' && c != '\n')
        {
            if (c == ';')
            {
                break;
            }
            buffer[buff_count++] = c;
            fscanf(ptr, "%c", &c);
        }
        temp = 0;
        while (temp < buff_count)
        {
            if (isOperator(buffer[temp]))
            {
                symbols[symb_count++] = buffer[temp];
                buffer[temp] = 0;
            }
            temp++;
        }
        if (isKeyword(buffer, buff_count))
        {
            strcpy(keywordList[keyword_count++], buffer);
        }
        else if (isConstant(buffer, buff_count))
        {
            strncpy(constList[const_count++], buffer, buff_count);
        }
        else if (strcmp(buffer, "") && strcmp(buffer, " "))
        {
            strncpy(identList[ident_count++], buffer, buff_count);
        }
    }
    printf("\nKeyword list:\n");
    for (int i = 0; i < keyword_count; i++)
    {
        printf("%s\n", keywordList[i]);
    }
    printf("\nIdentifier list:\n");
    for (int i = 0; i < ident_count; i++)
    {
        printf("%s\n", identList[i]);
    }
    printf("\nConstant list:\n");
    for (int i = 0; i < const_count; i++)
    {
        printf("%s\n", constList[i]);
    }
    ("\nSymbol list:\n");
    for (int i = 0; i < symb_count; i++)
    {
        printf("%c\n", symbols[i]);
    }
    fclose(ptr);
}