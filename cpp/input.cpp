#include<iostream>
using namespace std;

int main(){
    int a; 
    cout<<"Enter the first number: ";
    cin>> a;
    int b;
    cout<<"Enter the second number: ";
    cin>> b;
    int add = a + b;
    cout<<"The sum of "<<a<<" and "<<b<<" is: "<<add<<endl;

    int sub = a - b;
    cout<<"The difference of "<<a<<" and "<<b<<" is: "<<sub<<endl;
    int prod = a * b;
    cout<<"The product of "<<a<<" and "<<b<<" is: "<<prod<<endl;

}