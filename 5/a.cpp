// If the number of ranges is M and the number of ingredients is N,
// runtime is O(M * N).

#include <charconv>
#include <iostream>
#include <print>
#include <string>
#include <utility>
#include <vector>

using ull = unsigned long long;
using pull = std::pair<ull, ull>;

bool is_fresh(const std::vector<pull>& fresh_ranges, ull ingredient)
{
    for (const pull& range : fresh_ranges)
    {
        if (ingredient >= range.first && ingredient <= range.second)
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::vector<pull> fresh_ranges;
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

        fresh_ranges.emplace_back(start, end);
    }

    ull ingredient = 0;
    int cnt = 0;
    while (std::cin >> ingredient)
    {
        if (is_fresh(fresh_ranges, ingredient))
        {
            cnt++;
        }
    }

    std::println("{}", cnt);
}