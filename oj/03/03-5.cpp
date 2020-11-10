/*
表达式求值（递归算法）
        表达式：1、可以是一个项
                2、也可以由多个项通过加减构成
        项：1、项本身可以是一个因子
            2、项也可以由若干个因子通过乘除组成
        因子：1、因子本身可以是一个数字
              2、因子也可以由表达式加上括号组成
 */
 #include <iostream>
 #include <cstring>
 #include <cstdlib>
 #include<vector>
 #include<stdio.h>
 using namespace std;
 
 class Matrix
{
    public:
    int row=0;
    int col=0;
    int flag=0;
    int map[100][100]={0};
    
    Matrix & operator *=(Matrix & mat)
    {
        if(flag==0){
            if(mat.flag==0){
                map[0][0]*=mat.map[0][0];
            }else{
                int num = map[0][0];
                for(int i=0;i<mat.row;i++){
                    for(int j=0;j<mat.col;j++){
                        map[i][j]=num*mat.map[i][j];
                    }
                }
                row=mat.row;
                col=mat.col;
                flag=1;
            }
        }else{
            if(mat.flag==0){
                for(int i=0;i<row;i++){
                    for(int j=0;j<col;j++){
                        map[i][j]*=mat.map[0][0];
                    }
                }
            }else{
                for(int i=0;i<row;i++){
                    for(int j=0;j<col;j++){
                        map[i][j]*=mat.map[i][j];
                    }
                }
            }
        }
        return *this;
    }
    Matrix & operator +=(Matrix & mat)
    {
        //cout<<flag;
        if(flag==0){
            if(mat.flag==0){
                map[0][0]+=mat.map[0][0];
            }else{
                int num = map[0][0];
                //cout<<mat.row<<mat.col;
                for(int i=0;i<mat.row;i++){
                    for(int j=0;j<mat.col;j++){
                        map[i][j]=num+mat.map[i][j];
                    }
                }
                row=mat.row;
                col=mat.col;
                flag=1;
            }
        }else{
            if(mat.flag==0){
                for(int i=0;i<row;i++){
                    for(int j=0;j<col;j++){
                        map[i][j]+=mat.map[0][0];
                    }
                }
            }else{
                for(int i=0;i<row;i++){
                    for(int j=0;j<col;j++){
                        map[i][j]+=mat.map[i][j];
                    }
                }
            }
        }
        return *this;
    }
};
void output(Matrix & ans){
     for(int i=0;i<ans.row;i++){
        for(int j=0;j<ans.col;j++){
            if(i+j != 0){
                cout<<' ';
            }
            cout<<ans.map[i][j];
        }
    }
    //cout<<ans.flag;
 }
Matrix factor_value();//读入一个因子并且返回其值
 Matrix term_value();//读入一项的并且返回其值
 Matrix expression_value();//读入一个表达式并返回值
 Matrix Ones();
Matrix Conc();
 int main()
 {
    Matrix ans = expression_value();
    for(int i=0;i<ans.row;i++){
        for(int j=0;j<ans.col;j++){
            if(i+j != 0){
                cout<<" ";
            }
            cout<<ans.map[i][j];
        }
    }
     system("pause");
     return 0;
 }
 Matrix expression_value()//读入一个表达式并返回值
 {
     Matrix result = term_value();//求第一项的值
     bool more = true;
     while( more)
     {
         char op = cin.peek();//看一个字符不取走
         if( op == '+')
         {
             cin.get();//从输入流中取走一个字符('+'或者'-')
             Matrix value = term_value();//读入下一个项
             if(op == '+')
             //output(result);
             //output(value);
                result +=value;     
         }
         else
            more = false;
     }
     return result;
 }
 Matrix term_value()//读入一项的并且返回其值
 {
     Matrix result = factor_value();//读入一个因子
     while(true)
     {
         char op = cin.peek();//取出一个字符判断还有没有因子
         if(op== '*')
         {
             cin.get();
             Matrix value = factor_value();//读入下一个因子
             if(op == '*')
                result *=value;
         }
         else
            break;
     }
     //cout<<result.map[0][0];
     return result;
 }
 Matrix factor_value()//读入一个因子并返回值
 {
     Matrix result;
     char c = cin.peek();//取出一个字符判断输入流中是一个因子还是一个整数
     if( c =='(')
     {
         cin.get();//去掉左括号
         result = expression_value();//读入表达式
         cin.get();//去掉右括号
     }
     else if(c == 'n')
     {
         cin.ignore(3,'\n');
         c = cin.peek();
         if(c=='c'){
             result = Conc();
             //cout<<result.flag;
         }else if(c=='o'){
             result = Ones();
         }
     }
     else//是一个数字
     {
         while(isdigit(c))//求出数字的值
         {
             result.map[0][0] = 10 * result.map[0][0] +c- '0';
             result.flag=0;

             cin.get();
             c= cin.peek();
         }
         result.col=1;
         result.row=1;
     }

     //cout<<result.map[0][0];
     //output(result);
     //cout<<endl;
     return result;
 }
 Matrix Ones()
 {
     Matrix result;
     cin.ignore(5,'\n');
    char ch = cin.peek();
    if(ch=='('){
        cin.get();//get (
        ch = cin.peek();
        result.row=ch-'0';
        cin.ignore(2,'\n');
        ch = cin.peek();
        result.col=ch-'0';
        for(int i=0;i<result.row;i++){
            for(int j=0;j<result.col;j++){
                result.map[i][j]=1;
            }
        }
        cin.ignore(3,'\0');
        result.flag=1;
        //result.row=
    }
    else
    {
        result.row=ch-'0';
        //cout<<result.row;
        result.col=1;
        for(int i=0;i<result.row;i++){
            for(int j=0;j<result.col;j++){
                result.map[i][j]=1;
            }
        }
        cin.ignore(2,'\0');
        result.flag=1;
    }
    return result;
 }
 Matrix Conc()
 {
     Matrix result;
     Matrix result2;
     cin.ignore(12,'\n');
     char ch = cin.peek();
     //cout<<ch;
    if(ch=='['){
        cin.get();
    }
    result=expression_value();
    //ch=cin.peek();
    //cout<<ch;
    cin.get();//get ,
    result2=expression_value();
    cin.get();//get ]
    ch=cin.peek();
    if(ch==','){
        cin.ignore(6,'\n');
        ch=cin.peek();
        if(ch=='1')
        {
            for(int i=0;i<result2.row;i++){
                for(int j=0;j<result2.col;j++){
                    result.map[i][result.col+j]=result2.map[i][j];
                }
            }
            result.col+=result2.col;
            cin.ignore(2,'\0');
        }else{
            for(int i=0;i<result2.row;i++){
                for(int j=0;j<result2.col;j++){
                    result.map[i+result.row][j]=result2.map[i][j];
                }
            }
            result.row+=result2.row;
            cin.ignore(2,'\0');
        }
        
    }else{
        cin.get();//get )
        for(int i=0;i<result2.row;i++){
            for(int j=0;j<result2.col;j++){
                result.map[i+result.row][j]=result2.map[i][j];
            }
        }
        result.row+=result2.row;
    }
    return result;
 }

// np.concatenate([4+np.ones((3,1))*3,2*np.ones((3,1))],axis=1)*2
// 2 2 2 2 2 2Press any key to continue . . .