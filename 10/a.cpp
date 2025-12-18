#include <algorithm>
#include <bit>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

int solve(const std::string& s)
{
    const size_t light_end = s.find(']');
    const int num_lights = static_cast<int>(light_end - 1);

    int target = 0;
    for (size_t i = 1; i < light_end; i++)
    {
        target <<= 1;
        if (s[i] == '#')
            target |= 1;
    }

    const size_t jolt_start = s.find('{');
    std::string_view switches_sv(&s[light_end + 2], jolt_start - light_end - 3);

    const std::vector<int> switches =
        switches_sv | std::views::split(' ') | std::views::transform([&](auto rng) {
            int val = 0;
            for (const auto r : std::ranges::subrange(rng.begin() + 1, rng.end() - 1) | std::views::split(','))
            {
                val |= 1 << (num_lights - 1 - (*r.begin() - '0'));
            }
            return val;
        }) |
        std::ranges::to<std::vector<int>>();

    int min_cnt = INT_MAX;
    for (unsigned int n = 0; n < (1u << switches.size()); n++)
    {
        int value = 0;
        const int cnt = std::popcount(n);
        for (size_t i = 0; i < switches.size(); i++)
        {
            if (n & (1 << i))
            {
                value ^= switches[i];
            }
        }

        if (value == target && cnt < min_cnt)
        {
            min_cnt = cnt;
        }
    }

    return min_cnt;
}

int main()
{
    std::string s;
    std::vector<std::string> v;

    while (std::getline(std::cin, s))
    {
        v.push_back(s);
    }

    std::vector<int> answers(v.size());
    std::transform(v.begin(), v.end(), answers.begin(), solve);

    const int answer = std::accumulate(answers.begin(), answers.end(), 0);
    std::println("{}", answer);
}