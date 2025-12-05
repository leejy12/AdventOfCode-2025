#include <iostream>
#include <print>
#include <string>
#include <vector>

int count_rolls(const std::vector<std::string>& v)
{
    const auto R = v.size();
    const auto C = v[0].size();

    const auto is_roll = [&](int r, int c) { return r >= 0 && r < R && c >= 0 && c < C && v[r][c] == '@'; };
    int cnt = 0;

    for (int r = 0; r < R; r++)
    {
        for (int c = 0; c < C; c++)
        {
            int adj_rolls = 0;
            if (!is_roll(r, c))
                continue;

            for (int dr : {-1, 0, 1})
                for (int dc : {-1, 0, 1})
                    if (!(dr == 0 && dc == 0) && is_roll(r + dr, c + dc))
                        adj_rolls++;

            if (adj_rolls < 4)
                cnt++;
        }
    }

    return cnt;
}

int main()
{
    std::vector<std::string> v;
    std::string s;

    while (std::cin >> s)
    {
        v.push_back(s);
    }

    std::println("{}", count_rolls(v));
}
