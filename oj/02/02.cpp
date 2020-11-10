#include<iostream>
using namespace std;
struct node{
    int L = 0;
    int R = 0;
}s[200002];
void Nfunc();
void Mfunc();
void Kfunc();
void Lfunc();
void output();
int Head=0;
int End=0;
int direc=-3;
#define over 200001
int main()
{
    //std::ios::sync_with_stdio(false);
    int n, m, k, l;
    cin>>n>>m>>k>>l;
    for(int i=0;i<(n+m+l+k);i++){
        int a;
        cin>>a;
        switch (a){
            case 1:
                Nfunc();
                //output();
                break;
            case 0:
                Mfunc();
                //output();
                break;
            case -1:
                Kfunc();
                //output();
                break;
            case -2:
                Lfunc();
                //output();
                break;
        }
    }
    output();
    cout<<-1;
    system("pause");
}
void Nfunc(){
    int i, j, dir;
    cin>>i>>j>>dir;
    if(j==-1){
        s[i].L=over;
        s[i].R=over;
        Head=i;
        End=i;
    }
    if(j!=-1){
        if(direc==-3){
            if(dir == 0){//是否要判断j！=-1
                if(s[j].L==over){
                    Head=i;
                }
                s[i].L=s[j].L;
                s[s[j].L].R=i;
                s[i].R=j;
                s[j].L=i;
            }else if(dir==1){
                if(s[j].R==over){
                    End=i;
                }
                s[i].R=s[j].R;
                s[s[i].R].L=i;
                s[i].L=j;
                s[j].R=i;
            }
        }
        if(direc==3){
            if(dir == 1){//是否要判断j！=-1
                if(s[j].L==over){
                    End=i;
                }
                s[i].L=s[j].L;
                s[s[j].L].R=i;
                s[i].R=j;
                s[j].L=i;
            }else if(dir==0){
                if(s[j].R==over){
                    Head=i;
                }
                s[i].R=s[j].R;
                s[s[i].R].L=i;
                s[i].L=j;
                s[j].R=i;
            }
        }
    }
    //cout<<s[i].L<<s[i].R<<endl;
    //cout<<s[j].L<<s[j].R<<endl;
}
void Mfunc(){
    int i;
    cin>>i;
    if(i==Head){
        if(direc==-3){
            Head=s[i].R;
        }else{
            Head=s[i].L;
        }
    }
    if(i==End){
        if(direc==-3){
            Head=s[i].L;
        }else{
            End=s[i].R;
        }
    }
    s[s[i].L].R=s[i].R;
    s[s[i].R].L=s[i].L;
    s[i].R=0;
    s[i].L=0;
}
void Kfunc(){
    int i,j;
    cin>>i>>j;
    int k;
    if(i==j){

    }
    else if(s[i].L==j){
        //k=s[i].R;
        s[s[j].L].R=i;
        s[s[i].R].L=j;
        s[i].L=s[j].L;
        s[j].R=s[i].R;
        s[i].R=j;
        s[j].L=i;
    }else if(s[i].R==j){
        s[s[j].R].L=i;
        s[s[i].L].R=j;
        s[j].L=s[i].L;
        s[i].R=s[j].R;
        s[j].R=i;
        s[i].L=j;
    }else{
    /*
    k=s[s[i].R].L;
    s[s[i].R].L=s[s[j].R].L;
    s[s[j].R].L=k;
    k=s[s[i].L].R;
    s[s[i].L].L=s[s[j].L].R;
    s[s[j].L].R=k;
    */
    if(s[i].R!=over){
        s[s[i].R].L=j;
    }
    //cout<<s[j].L<<s[j].R<<endl;
    if(s[j].R!=over){
        s[s[j].R].L=i;
    }
    //cout<<s[j].L<<s[j].R<<endl;
    if(s[i].L!=over){
        s[s[i].L].R=j;
    }
    //cout<<s[j].L<<s[j].R<<endl;
    if(s[j].L!=over){
        s[s[j].L].R=i;
    }
    k=s[i].R;
    s[i].R=s[j].R;
    s[j].R=k;

    k=s[i].L;
    s[i].L=s[j].L;
    s[j].L=k;
    }
    if(i==Head){
        Head=j;
    }else if(j==Head){
        Head=i;
    }
    if(i==End){
        End=j;
    }else if(j==End){
        End=i;
    }
    if(i==Head && j==End){
        Head=j;
        End=i;
    }
    if(i==End&&j==Head){
        Head=i;
        End=j;
    }
}
void Lfunc(){
    int k;
    k=Head;
    Head=End;
    End=k;
    direc *= -1;
}
void output(){

    int n;
    n = Head;
    do{
        cout<<n<<" ";
        if(direc==-3){
            n=s[n].R;
        }else{
            n=s[n].L;
        }
        
    }
    while(n != over);
    //cout<<endl;
}