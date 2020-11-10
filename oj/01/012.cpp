#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
int start(int num){
	string a[500];
	string b[500];
	string c[500];
    int d[500]={0};
    int e[500]={0};
    int f[500]={0};
    int g[500]={0};
    int dd=1;
	int sum1 =0,sum2 =0,sum3=0;
	int count =0;
	for(int i=0;i<num;i++){
		cin>>a[i];
	}
	for(int i=0;i<num;i++){
		cin>>b[i];
	}
	for(int i=0;i<num;i++){
		cin>>c[i];
        //d[i] = dd;
        //dd++;
	}

	/**************************************/
	for(int i=0;i<num;i++){
        for(int j=0;j<num;j++){
            d[i] += (b[i][j]-'a');
            sum1 += (c[i][j]-'a');
        }
    }
    for(int i=0;i<num;i++){
        //sum1 += g[i];
        for(int j=0;j<num;j++){
            e[i] += (a[j][i]-'a');
        }
    }
    
    for(int i=0;i<num;i++){
        sum2 += d[i]*e[i];
    }
    sum1 %= 26;
    sum2 %= 26;
    if(sum1 ==sum2){
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