#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <algorithm>

const int WINDOW = 5;
const int TOP_SIZE = 10;

int main() {
    std::freopen("traceLog", "r", stdin);
    std::freopen("statistics", "w", stdout);

    std::vector<std::map<std::vector<std::string>, int > > stats(WINDOW);
    std::vector<std::string> last_strings;
    std::string s;
    while(std::getline(std::cin, s)) {
        if (last_strings.size() == WINDOW) {
            last_strings.erase(last_strings.begin());
        }
        last_strings.push_back(s);
        for (int i = 0; i < last_strings.size(); ++i) {
            int window = last_strings.size() - i - 1;
            ++stats[window][std::vector(last_strings.begin() + i, last_strings.end())];
        }
    }

    for (int window = 0; window < 5; ++window) {
        std::vector<std::pair<std::vector<std::string>, int>> vec(
            stats[window].begin(), stats[window].end());

        std::sort(vec.begin(), vec.end(),
            [](const auto &a, const auto &b) { return a.second > b.second; });

        std::cout << "=== LENGTH " << (window + 1) << " PATTERNS ===\n";
        for (int i = 0; i < TOP_SIZE; ++i) {
            const auto& [seq, count] = vec[i];
            std::cout << "[" << count << "] ";
            for (size_t j = 0; j < seq.size(); ++j) {
                if (j) {
                    std::cout << ", ";
                }
                std::cout << seq[j];
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}