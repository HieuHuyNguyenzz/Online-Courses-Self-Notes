#include<bits/stdc++.h>

using namespace std;

// We assume that the size of matrix are nxn.


vector<vector<int>>normal_multiplication(vector<vector<int>>x, vector<vector<int>>y){
    int n = x.size();
    vector<vector<int>>z(n ,vector<int>(n, 0));

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                z[i][j]+=x[i][k]*y[k][j];
            }
        }
    }

    return z;
}

vector<vector<int>>add_matrix(vector<vector<int>>x, vector<vector<int>>y){
    int n = x.size();
    vector<vector<int>>z(n ,vector<int>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            z[i][j]=x[i][j]+y[i][j];
        }
    }
    return z;
}

vector<vector<int>>subtract_matrix(vector<vector<int>>x, vector<vector<int>>y){
    int n = x.size();
    vector<vector<int>>z(n ,vector<int>(n, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            z[i][j]=x[i][j]-y[i][j];
        }
    }
    return z;
}

vector<vector<int>> Strassen_algorithm(vector<vector<int>> x, vector<vector<int>> y) {
    int n = x.size();
    if (n == 1) {
        return {{x[0][0] * y[0][0]}};
    }

    // Chia ma trận
    int new_size = n / 2;
    vector<vector<int>> a(new_size, vector<int>(new_size));
    vector<vector<int>> b(new_size, vector<int>(new_size));
    vector<vector<int>> c(new_size, vector<int>(new_size));
    vector<vector<int>> d(new_size, vector<int>(new_size));
    vector<vector<int>> e(new_size, vector<int>(new_size));
    vector<vector<int>> f(new_size, vector<int>(new_size));
    vector<vector<int>> g(new_size, vector<int>(new_size));
    vector<vector<int>> h(new_size, vector<int>(new_size));

    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            a[i][j] = x[i][j];
            b[i][j] = x[i][j + new_size];
            c[i][j] = x[i + new_size][j];
            d[i][j] = x[i + new_size][j + new_size];
            e[i][j] = y[i][j];
            f[i][j] = y[i][j + new_size];
            g[i][j] = y[i + new_size][j];
            h[i][j] = y[i + new_size][j + new_size];
        }
    }

    // Tính toán các P
    vector<vector<int>> p1 = Strassen_algorithm(a, subtract_matrix(f, h));
    vector<vector<int>> p2 = Strassen_algorithm(add_matrix(a, b), h);
    vector<vector<int>> p3 = Strassen_algorithm(add_matrix(c, d), e);
    vector<vector<int>> p4 = Strassen_algorithm(d, subtract_matrix(g, e));
    vector<vector<int>> p5 = Strassen_algorithm(add_matrix(a, d), add_matrix(e, h));
    vector<vector<int>> p6 = Strassen_algorithm(subtract_matrix(b, d), add_matrix(g, h));
    vector<vector<int>> p7 = Strassen_algorithm(subtract_matrix(a, c), add_matrix(e, f));

    // Kết hợp kết quả
    vector<vector<int>> z(n, vector<int>(n));
    for (int i = 0; i < new_size; i++) {
        for (int j = 0; j < new_size; j++) {
            z[i][j] = p5[i][j] + p4[i][j] - p2[i][j] + p6[i][j];
            z[i][j + new_size] = p1[i][j] + p2[i][j];
            z[i + new_size][j] = p3[i][j] + p4[i][j];
            z[i + new_size][j + new_size] = p5[i][j] + p1[i][j] - p3[i][j] - p7[i][j];
        }
    }
    return z;
}


int main(){

    int n = 4;

    vector<vector<int>>x{{1, 2, 3, 4},
                          {4 ,3, 2, 1},
                          {1, 2, 3, 4},
                          {4 ,3, 2, 1}};

    vector<vector<int>>y{{4 ,3, 2, 1},
                          {1, 2, 3, 4},
                          {4 ,3, 2, 1},
                          {1, 2, 3, 4}};

    cout<<"Normal matrix multiplication: "<<"\n";
    vector<vector<int>>z1 = normal_multiplication(x, y);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<z1[i][j]<<" ";
        }
        cout<<"\n";
    }

    cout<<"Strassen matrix multiplication: "<<"\n";
    vector<vector<int>>z2 = Strassen_algorithm(x, y);

    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout<<z2[i][j]<<" ";
        }
        cout<<"\n";
    }
}