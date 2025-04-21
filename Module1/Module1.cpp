//c++ module1
#include <algorithm>
#include <iostream>
#include <cassert>
#include<vector>
//tarb1 1
int partition_copy(const int A[], const int N, int p, int B[]) {
    int left = 0, right = N;
    for (int i = 0; i < N; ++i) {
        if (A[i] < p) {
            B[left++] = A[i];
        } else {
            B[--right] = A[i];
        }
    }
    assert(left == right);
    return left;
}
//tarb2 1
void merge_inc_dec(const int A[], int m, const int B[], int n, int C[]) {
    int i = 0, j = n - 1;
    int k = 0;
    while (i < m && j >= 0) {
        if (A[i] < B[j]) {
            C[k++] = A[i];
        } else {
            C[k++] = B[j--];
        }
    }
    if (i < m) {
        std::copy(A + i, A + m, C + k);
    }
    if (j >= 0) {
        std::copy(B, B + j + 1, C + k);
    }
}
//tarb1 2
long long options_count_for(int N) {
    std::vector<long long> cnt(std::max(4, N + 1), 0);
    cnt[0] = 1;
    cnt[1] = 0;
    cnt[2] = 1;
    cnt[3] = 1;
    for (int i = 4; i <= N; ++i) {
        cnt[i] = cnt[i - 2] + cnt[i - 3] + cnt[i - 4];
    }
    return cnt[N];
}

long long options_count(int N, int k) {
    return options_count_for(k) * options_count_for(N) - k;
}
//tarb2 2
int maximal_bonus_subsequence(const std::string &x, const std::string &y, int bonuses[4]) {
    const int m = x.size();
    const int n = y.size();
    std::vector<std::vector<int> > A(m + 1, std::vector<int>((n + 1), 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; ++j) {
            if (x[i - 1] == y[j - 1]) {
                A[i][j] = A[i - 1][j - 1] + bonuses[x[i - 1] - 'a'];
            } else {
                A[i][j] = std::max(A[i - 1][j], A[i][j - 1]);
            }
        }
    }
    return A[m][n];
}
//tarb1 3
struct Stone {
    int value;
    bool isBlack;
};

bool exists_stones_subset(const std::vector<Stone> &x, int S) {
    const int N = x.size();
    std::vector<std::vector<int> > byEvenBlack(N + 1, std::vector<int>(S + 1, 0));

    std::vector<std::vector<int> > byOddBlack(N + 1, std::vector<int>(S + 1, 0));
    byEvenBlack[0][0] = 1;
    for (int k = 1; k <= N; ++k) {
        for (int s = 1; s <= S; ++s) {
            byEvenBlack[k][s] = byEvenBlack[k - 1][s];
            byOddBlack[k][s] = byOddBlack[k - 1][s];
            if (x[k].value <= s){
                if (x[k].isBlack ) {
                    byEvenBlack[k][s] += byOddBlack[k - 1][s - x[k].value];
                    byOddBlack[k][s] += byEvenBlack[k - 1][s - x[k].value];
                } else {
                    byEvenBlack[k][s] += byEvenBlack[k - 1][s - x[k].value];
                    byOddBlack[k][s] += byOddBlack[k - 1][s - x[k].value];
                }
            }
        }
    }
    return byEvenBlack[N][S];
}
//tarb2 3
struct Rect {
    int lenght;
    int width;
};

bool fits(const Rect &r1, const Rect &r2) {
    return r1.lenght < r2.lenght && r1.width < r2.width;
}

int longest_nested_chain(std::vector<Rect> x) {
    for ( Rect& r : x) {
        if ( r.lenght < r.width ) {
            std::swap(r.lenght, r.width);
        }
    }
    const int N = x.size();;
    std::vector<int> L (N,1);
    for ( int i = N-2;i>=0;i--) {
        for ( int j = i+1;j<N;++j) {
            if (fits(x[i],x[j])) {
                L[i] =std::max(L[i],L[j]+1);
            }
        }
    }
    return *std::max_element(L.cbegin(),L.cend());
}