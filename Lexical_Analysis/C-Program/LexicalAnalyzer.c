#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
bool isValidDelimiter(char ch) 
{
    if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
        ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
        ch == '[' || ch == ']' || ch == '{' || ch == '}')
        return (true);
    return (false);
}

bool isValidOperator(char ch)
{
    if (ch == '+' || ch == '-' || ch == '*' ||
        ch == '/' || ch == '>' || ch == '<' ||
        ch == '=')
        return (true);
    return (false);
}

bool isvalidIdentifier(char* str)
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
        str[0] == '3' || str[0] == '4' || str[0] == '5' ||
        str[0] == '6' || str[0] == '7' || str[0] == '8' ||
        str[0] == '9' || isValidDelimiter(str[0]) == true)
        return (false);
    return (true);
}

bool isValidKeyword(char* str) 
{
    if (!strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "while") || !strcmp(str, "do") ||    !strcmp(str, "break") || !strcmp(str, "continue") || !strcmp(str, "int")
        || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str,    "char") || !strcmp(str, "case") || !strcmp(str, "char")
        || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned")
        || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto") || !strcmp(str, "main"))
        return (true);
    return (false);
}

bool isValidInteger(char* str) 
{
    int i, len = (int)strlen(str);
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2'&& str[i] != '3' && str[i] != '4' && str[i] != '5'
            && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
            return (false);
    }
    return (true);
}

bool isRealNumber(char* str) 
{
    int i, len = (int)strlen(str);
    bool hasDecimal = false;
    if (len == 0)
        return (false);
    for (i = 0; i < len; i++) 
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8'
            && str[i] != '9' && str[i] != '.' || (str[i] == '-' && i > 0))
            return (false);
        if (str[i] == '.')
            hasDecimal = true;
    }
    return (hasDecimal);
}

char* subString(char* str, int left, int right) 
{
    int i;
    char* subStr = (char*)malloc( sizeof(char) * (right - left + 2));
    for (i = left; i <= right; i++)
        subStr[i - left] = str[i];
    subStr[right - left + 1] = '\0';
    return (subStr);
}

void detectTokens(char* str)
{
    int left = 0, right = 0;
    int length = (int)strlen(str);
    while (right <= length && left <= right) 
    {
        if (isValidDelimiter(str[right]) == false)
            right++;
        if (isValidDelimiter(str[right]) == true && left == right) 
        {
            if (isValidOperator(str[right]) == true)
                printf("Valid operator : '%c'\n", str[right]);
            right++;
            left = right;
        } 
        else if (isValidDelimiter(str[right]) == true && left != right || (right == length && left != right)) 
        {
            char* subStr = subString(str, left, right - 1);
            if (isValidKeyword(subStr) == true)
                printf("Valid keyword : '%s'\n", subStr);
            else if (isValidInteger(subStr) == true)
                printf("Valid Integer : '%s'\n", subStr);
            else if (isRealNumber(subStr) == true)
                printf("Real Number : '%s'\n", subStr);
            else if (isvalidIdentifier(subStr) == true
                     && isValidDelimiter(str[right - 1]) == false)
                printf("Valid Identifier : '%s'\n", subStr);
            else if (isvalidIdentifier(subStr) == false
                     && isValidDelimiter(str[right - 1]) == false)
                printf("Invalid Identifier : '%s'\n", subStr);
            left = right;
        }
    }
}

//Choose one of the codes below.
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
1) Code for array

int main()
{
    char str[100] = "float x = a + 1b; ";
    printf("The Program is : '%s'\n", str);
    printf("All Tokens are :\n");
    detectTokens(str);
    return (0);
}
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
2) Code from file

int main() 
{
    FILE    *textfile;
    char    line[MAX_LINE_LENGTH];

    textfile = fopen("~File-Path~", "r");
    if(textfile == NULL)
        return 1;
    printf("The Program is : \n");
    while(fgets(line, MAX_LINE_LENGTH, textfile)){
        printf(line);
    }
    fclose(textfile);
    printf("\n");
    printf("All Tokens are :\n");
    textfile = fopen("~File-Path~", "r");
    if(textfile == NULL)
        return 1;
    while(fgets(line, MAX_LINE_LENGTH, textfile)){
        detectTokens(line);
    }

    fclose(textfile);

    return 0;
}
*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
3) Store user input in file and read file.

int main()
{
    char inputString[128], c;
    int index = 0;

    FILE *fileptr, *textfile;
    char id [30];
    char name [47];
    char amt[50];
    char    line[MAX_LINE_LENGTH];
    fileptr = fopen("~File-Path~", "w");
    if (fileptr == NULL)
    {
        printf("File couldn't be opened\n\a\a");
        fclose(fileptr);
        return 1;
    }

    printf("Enter a multi line string( press '/' to end input)\n");
    while((c = getchar()) != '/')
    {
        inputString[index++] = c;
    }
    inputString[index] = '\0';

    fputs(inputString, fileptr);
    fclose(fileptr);
    printf("File write was successful\n");

    textfile = fopen("~File-Path~", "r");
    if(textfile == NULL)
        return 1;
    printf("The Program is : \n");
    while(fgets(line, MAX_LINE_LENGTH, textfile))
    {
        printf(line);
    }
    fclose(textfile);
    printf("\n");
    printf("All Tokens are :\n");
    textfile = fopen("~File-Path~", "r");
    if(textfile == NULL)
        return 1;
    while(fgets(line, MAX_LINE_LENGTH, textfile))
    {
        detectTokens(line);
    }

    fclose(textfile);
    return 0;
}
*/