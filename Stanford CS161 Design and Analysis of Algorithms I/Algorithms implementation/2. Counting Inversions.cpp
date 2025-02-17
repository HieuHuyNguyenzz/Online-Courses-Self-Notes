#include<bits/stdc++.h>

using namespace std;

int inversions;

vector<int>merge(vector<int>x, vector<int>y){
    int n = x.size()+y.size(), i = 0, j = 0;
    vector<int>res;
    for(int k=0;k<n;k++){
        if(i==x.size()){
            res.push_back(y[j]);
            j++;
        }
        else if(j==y.size()){
            res.push_back(x[i]);
            i++;
        }
        else if(x[i] <= y[j]){
            res.push_back(x[i]);
            i++;
        }
        else{
            res.push_back(y[j]);
            // Chỉ cần có thêm dòng này
            inversions += x.size()-i;
            j++;
        }
    }
    return res;
}

vector<int>merge_sort(vector<int>arr){
    if(arr.size()==1){
        return arr;
    }
    int n = arr.size();
    vector<int>left, right;
    for(int i=0;i<n/2;i++){
        left.push_back(arr[i]);
    }
    for(int i=n/2;i<n;i++){
        right.push_back(arr[i]);
    }
    vector<int>sorted_left = merge_sort(left);
    vector<int>sorted_right = merge_sort(right);
    vector<int>n_arr = merge(sorted_left, sorted_right);

    return n_arr;
}

int main(){
    vector<int>arr = {7, 8, 1, 9, 2};

    vector<int>sorted_arr = merge_sort(arr);

    cout<<"Number of Inversions: ";
    cout<<inversions<<"\n";
}