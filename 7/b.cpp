#include <iostream>
#include <numeric>
#include <print>
#include <string>
#include <vector>

long long count_splits(std::vector<std::string>& grid)
{
    const size_t L = grid[0].length();

    std::vector<std::vector<long long>> timeline(grid.size());
    for (auto& v : timeline)
    {
        v.resize(L);
    }

    const size_t start = grid[0].find('S');
    grid[0].replace(start, 1, 1, '|');
    timeline[0][start] = 1;

    for (size_t i = 0; i < grid.size() - 1; i++)
    {
        for (size_t j = 0; j < L; j++)
        {
            if (grid[i][j] == '|')
            {
                if (grid[i + 1][j] == '^')
                {
                    grid[i + 1][j - 1] = '|';
                    grid[i + 1][j + 1] = '|';
                    timeline[i + 1][j - 1] += timeline[i][j];
                    timeline[i + 1][j + 1] += timeline[i][j];
                }
                else
                {
                    grid[i + 1][j] = '|';
                    timeline[i + 1][j] += timeline[i][j];
                }
            }
        }
    }

    return std::accumulate(timeline.back().begin(), timeline.back().end(), 0LL);
}

int main()
{
    std::vector<std::string> grid;
    std::string s;
    while (std::cin >> s)
    {
        grid.push_back(s);
    }

    std::println("{}", count_splits(grid));
}