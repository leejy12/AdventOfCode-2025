#include <algorithm>
#include <execution>
#include <iostream>
#include <mutex>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

using pii = std::pair<int64_t, int64_t>;

struct Hline
{
    int64_t pos;
    int64_t start;
    int64_t end;

    Hline(int64_t pos, int64_t start, int64_t end) : pos(pos), start(start), end(end)
    {
    }

    bool above(const pii& p) const
    {
        return p.second <= pos && p.first >= start && p.first <= end;
    }

    bool below(const pii& p) const
    {
        return p.second >= pos && p.first >= start && p.first <= end;
    }
};

struct Vline
{
    int64_t pos;
    int64_t start;
    int64_t end;

    Vline(int64_t pos, int64_t start, int64_t end) : pos(pos), start(start), end(end)
    {
    }

    bool right(const pii& p) const
    {
        return p.first >= pos && p.second >= start && p.second <= end;
    }

    bool left(const pii& p) const
    {
        return p.first <= pos && p.second >= start && p.second <= end;
    }
};

int main()
{
    std::string s;
    std::vector<pii> v;

    while (std::cin >> s)
    {
        const size_t comma = s.find(',');
        const int64_t x = std::atoll(s.c_str());
        const int64_t y = std::atoll(s.c_str() + comma + 1);

        v.emplace_back(x, y);
    }

    std::vector<Vline> vlines;
    std::vector<Hline> hlines;

    const auto add_lines = [&](const pii& p1, const pii& p2) {
        if (p1.first == p2.first)
        {
            vlines.emplace_back(p1.first, std::min(p1.second, p2.second), std::max(p1.second, p2.second));
        }
        else
        {
            hlines.emplace_back(p1.second, std::min(p1.first, p2.first), std::max(p1.first, p2.first));
        }
    };

    for (const auto& [p1, p2] : v | std::views::pairwise)
    {
        add_lines(p1, p2);
    }
    add_lines(v.back(), v.front());

    const auto check_inside_boundary = [&](const pii& p) {
        return std::ranges::any_of(vlines, [&](const Vline& v) { return v.left(p); }) &&
               std::ranges::any_of(vlines, [&](const Vline& v) { return v.right(p); }) &&
               std::ranges::any_of(hlines, [&](const Hline& h) { return h.above(p); }) &&
               std::ranges::any_of(hlines, [&](const Hline& h) { return h.below(p); });
    };

    const auto check_all_inside_boundary = [&](const pii& p1, const pii& p2) {
        const int64_t x_min = std::min(p1.first, p2.first);
        const int64_t x_max = std::max(p1.first, p2.first);
        const int64_t y_min = std::min(p1.second, p2.second);
        const int64_t y_max = std::max(p1.second, p2.second);

        for (int64_t x = x_min; x <= x_max; x++)
            if (!check_inside_boundary(std::make_pair(x, y_min)))
                return false;
        for (int64_t x = x_min; x <= x_max; x++)
            if (!check_inside_boundary(std::make_pair(x, y_max)))
                return false;
        for (int64_t y = y_min; y <= y_max; y++)
            if (!check_inside_boundary(std::make_pair(x_min, y)))
                return false;
        for (int64_t y = y_min; y <= y_max; y++)
            if (!check_inside_boundary(std::make_pair(x_max, y)))
                return false;

        return true;
    };

    int64_t max_area = 0;
    std::vector<std::pair<pii, pii>> pairs;
    for (size_t i = 0; i < v.size(); i++)
        for (size_t j = i + 1; j < v.size(); j++)
            pairs.emplace_back(v[i], v[j]);

    std::mutex m;

    std::for_each(std::execution::par_unseq, pairs.begin(), pairs.end(), [&](const std::pair<pii, pii>& p) {
        if (check_all_inside_boundary(p.first, p.second))
        {
            const int64_t area =
                (std::abs(p.first.first - p.second.first) + 1) * (std::abs(p.first.second - p.second.second) + 1);
            std::lock_guard<std::mutex> lock(m);
            if (area > max_area)
                max_area = area;
        }
    });

    std::println("{}", max_area);
}
