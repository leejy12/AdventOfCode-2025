#include <algorithm>
#include <iostream>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

/**
 * Converts a matrix `m` to reduced row echelon form.
 * This implements the pseudocode in https://rosettacode.org/wiki/Reduced_row_echelon_form.
 */
void gauss_elim(std::vector<std::vector<int>>& m)
{
    int lead = 0;
    const int numRows = static_cast<int>(m.size());
    const int numCols = static_cast<int>(m[0].size());

    for (int r = 0; r < numRows; r++)
    {
        if (numCols <= lead)
        {
            break;
        }

        int i = r;
        while (m[i][lead] == 0)
        {
            i++;
            if (numRows == i)
            {
                i = r;
                lead++;
                if (numCols == lead)
                {
                    break;
                }
            }
        }

        std::swap(m[i], m[r]);

        if (m[r][lead] != 0)
        {
            const int divisor = m[r][lead];
            for (int& v : m[r])
            {
                v /= divisor;
            }
        }

        for (int j = 0; j < numRows; j++)
        {
            if (j != r)
            {
                const int factor = m[j][lead];
                for (int k = 0; k < numCols; k++)
                {
                    m[j][k] -= factor * m[r][k];
                }
            }
        }

        lead++;
    }
}

void remove_zero_rows(std::vector<std::vector<int>>& m)
{
    for (auto it = m.begin(); it != m.end(); ++it)
    {
        if (std::ranges::all_of(*it, [](int x) { return x == 0; }))
        {
            m.erase(it, m.end());
            return;
        }
    }
}

std::vector<std::vector<int>> parse(const std::string& s)
{
    std::vector<std::vector<int>> m;

    const size_t light_end = s.find(']');
    const int num_lights = static_cast<int>(light_end - 1);
    const size_t switch_start = s.find('(');
    const size_t jolt_start = s.find('{');

    std::vector<std::vector<int>> m;
    m.resize(num_lights);

    for (size_t i = switch_start; i < jolt_start; i++)
    {
        if (s[i] == '(')
        {
            // new column
            for (auto& row : m)
                row.push_back(0);
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            m[s[i] - '0'].back() = 1;
        }
    }

    std::string_view jolt_sv(s.c_str() + jolt_start + 1, s.size() - jolt_start - 2);
    for (auto [row, rng] : std::views::enumerate(jolt_sv | std::views::split(',')))
    {
        std::string_view sv(rng);
        int x{};
        std::from_chars(sv.data(), sv.data() + sv.size(), x);
        m[row].push_back(x);
    }

    return m;
}

int main()
{
    std::string s;
    // int answer = 0;

    while (std::getline(std::cin, s))
    {
        std::vector<std::vector<int>> m = parse(s);
        gauss_elim(m);
        remove_zero_rows(m);
        std::println("{}", m);
    }

    // std::println("{}", answer);

    // std::vector<std::vector<int>> v{
    //     {0, 0, 0, 0, 1, 1, 3},
    //     {0, 1, 0, 0, 0, 1, 5},
    //     {0, 0, 1, 1, 1, 0, 4},
    //     {1, 1, 0, 1, 0, 0, 7},
    // };

    // std::vector<std::vector<int>> v{
    //     {1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 72},
    //     {0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 88},
    //     {0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 59},
    //     {0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 60},
    //     {1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 69},
    //     {0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 36},
    //     {0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 53},
    //     {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 64},
    //     {0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 58},
    //     {0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 81},
    // };

    // std::vector<std::vector<int>> v{
    //     {1, 2, -1, -4},
    //     {2, 3, -1, -11},
    //     {-2, 0, -3, 22},
    // };

    // gauss_elim(v);

    // for (const auto& row : v)
    //     std::println("{}", row);
}
