#include<iostream>
#include<vector>

using namespace std;

int main(){
vector<int> nums = {4, 7, 2, 9, 5};
int max =0;
int i = 0;

while( i<nums.size()){
    if (nums[i]> max){
        max = nums[i];
    }
    i++;
}
cout<<max<<endl;
}