#include<stdio.h>
#include<vector>
#include<string>
using namespace std;
//void Read(char a);
int ismul(char a);
void tgetchar(int t);
void Do(int type);
void output();
class Matrix
{
    int my_col, my_row;
    vector<vector<int> *> vecArray;
public:
    Matrix(int row, int col): my_row(row),my_col(col)
    {
        vecArray = vector<vector<int> *>(row, NULL);
        for(int i = 0; i < row; i++)
        {
            vecArray[i] = new vector<int>(col, 1);
        }
    }
    Matrix & operator*=(int num)
    {
        for(int i = 0; i < my_row; i++)
        {
            vector<int> & temp = *vecArray[i];
            for(int j = 0; j < my_col; j++)
            {
                temp[j] *= num;
            }
        }
        return *this;
    }
    Matrix & operator*=(Matrix & mat)
    {
        for(int i = 0; i < my_row; i++)
        {
            vector<int> & temp = *vecArray[i];
            vector<int> & temp2 = *mat.vecArray[i];
            for(int j = 0; j < my_col; j++)
            {
                temp[j] *= temp2[j];
            }
        }
        return *this;
    }
    Matrix & operator+=(int num)
    {
        for(int i = 0; i < my_row; i++)
        {
            vector<int> & temp = *vecArray[i];
            for(int j = 0; j < my_col; j++)
            {
                temp[j] += num;
            }
        }
        return *this;
    }
    Matrix & operator+=(Matrix & mat)
    {
        for(int i = 0; i < my_row; i++)
        {
            vector<int> & temp = *vecArray[i];
            vector<int> & temp2 = *mat.vecArray[i];
            for(int j = 0; j < my_col; j++)
            {
                temp[j] += temp2[j];
            }
        }
        return *this;
    }
    void concat(Matrix * pMat, bool axis = 0)
    {
        if(axis)
        {
        for(int i = 0; i < my_row; i++)
        {
            vector<int> * pVec = vecArray[i];
            vector<int> * pVec2 = pMat->vecArray[i];
            pVec->insert(pVec->end(), pVec2->begin(), pVec2->end());
        }
            my_col += pMat->my_col;
        }
        else
        {
            for(int i = 0; i < pMat->my_row; i++)
            {
                vector<int> * pVec = new vector<int>(my_col);
                *pVec = *(pMat->vecArray[i]);
                vecArray.push_back(pVec);
            }
        }
    }
    void output()
    {
        for(int i=0;i<my_row;i++)
        {
            for(int j=0;j<my_col;j++)
            {
                if(i+j !=0)
                {
                    printf(" ");
                }
                printf("%d",vecArray[i][j]);
            }
        }
    }
    ~Matrix()
    {
        for(int i = 0; i < my_row; i++)
        {
            delete vecArray[i];
        }
    }
};
class Np
{
    public:
        int flag;
        int num;
        //int row,col;
        Matrix mat;
        Np(int flag, int num, int row=0, int col=0):flag(flag), num(num), mat(row, col)
        {
           
        }
        /*~Np()
        {
            delete []mat;
        }*/
};
int isint(char a){
    if(a<=57 && a>=49){
            return 1;
    }else{
        return 0;
    }
}
enum Operator{
    Concatenate=0,
    Plus=2,
    Multiplies=3,
    axis=4,
    Right=5,
    Left=1,
    ones=9,
};
//static char now = -2;
vector <Np*> number;
vector <int> multi;
int main()
{
    
    char a;
    while(a=getchar() != '\n')
    {
        if(isint(a))
        {
            Np* mat = new Np(0,a-'0');
            number.push_back(mat);
            a=getchar();
            innum:
                if(isint(a))
                {
                    mat->num = mat->num*10 +(a - '0');
                }
                a=getchar();
            if(isint(a))
            {
                goto innum;
            }
        }
        int mul = ismul(a);
        
        switch(mul)
        {
            case ones:
            {
                char c_row,c_col;
                c_row=getchar();
                if(c_row=='(')
                {
                    c_row=getchar();
                    getchar();
                    c_col=getchar();
                    Np* mat = new Np(1,0,c_row-'0',c_col-'0');
                }
                else
                {
                   Np* mat = new Np(1,0,c_row-'0',1);
                }
                
            }break;
            case Concatenate:
                multi.push_back(Concatenate);
                break;
            case Left:
                multi.push_back(Left);
                break;
            case Multiplies:
            {    //int t; 
                int t=multi.back();
                if(t==Left)
                {
                    break;
                }
                if(t=multi.back()<Multiplies)
                {
                    Do(t);
                    multi.push_back(Multiplies);
                }
                else
                {
                    Do(mul);
                }
                
            }break;
            case Plus: 
                //int t;
            {
                int t=multi.back();
                if(t==Left)
                {
                    break;
                }
                if(t=multi.back()<Plus)
                {
                    Do(t);
                    multi.push_back(Plus);
                }
                else
                {
                    Do(mul);
                }
            }
                break;
            case axis:
                Do(axis);
                break;
            case Right:
            {
                int t=multi.back();
                while(t!=Left)
                {
                    Do(t);
                    t=multi.back();
                }
                if(t==Left)
                {
                    multi.pop_back();
                }
            }    break;
            default:
                break;
        }
        
    }

    if(!multi.empty())
    {
        Do(multi.back());
    }
    output();
}
void output()
{
    Np* ans=number.back();    
    
    if(ans->flag==0)
    {
        printf("%d",ans->num);
    }
    else
    {
        ans->mat.output();
    }
    delete ans;
}
void Mplus()
{
    Np* two=number.back();
    number.pop_back();
    Np* one=number.back();
    if(one->flag==0)
    {
        if(two->flag==0)
        {
            one->num += two->num;
        }
        else
        {
            two->mat += one->num;
        }    
    }
    else
    {
        if(two->flag==0)
        {
            one->mat += two->num;
        }
        else
        {
            one->mat += two->mat;
        }
        
    }
    delete one, two;
}
void Mmulti()
{
    Np* two=number.back();
    number.pop_back();
    Np* one=number.back();
    if(one->flag==0)
    {
        if(two->flag==0)
        {
            one->num *= two->num;
        }
        else
        {
            two->mat *= one->num;
        }    
    }
    else
    {
        if(two->flag==0)
        {
            one->mat *= two->num;
        }
        else
        {
            one->mat *= two->mat;
        }
        
    }
    delete one, two;
}
void Mcon()
{
    Np* two=number.back();
    number.pop_back();
    Np* one=number.back();
    one->mat.concat(&two->mat, 0);
    delete one, two;
}
void Do(int type)
{
    switch(type)
    {
        case Plus:
            Mplus();
            break;
        case Multiplies:
            Mmulti();
            break;
        case Concatenate:
            Mcon();
            break;
        case axis:
        {
            Np* two=number.back();
            number.pop_back();
            Np* one=number.back();
            one->mat.concat(&two->mat, 1);
            delete one, two;
            break;
        }
        default:
            break;    
    }
}
void tgetchar(int t)
{
    for(int i=0;i<t;i++){
        getchar();
    }
    return;
}

int ismul(char a)
{
    if(a=='n')
    {
        tgetchar(2);
        a=getchar();
        if(a=='c')
        {
            tgetchar(12);
            return Concatenate;
        }
        if(a=='o')
        {
            tgetchar(4);
            return ones;
        }
    }
    else if(a=='(')
    {
        return Left;
    }
    else if(a=='+')
    {
        return Plus;
    }
    else if(a=='*')
    {
        return Multiplies;
    }
    else if(a=='=')
    {
        return axis;
    }
    else if(a==')')
    {
        return Right;
    }
    else
    {
        return 7;
    }
    return 7;
}

