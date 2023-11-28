#include <iostream>
#include <vector>

long long waysToMove(int n, int m) {
    std::vector<std::vector<long long>> ways(n + 1, std::vector<long long>(m + 1, 0));
    ways[0][0] = 1;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (i > 0) {
                ways[i][j] += ways[i - 1][j];
            }
            if (j > 0) {
                ways[i][j] += ways[i][j - 1];
            }
        }
    }

    return ways[n][m];
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::cout << waysToMove(n, m) << std::endl;
    return 0;
}