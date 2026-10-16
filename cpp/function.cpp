#include<iostream>
using namespace std;

bool isEven(int n){
    if(n%2==0){
        return true;

    }else{
        return false;
    }
}

int main(){
    bool result = isEven(7);
    cout<<result<<endl;
    return 0;
}