#include<bits/stdc++.h>

using namespace std;

// This code only works on x y with the same size
// This codes are from the description on Stanford CS161

int n = 4, x = 1234, y = 5678;

vector<int>to_element(int x){
    vector<int>num;
    while(x){
        num.push_back(x%10);
        x/=10;
    }
    reverse(num.begin(), num.end());
    return num;
}

int multiplication(int a, vector<int>b){
    int ans=0, res=0, base=1;
    reverse(b.begin(), b.end());
    for(int i:b){
        int mul =  i * a + res;
        res = mul/10;
        ans+=base*(mul%10);
        base*=10;
    }
    if(res!=0){
        ans+=base*res;
    }
    return ans;
}

vector<int>add(vector<int>x, vector<int>y){
    vector<int>res;
    for(int i=0;i<x.size();i++){
        res.push_back(x[i]+y[i]);
    }
    return res;
}

int third_grade_algorithm(vector<int>x, vector<int>y){
    vector<int>mul_res;
    int base=1, ans=0;
    for(int i=n-1;i>=0;i--){
        mul_res.push_back(multiplication(x[i], y)*base);
        base*=10;
    }
    for(int i:mul_res){
        ans+=i;
    }
    return ans;
}

int karatsuba_algorithm(vector<int>x, vector<int>y){
    if(x.size()==1&&y.size()==1){
        return x[0]*y[0];
    }
    else{
        int n = x.size();
        vector<int>a,b,c,d;
        for(int i=0;i<n/2;i++){
            a.push_back(x[i]);
            c.push_back(y[i]);
        }
        for(int i=n/2;i<n;i++){
            b.push_back(x[i]);
            d.push_back(y[i]);
        }
        int ac = karatsuba_algorithm(a, c);
        int bd = karatsuba_algorithm(b, d);
        int adbc = karatsuba_algorithm(add(a, b), add(c, d)) - ac - bd;
        return pow(10, n)* ac + pow(10, n/2)*adbc + bd;
    }
}

int main(){

    cout<<"The answer is: "<<x*y<<"\n";

    vector<int>nx = to_element(x), ny = to_element(y);
    
    cout<<"Third grade algorithm: "<<third_grade_algorithm(nx, ny)<<"\n";

    cout<<"Karatsuba algorithm: "<<karatsuba_algorithm(nx, ny)<<"\n";
    
}