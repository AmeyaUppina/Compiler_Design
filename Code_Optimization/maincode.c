/*
Sample I/O:

Input: (n no. of quad instructions)
Enter no of instructions: 4
0 #2 #2 +
1 #8 #4 -
2 0 1 +
3 c 2 =

Output:
Optimized quad table:
3 c #8 =
*/
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

int calc(int n1, int n2, string op)
{
  if (op == "+")
  {
    return n1 + n2;
  }
  else if (op == "-")
  {
    return n1 - n2;
  }
  else if (op == "*")
  {
    return n1 * n2;
  }
  else if (op == "/")
  {
    return n1 / n2;
  }
  else
  {
    return -1;
  }
}

int main()
{
  vector<vector<string>> vs;
  int u;
  cout<<"Enter no of instructions: ";
  cin >> u;
  for (int i = 0; i < u + 1; i++)
  {
    string S, T;
    getline(cin, S);
    stringstream X(S);
    vector<string> v1;
    while (getline(X, T, ' '))
      v1.push_back(T);
    vs.push_back(v1);
  }
  vs.erase(vs.begin());
  vector<int> buff(u, -1);
  int i = 0;
  for (auto &v : vs)
  {
    if (isdigit(v[1][0]))
    {
      int n = stoi(v[1]);
      if (buff[n] != -1)
        v[1] = "#" + to_string(buff[n]);
    }
    if (isdigit(v[2][0]))
    {
      int n = stoi(v[2]);
      if (buff[n] != -1)
        v[2] = "#" + to_string(buff[n]);
    }
    if ((v[1].rfind("#", 0) == 0) && (v[2].rfind("#", 0) == 0))
    {
      v[1].erase(v[1].begin());
      v[2].erase(v[2].begin());
      buff[i] = calc(stoi(v[1]), stoi(v[2]), v[3]);
      cout << buff[i] << endl;
    }
    i++;
  }
  vector<vector<string>> cp;
  for (int i = 0; i < u; i++)
  {
    if (buff[i] == -1)
    {
      cp.push_back(vs[i]);
    }
  }
  for (auto v : cp)
  {
    for (auto v1 : v)
      cout << v1 << " ";
    cout << "\n";
  }
  return 0;
}
