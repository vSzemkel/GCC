
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using intvec = std::vector<int64_t>;
intvec g_input, g_partial;

int64_t partial_sum(const int i, const int j) { return g_partial[j + 1] - g_partial[i]; }
void incl_scan(const intvec& src, intvec& dst) {int64_t s{0}; dst = {0}; for (const auto& n : src) { s += n; dst.push_back(s); };}

int64_t solve() {
    return 0;
}

int main(int argc, char* argv[])
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // parse console input
    int no_of_cases, size;
    std::cin >> no_of_cases;
    for (int g = 1; g <= no_of_cases; ++g) {
        std::cin >> size;
        g_input.resize(size);
        for (auto& c : g_input) std::cin >> c;
        // Set 1
        std::cout << "Case #" << g << ": " << std::setprecision(15) << solve() << "\n";
    }
}

/*
clang++.exe -Wall -ggdb3 -O0 -std=c++17 $TASKNAME$.cpp -o $TASKNAME$.exe
$TASKNAME$.exe < $TASKNAME$.in

Input:


Output:


*/