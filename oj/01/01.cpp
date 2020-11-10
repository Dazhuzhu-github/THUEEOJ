#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
int start(int num){
	string a[500];
	string b[500];
	string c[500];
	int sum1 =0,sum2 =0,sum3;
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
	for(int i=0;i<num;i++){
		for(int j=0;j<num;j++){
			//cout<< (a[i][j]-'a')<<(b[j][i]-'a');
			sum1 += (a[i][j]-'a')*(b[j][i]-'a');
			//sum3 += (c[i][j]-'a');
		}
		sum2 = (sum1%26);
		sum3 = (c[i][i]-'a');
		//cout<<sum2<<sum3<<endl;
		if(sum2 != sum3){
			count++;
		}
		sum1 = 0;
	}
	
	/*if(sum1 == sum2){
		cout<<"yes";
	}
	else{
		cout<<"no";
	}*/
	if(count>0){
		//cout<<"no";
		return 0;
	}else{
		//cout<<"yes";
		return 1;
	}
}
int main()
{
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
