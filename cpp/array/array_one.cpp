#include<iostream>
#include<vector>
using namespace std;

int main(){



vector<int> nums = {4, 7, 2, 9, 5};
int sum =0;
    for( int i =0; i<nums.size(); i++){
         sum += nums[i]; 
    }
    cout<<sum<<endl; 
}