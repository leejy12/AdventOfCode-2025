#include <iostream>
#include <print>
#include <string>
#include <vector>

using pii = std::pair<int, int>;

std::vector<pii> get_roll_positions(const std::vector<std::string>& v)
{
    const auto R = v.size();
    const auto C = v[0].size();

    const auto is_roll = [&](int r, int c) { return r >= 0 && r < R && c >= 0 && c < C && v[r][c] == '@'; };
    std::vector<pii> positions;

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
                positions.emplace_back(r, c);
        }
    }

    return positions;
}

void remove_rolls(std::vector<std::string>& v, const std::vector<pii>& positions)
{
    for (const pii& pos : positions)
    {
        v[pos.first][pos.second] = '.';
    }
}

int count_rolls(std::vector<std::string>& v)
{
    int cnt = 0;

    while (true)
    {
        const auto positions = get_roll_positions(v);
        if (positions.empty())
            break;

        cnt += static_cast<int>(positions.size());
        remove_rolls(v, positions);
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
