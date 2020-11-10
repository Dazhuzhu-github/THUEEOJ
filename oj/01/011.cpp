#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
int start(int num){
	string a[500];
	string b[500];
	string c[500];
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
	}
	/**************************************/
	for(int k=0;k<num;k++){
	for(int i=0;i<num;i++){
		sum3 += (c[k][i]-'a');
		for(int j=0;j<num;j++){
			sum1 += (a[k][j]-'a')*(b[j][i]-'a');	
		}
		sum2 += (sum1%26);
		sum1 = 0;
		//cout<<sum2<<" "<<sum3<<endl;
	}
	}
	
	if(sum3 == sum2){
		return 1;
	}
	else{
		return 0;
	}
	
}
int main()
{
	ios::sync_with_stdio(false); 

	int a;
	int x[100];
	//int count=0;
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
