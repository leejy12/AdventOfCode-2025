#include <cstdlib>
#include <iostream>
#include <print>
#include <string>
#include <utility>
#include <vector>

int main()
{
    std::string s;
    std::vector<std::pair<int64_t, int64_t>> v;

    while (std::cin >> s)
    {
        const auto comma = s.find(',');
        const auto x = std::atoll(s.c_str());
        const auto y = std::atoll(s.c_str() + comma + 1);

        v.emplace_back(x, y);
    }

    int64_t max_area = 0;

    for (size_t i = 0; i < v.size(); i++)
    {
        for (size_t j = i + 1; j < v.size(); j++)
        {
            const int64_t area = (std::abs(v[i].first - v[j].first) + 1) * (std::abs(v[i].second - v[j].second) + 1);
            if (area > max_area)
                max_area = area;
        }
    }

    std::println("{}", max_area);
}
