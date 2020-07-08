#include<fstream>
#include<cmath>
#include<cstring>
#include <vector>
using namespace std;

ifstream finp("final2.inp");
ofstream fout("final2.out");

vector<int> arr;
vector<bool> jollo;

bool isSecondJollo(int n) {
    for (int i = 0; i < n; i++) {
        jollo[arr[i]] = true;
    }
    for (int i = 1; i <= n; i++) {
        if (!jollo[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    
    int testcase;
    finp >> testcase;
    while (testcase--) {
        int n;
        finp >> n;
        arr.resize(n + 1);
        jollo.resize(n + 1, false);
        for (int i = 0; i < n; i++) {
            finp >> arr[i];
        }
        for (int i = 0; i < n - 1; i++) {
            arr[i] = abs(arr[i] - arr[i + 1]);
        }
        for (int i = 0; i < n - 2; i++) {
            arr[i] = abs(arr[i] - arr[i + 1]);
        }

        if (isSecondJollo(n -2)) {
            fout << "Yes" << '\n';
        }
        else {
            fout << "No" << '\n';
        }
        
        arr.clear();
        jollo.clear();

    }
    return 0;
}

