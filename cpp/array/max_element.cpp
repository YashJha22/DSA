#include<iostream>
#include<vector>

using namespace std;

int main(){
vector<int> nums = {4, 7, 2, 9, 5};
int max =0;

for (int i=0; i<nums.size(); i++){
    if (nums[i]> max){
        max = nums[i];
    }
}
cout<<max<<endl;
}