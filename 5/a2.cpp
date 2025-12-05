// If the number of ranges is M and the number of ingredients is N,
// runtime is O((M + N) * log(M + N))

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

    ull ingredient = 0;
    while (std::cin >> ingredient)
    {
        v.emplace_back(ingredient, 'b');
    }

    std::ranges::sort(v);

    int now = 0;
    int cnt = 0;
    for (const auto& p : v)
    {
        if (p.second == 'a')
            now++;
        else if (p.second == 'c')
            now--;
        else if (p.second == 'b' && now > 0)
            cnt++;
    }

    std::println("{}", cnt);
}