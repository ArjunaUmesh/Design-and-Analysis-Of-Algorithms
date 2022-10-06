#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

vector<vector<int>>
naiveMultiplication(vector<vector<int> >,vector<vector<int> >);

vector<vector<int>>
divideAndConquer(vector<vector<int> >,vector<vector<int> >);


vector<vector<int> >
strassensMultiplication(vector<vector<int> > A,vector<vector<int> > B);



vector<vector<int> > naiveMutiplication(vector<vector<int> > A,vector<vector<int> > B)
{
    int row_A=A.size();
    int row_B=B.size();
    int col_A=A[0].size();
    int col_B=B[0].size();

    vector<vector<int> > C(row_A,vector<int>(col_B));
    if(col_A!=row_B)
    {
        cout<<"Can't multiply\n";

    }else{

        for(int i=0;i<row_A;i++)
        {
            for(int j=0;j<col_A;j++)
            {
                C[i][j]=0;
                for(int k=0;k<col_A;k++)
                {
                    C[i][j]+=A[i][k]*B[k][j];
                }
            }
        }
    }
    return C;
}


vector<int> operator +(vector<int> A,vector<int> B)
{
    int n=A.size();
    vector<int> sum(n);

    for(int i=0;i<n;i++)
    {
        sum[i]=(A[i]+B[i]);
    }
    return sum;
}

vector<int> operator -(vector<int> A,vector<int> B)
{
    int n=A.size();
    vector<int> sum(n);

    for(int i=0;i<n;i++)
    {
        sum[i]=(A[i]-B[i]);
    }
    return sum;
}


vector<vector<int>> operator +(vector<vector<int>> A,vector<vector<int>> B)
{
    int n=A.size();
    vector<vector<int>> sum(n,vector<int>(n));

    for(int i=0;i<n;i++)
    {
        sum[i]=(A[i]+B[i]);
    }
    return sum;
}
vector<vector<int>> operator -(vector<vector<int>> A,vector<vector<int>> B)
{
    int n=A.size();
    vector<vector<int>> sum(n,vector<int>(n));

    for(int i=0;i<n;i++)
    {
        sum[i]=(A[i]-B[i]);
    }
    return sum;
}

ostream& operator<<(ostream& os, const vector<vector<int>>& v)
{
    for (auto i:v) {
        for(auto j:i)
            os <<j<<"\t";
        cout<<"\n";
    }
    return os;
}

int checkMatrix(vector<vector<int> > &A)
{
    int row_A=A.size();
    int col_A=A[0].size();

    int n=log2(row_A);
    //cout<<A;
    if(pow(2,n)!=row_A || row_A!=col_A)
    {
        if((pow(2,n+1)<col_A))
        {
               n++;
        }
        n=pow(2,n+1);
        int r=n-row_A;

        for(int i=0;i<r;i++)
        {
            vector<int> a(A[0].size());
            fill(a.begin(), a.end(), 0);
            A.push_back(a);
        }
        r=A.size()-A[0].size();
        if(r>0)
        {
            for(int i=0;i<A.size();i++)
            {
                for(int j=0;j<r;j++)
                {
                    A[i].push_back(0);
                }
            }

        }
    }

}


vector<vector<int> > divideAndConquer(vector<vector<int> > A,vector<vector<int> > B)
{

    int row_A=A.size();
    int row_B=B.size();
    int col_A=A[0].size();
    int col_B=B[0].size();


    vector<vector<int>> product(row_A,vector<int>(col_B));

    if(col_A!=row_B)
    {
        cout<<"Cannot multiply\n";
        return product;
    }

    checkMatrix(A);
    checkMatrix(B);
    if(col_A==1)
    {
        product[0][0]=A[0][0]*B[0][0];
        return product;
    }
    else
    {
        int n2=col_A/2;
        int n=col_A;
        vector<vector<int>> product_a(n2,vector<int>(n2));
        vector<vector<int>> product_b(n2,vector<int>(n2));
        vector<vector<int>> product_c(n2,vector<int>(n2));
        vector<vector<int>> product_d(n2,vector<int>(n2));

        vector<vector<int>> a1(n2,vector<int>(n2));
        vector<vector<int>> b1(n2,vector<int>(n2));
        vector<vector<int>> c1(n2,vector<int>(n2));
        vector<vector<int>> d1(n2,vector<int>(n2));


        vector<vector<int>> a2(n2,vector<int>(n2));
        vector<vector<int>> b2(n2,vector<int>(n2));
        vector<vector<int>> c2(n2,vector<int>(n2));
        vector<vector<int>> d2(n2,vector<int>(n2));

        for(int i=0;i<n2;i++)
        {
            for(int j=0;j<n2;j++)
            {
                a1[i][j]=A[i][j];
                b1[i][j]=A[i][n2+j];
                c1[i][j]=A[i+n2][j];
                d1[i][j]=A[i+n2][j+n2];
                a2[i][j]=B[i][j];
                b2[i][j]=B[i][n2+j];
                c2[i][j]=B[i+n2][j];
                d2[i][j]=B[i+n2][j+n2];
            }

        }

        product_a=divideAndConquer(a1,a2)+divideAndConquer(b1,c2);
        product_b=divideAndConquer(a1,b2)+divideAndConquer(b1,d2);
        product_c=divideAndConquer(c1,a2)+divideAndConquer(d1,c2);
        product_d=divideAndConquer(c1,b2)+divideAndConquer(d1,d2);

        n=product_a.size();
        //n=n*2;
        vector<vector<int>> product(2*n,vector<int>(2*n));

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                product[i][j]=product_a[i][j];
                product[i][j+n]=product_b[i][j];
                product[i+n][j]=product_c[i][j];
                product[i+n][j+n]=product_d[i][j];

            }
        }

        //cout<<product<<"\n\n";
        return product;
    }

}


