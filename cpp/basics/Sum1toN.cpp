#include<iostream>
using namespace std;
int main(){
int n ;
cout<<"Please enter the number you want till you want to add: ";
cin>>n;
int sum =0;

for(int i=1; i<=n; i++){
     sum = sum + i;
    
}
cout<<sum<<endl;
}