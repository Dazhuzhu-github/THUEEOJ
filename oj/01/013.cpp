#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
int start(int num){
	string a[500];
	string b[500];
	string c[500];
    int d[500]={0};//01
    int e[500]={0};//02
    int f[500]={0};//03
    int ans1[500]={0};
    int ans2[500]={0};
    int ansc[500]={0};
    int ee=1;
	int sum1 =0,sum2 =0,sum3=0;
	int flag =1;
	for(int i=0;i<num;i++){
		cin>>a[i];
	}
	for(int i=0;i<num;i++){
		cin>>b[i];
	}
	for(int i=0;i<num;i++){
		cin>>c[i];
        d[i]=1;
        e[i]=(2+ee);
        ee *= -1;
	}

	/**************************************/
	for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            ans1[i] += d[j]*(b[i][j]-'a');
            
            ansc[i] += d[j]*(c[i][j]-'a');
        }
        ansc[i] %= 26;
        
    }
    for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            
            ans2[i] += ans1[j]*(a[i][j]-'a');
        }
        
        ans2[i] %= 26;
        
    }
    
    for(int i=0;i<num;i++){
        if(ansc[i] != ans2[i]){
            flag = 0;
        }
    }
    
    if(flag){
        return 1;
    }else{
        return 0;
    }
	
}
int main()
{
	ios::sync_with_stdio(false); 

	int a;
	int x[100];
	cin>>a;
	for(int i=0;i<a;i++){
		int b;
		cin>>b;
		x[i] =  start(b);

	}
	for(int i=0;i<a;i++){
		if(x[i]==0){
			cout<<"no"<<endl;
		}else{
			cout<<"yes"<<endl;
		}
	}
	system("pause");
 } 