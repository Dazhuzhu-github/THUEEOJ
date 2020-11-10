#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;
int main()
{
    string a[3];
    a[0]="abc";

    a[0][0]='b';
    int c = a[0][0]-'a';
    cout<<c;
    system("pause");
}