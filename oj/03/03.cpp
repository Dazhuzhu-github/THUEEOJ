#include<iostream>
#include<vector>
#include<string>
using namespace std;
int isint(char a){
    if(a<=57 && a>=49){
            return 1;
    }else{
        return 0;
    }
}
enum Operator{
    Plus=0,
    Left=1,
    Multiplies=2,
    Right=3,
    Contcatenate=4,
    Ones=5,
    axis=6,
};
void ones();
void concatenate();
void multiply();
void add();
class np{
    int ans=0;
    int flag=0;
    vector<vector<int>> an;
};
int main()
{
    string a;
    cin>>a;
    int count=0;
    vector <int> number;
    vector <int> multi;
    vector <vector<int>> all;
    while(a[count]=='\0'){
        if(isint(a[count])){//数字入栈
            number.push_back((a[count]-'0'));
            count++;
            while(isint(a[count])){
                number.push_back((a[count]-'0')*10+(a[count+1]-'0'));
                count += 2;
            }
        }
        if(a[count]=='+'){
            multi.push_back(Plus);
            count++;
        }else if(a[count]=='*'){
            multi.push_back(Multiplies);
            count++;
        }else if(a[count]=='('){
            multi.push_back(Left);
            count++;
        }else if(a[count]==')'){
            multi.push_back(Right);
            count++;
        }else if(a[count]=='n'){
            count += 3;
            if(a[count]=='c'){
                multi.push_back(Contcatenate);
                if(a[count] != '('){
                    count++;
                }
            }
            else if(a[count]=='o'){
                
            }
        }
    }
    return 0;
}