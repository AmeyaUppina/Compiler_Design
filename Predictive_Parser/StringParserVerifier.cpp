#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

// Custom data structure for storing parse table entries
struct ParseTableEntry 
{
    char nonTerminal;
    string production;
};

// Function to check if the given string is accepted or rejected by the grammar
bool isAccepted(const unordered_map<char, int>& nonTermToIndex, const unordered_map<char, int>& termToIndex,
                const vector<vector<ParseTableEntry>>& parseTable, const string& inputString) 
{
    vector<char> stack;
    stack.push_back('$');
    stack.push_back(parseTable[0][0].nonTerminal); // Start symbol (usually 'S')

    size_t ip = 0;
    cout << "Parsing Steps:\n";
    while (!stack.empty()) 
    {
        char topSymbol = stack.back();
        char inputSymbol = (ip < inputString.length()) ? inputString[ip] : '$';

        cout << "Stack: ";
        for (char symbol : stack) 
        {
            cout << symbol;
        }
        cout << "\tInput String: " << inputString.substr(ip) << "$\tAction: ";

        if (topSymbol == inputSymbol) 
        {
            stack.pop_back();
            ip++;
            cout << "Match " << inputSymbol << endl;
        } 
        else if (nonTermToIndex.count(topSymbol) && termToIndex.count(inputSymbol)) 
        {
            int ntIndex = nonTermToIndex.at(topSymbol);
            int tIndex = termToIndex.at(inputSymbol);

            if (parseTable[ntIndex][tIndex].production == "") 
            {
                cout << "ERROR: No production found for non-terminal '" << topSymbol << "' and input symbol '" << inputSymbol << "'.\n";
                return false;
            }

            stack.pop_back();
            const string& production = parseTable[ntIndex][tIndex].production;
            for (int i = production.length() - 1; i >= 3; --i) 
            {
                if (production[i] != '@') 
                {
                    stack.push_back(production[i]);
                }
            }
            cout << "Apply Production: " << production << endl;
        } 
        else 
        {
            cout << "ERROR: Invalid input symbol '" << inputSymbol << "'.\n";
            return false;
        }
    }

    return true;
}

int main() 
{
    unordered_map<char, int> nonTermToIndex = {{'S', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}}; // Map non-terminals to row indices
    unordered_map<char, int> termToIndex = {{'a', 0}, {'b', 1}, {'c', 2}, {'g', 3}, {'f', 4}, {'h', 5}, {'$', 6}}; // Map terminals to column indices

    // Parse table for the LL(1) grammar
    vector<vector<ParseTableEntry>> parseTable = {
        {{'S', "S->aBDh"}, {'S', ""}, {'S', ""}, {'S', ""}, {'S', ""}, {'S', ""}, {'S', ""}},
        {{'B', ""}, {'B', ""}, {'B', "B->cC"}, {'B', ""}, {'B', ""}, {'B', ""}, {'B', ""}},
        {{'C', ""}, {'C', "C->bC"}, {'C', ""}, {'C', "@"}, {'C', "@"}, {'C', "@"}, {'C', "@"}},
        {{'D', ""}, {'D', ""}, {'D', ""}, {'D', "D->EF"}, {'D', "D->EF"}, {'D', "D->EF"}, {'D', ""}},
        {{'E', ""}, {'E', ""}, {'E', ""}, {'E', "E->g"}, {'E', "@"}, {'E', "@"}, {'E', ""}},
        {{'F', ""}, {'F', ""}, {'F', ""}, {'F', ""}, {'F', "F->f"}, {'F', "@"}, {'F', "@"}}
    };

    string inputString;
    cout << "Enter the input string: ";
    cin >> inputString;

    bool isAcceptedInput = isAccepted(nonTermToIndex, termToIndex, parseTable, inputString);
    if (isAcceptedInput) 
    {
        cout << "The input string is accepted by the grammar.\n";
    } 
    else 
    {
        cout << "The input string is rejected by the grammar.\n";
    }

    return 0;
}
