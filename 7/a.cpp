#include <iostream>
#include <print>
#include <string>
#include <vector>

int count_splits(std::vector<std::string>& grid)
{
    grid[0].replace(grid[0].find('S'), 1, 1, '|');
    const size_t L = grid[0].length();
    int splits = 0;

    for (size_t i = 0; i < grid.size() - 1; i++)
    {
        for (size_t j = 0; j < L; j++)
        {
            if (grid[i][j] == '|')
            {
                if (grid[i + 1][j] != '^') // == '.'
                {
                    // Beam goes straight.
                    grid[i + 1][j] = '|';
                }
                else
                {
                    // Beam splits. The indicies will never go out of range.
                    grid[i + 1][j - 1] = '|';
                    grid[i + 1][j + 1] = '|';
                    splits++;
                }
            }
        }
    }

    return splits;
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