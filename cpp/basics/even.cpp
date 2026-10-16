#include<iostream>
using namespace std;

int main(){
    int n =10;
    int count =0;
    for(int i=0; i<=n; i++){
        if(i%2 == 0){
            count++;
        }
        
    }
cout<<"The number of even numbers from 0 to "<<n<<" is: "<<count<<endl;
}