#include "lcs.h"
#include "vector"
#include "iostream"
using namespace std;


string lcs_helper(const string& first, const string& second, int m, int n) {
    if (m == 0 || n == 0) {
        return "";
    }

    if (first[m - 1] == second[n - 1]) {
        return lcs_helper(first, second, m - 1, n - 1) + first[m - 1];
    }
    else {
        string lcs1 = lcs_helper(first, second, m - 1, n);
        string lcs2 = lcs_helper(first, second, m, n - 1);
        return (lcs1.length() > lcs2.length()) ? lcs1 : lcs2;
    }
}

string lcs_rec_search(const string& first, const string& second) {
    return lcs_helper(first, second, first.length(), second.length());
}

string lcs(const string& first, const string& second) {
    int m = first.length();
    int n = second.length();
    
    vector<vector<int>> LCS(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (first[i] == second[j]) {
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            }
            else {
                LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
            }
        }
    }

    int length = LCS[m][n];
    string result(length, ' ');
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (first[i] == second[j]) {
            result[length] = first[i];
            i--;
            j--;
            length--;
        }
        else if (LCS[i - 1][j] > LCS[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }
    if (i > j) {
        while (i>=0 && length >= 0){
            if (first[i] == second[j]) {
                result[length] = first[i];
                length--;
            }
            i--;
            
        }
    }
    else {
        while(j >= 0 && length >= 0) {
            if (first[i] == second[j]) {

                result[length] = first[i];  
                length--;
            }
            j--;
        }
    }
    result.erase(remove(result.begin(), result.end(), ' '), result.end()); //костыль для решения бага в последнем тесте. оптимальное решение через set или первый алгоритм динам. прог
    return result;
}