vector<vector<int> > strassensMultiplication(vector<vector<int> > A,vector<vector<int> > B)
{

    int row_A=A.size();
    int row_B=B.size();
    int col_A=A[0].size();
    int col_B=B[0].size();


    vector<vector<int>> product(row_A,vector<int>(col_B));

    if(col_A!=row_B)
    {
        cout<<"Cannot multiply\n";
        return product;
    }

    checkMatrix(A);
    checkMatrix(B);
    if(col_A==1)
    {
        product[0][0]=A[0][0]*B[0][0];
        return product;
    }
    else
    {
        int n2=col_A/2;
        int n=col_A;
        vector<vector<int>> product_a(n2,vector<int>(n2));
        vector<vector<int>> product_b(n2,vector<int>(n2));
        vector<vector<int>> product_c(n2,vector<int>(n2));
        vector<vector<int>> product_d(n2,vector<int>(n2));

        vector<vector<int>> t1(n2,vector<int>(n2));
        vector<vector<int>> t2(n2,vector<int>(n2));
        vector<vector<int>> t3(n2,vector<int>(n2));
        vector<vector<int>> t4(n2,vector<int>(n2));
        vector<vector<int>> t5(n2,vector<int>(n2));
        vector<vector<int>> t6(n2,vector<int>(n2));
        vector<vector<int>> t7(n2,vector<int>(n2));

        vector<vector<int>> a1(n2,vector<int>(n2));
        vector<vector<int>> b1(n2,vector<int>(n2));
        vector<vector<int>> c1(n2,vector<int>(n2));
        vector<vector<int>> d1(n2,vector<int>(n2));


        vector<vector<int>> a2(n2,vector<int>(n2));
        vector<vector<int>> b2(n2,vector<int>(n2));
        vector<vector<int>> c2(n2,vector<int>(n2));
        vector<vector<int>> d2(n2,vector<int>(n2));

        for(int i=0;i<n2;i++)
        {
            for(int j=0;j<n2;j++)
            {
                a1[i][j]=A[i][j];
                b1[i][j]=A[i][n2+j];
                c1[i][j]=A[i+n2][j];
                d1[i][j]=A[i+n2][j+n2];
                a2[i][j]=B[i][j];
                b2[i][j]=B[i][n2+j];
                c2[i][j]=B[i+n2][j];
                d2[i][j]=B[i+n2][j+n2];
            }

        }

        t1=strassensMultiplication(b2-d2,a1);
        t2=strassensMultiplication(a1+b1,d2);
        t3=strassensMultiplication(c1+d1,a2);
        t4=strassensMultiplication(c2-a2,d1);
        t5=strassensMultiplication(a1+d1,a2+d2);
        t6=strassensMultiplication(b1-d1,c2+d2);
        t7=strassensMultiplication(a1-c1,a2+b2);

        product_a=t5+t4-t2+t6;
        product_b=t1 + t2;
        product_c=t3+t4;
        product_d=t1 + t5 - t3 - t7;

        n=product_a.size();
        //n=n*2;
        vector<vector<int>> product(2*n,vector<int>(2*n));

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                product[i][j]=product_a[i][j];
                product[i][j+n]=product_b[i][j];
                product[i+n][j]=product_c[i][j];
                product[i+n][j+n]=product_d[i][j];

            }
        }

        //cout<<product<<"\n\n";
        return product;
    }

}


int main()
{

    vector<vector<int> > A1={ { 1, 1},
                             { 2, 2} };

    vector<vector<int> > B1={ { 1, 1,},
                             { 2, 2,} };

    vector<vector<int> > A2={{ 1, 1, 1, 1, },
                            { 2, 2, 2, 2, },
                            { 3, 3, 3, 3, },
                            { 2, 2, 2, 2, }};

    vector<vector<int> > B2={ { 1, 1, 1, 1, },
                             { 2, 2, 2, 2, },
                             { 3, 3, 3, 3, },
                             { 2, 2, 2, 2, }};

    vector<vector<int> > A={{ 1, 1, 1, 1, },
                            { 2, 2, 2, 2, },
                            { 3, 3, 3, 3, }};

    vector<vector<int> > B={ { 1, 1, },
                             { 2, 2, },
                             { 3, 3, },
                             { 2, 2, }};
/*
    vector<vector<int> > C=naiveMutiplication(A,B);
    for(int i=0;i<C.size();i++)
    {
        for(int j=0;j<C[0].size();j++)
        {
            cout<<C[i][j]<<"\t";
        }
        cout<<"\n";
    }
*/
    cout<<"Naive Multiplication : \n";
    vector<vector<int> > a=naiveMutiplication(A,B);
    cout<<a;
    cout<<"\nDivide and conquer (1) : \n";

    vector<vector<int>> b=divideAndConquer(A,B);
    cout<<b;
    cout<<"\nStrassen's Multiplication : \n";
    vector<vector<int>> c=strassensMultiplication(A,B);
    cout<<c;
}
