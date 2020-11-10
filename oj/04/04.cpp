#include<stdio.h>
#include<algorithm>
using namespace std;
int quickRead()
{
    static char s[16];
    fgets(s, 16, stdin);
    int result = 0;
    char* p = s;
    while ('0' <= *p && *p <= '9')
    {
        result *= 10;
        result += *p - '0';
        p++;
    }
    return result;
}
struct tree_node
{
    int* Left;
    int* Right;
};
class KDTree
{
public:
    //建树
    KDTree();
    // return root
    tree_node* Getroot();
    //findnearest
    tree_node* FindN();
    //findfar
    tree_node* FindF();
private:
    tree_node* root;
};
int Village()
{
    int ans;
    return ans;
}
int main(){
    int ans;
    int T;
    scanf("%d",T);
    for(int i=0;i<T;i++)
    {
        ans=Village();
        printf("%d",ans);
    }
    return 0;
}