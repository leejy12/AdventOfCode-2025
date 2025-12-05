#include <algorithm>
#include <charconv>
#include <iostream>
#include <print>
#include <string>
#include <utility>
#include <vector>

using ull = unsigned long long;

int main()
{
    std::vector<std::pair<ull, char>> v;
    std::string s;
    ull start = 0;
    ull end = 0;

    while (std::getline(std::cin, s))
    {
        if (s.empty())
            break;

        const auto dash = s.find('-');

        std::from_chars(&s[0], &s[dash], start);
        std::from_chars(&s[dash + 1], &s[0] + s.size(), end);

        v.emplace_back(start, 'a');
        v.emplace_back(end, 'c');
    }

    std::ranges::sort(v);

    int now = 0;
    ull cnt = 0;
    ull last_a = 0;

    for (const auto& p : v)
    {
        if (p.second == 'a')
        {
            now++;
            if (now == 1)
            {
                last_a = p.first;
            }
        }
        else // (p.second == 'c')
        {
            now--;
            if (now == 0)
            {
                cnt += p.first - last_a + 1;
            }
        }
    }

    std::println("{}", cnt);
}