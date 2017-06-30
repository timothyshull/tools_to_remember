#include <string>
#include <vector>

std::string lcs(const std::string &x, const std::string &y)
{
    auto m = static_cast<int>(x.size()); // to avoid wraparound
    auto n = static_cast<int>(y.size()); // to avoid wraparound

    std::vector<std::vector<int>> opt(x.size() + 1, std::vector<int>(y.size() + 1));

    for (auto i = m - 1; i >= 0; --i) {
        for (auto j = n - 1; j >= 0; --j) {
            opt[i][j] = x[i] == y[j] ?
                        opt[i + 1][j + 1] + 1 :
                        std::max(opt[i + 1][j], opt[i][j + 1]);
        }
    }

    auto lcs = std::string{""};
    auto i = 0;
    auto j = 0;
    while (i < m && j < n) {
        if (x[i] == y[j]) {
            lcs += x[i];
            ++i;
            ++j;
        } else if (opt[i][j + 1] <= opt[i + 1][j]) {
            ++i;
        } else {
            ++j;
        }
    }
    return lcs;
}