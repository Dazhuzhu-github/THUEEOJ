#include<iostream>
#include<vector>
#include<string>
using namespace std;
class np{
    int number=0;
    int flag=0;
    vector<vector<int>> vec;
};
int isint(char a){
    if(a<=57 && a>=49){
            return 1;
    }else{
        return 0;
    }
}
np add(){

}
np multi(){

}
np all(char a, np ans, int& count){
    if(a==')'){

    }
    if(a=='n'){

    }
    if(a=='n'){

    }
}
int main()
{
    int count = 0;
    string a;
    cin>>a;
    np ans;
    while(a[count] != '\0'){
        ans = all(a[count], ans, count);
        count++;
    }
}