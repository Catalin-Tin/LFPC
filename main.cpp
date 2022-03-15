#include<bits/stdc++.h>
using namespace std;

void multiply(int F[2][2], int M[2][2]);

void power(int F[2][2], int n);

int fib(int n)
{
    int F[2][2] = { { 1, 1 }, { 1, 0 } };

    if (n == 0)
        return 0;

    power(F, n - 1);

    return F[0][0];
}

void multiply(int F[2][2], int M[2][2])
{
    int x = F[0][0] * M[0][0] +
            F[0][1] * M[1][0];
    int y = F[0][0] * M[0][1] +
            F[0][1] * M[1][1];
    int z = F[1][0] * M[0][0] +
            F[1][1] * M[1][0];
    int w = F[1][0] * M[0][1] +
            F[1][1] * M[1][1];

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(int F[2][2], int n)
{
    int i;
    int M[2][2] = { { 1, 1 }, { 1, 0 } };

    // n - 1 times multiply the
    // matrix to {{1,0},{0,1}}
    for(i = 2; i <= n; i++)
        multiply(F, M);
}

// Driver code
int main()
{   time_t start, end;
    long n;
    cin >> n;
    start = clock();
    cout << " " <<  fib(n)<<endl;
     end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    return 0;
}
