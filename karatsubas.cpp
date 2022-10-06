#include<iostream>
using namespace std;

#include <bits/stdc++.h>
#include <cmath>
int karatsuba(int,int);
int power(int,int);
int main()
{
    int num1=12;
    int num2=87;

    int product=karatsuba(num1,num2);
    cout<<product;

    string c="letter";
    cout<<"\n"<<c.length();
}

int karatsuba(int num1,int num2)
{
    if(num1<10 || num2<10)
    {
        return num1*num2;
    }
    int len1=log10(num1)+1;
    int len2=log10(num2)+1;
    int n=(len1>len2)?len1:len2;
    n=n/2;

    int a,b,c,d;
    int m=power(10,n);
    c=num1%m;
    d=num2%m;
    a=num1/m;
    b=num2/m;

    cout<<"\na:"<<a<<" b:"<<b<<" c:"<<c<<" d:"<<d<<"\n";
    int x,y,z;
    x=karatsuba(a,b);
    y=karatsuba(c,d);
    z=karatsuba((a+c),(b+d));

    int k=power(10,2*n);
    int result=x*k+(z-x-y)*m+y;
    cout<<result<<"\n";
    return result;
}

int power(int a,int b)
{
    int result=1;
    while(b>0)
    {
        result*=a;
        b--;
    }
    return result;
}
