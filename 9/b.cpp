#include <algorithm>
#include <execution>
#include <iostream>
#include <mutex>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

struct Point
{
    int64_t x;
    int64_t y;
};

struct Hline
{
    int64_t y_pos;
    int64_t start;
    int64_t end;

    Hline(int64_t y_pos, int64_t start, int64_t end) : y_pos(y_pos), start(start), end(end)
    {
    }

    bool above(const Point& p) const
    {
        return p.y <= y_pos && p.x >= start && p.x <= end;
    }

    bool below(const Point& p) const
    {
        return p.y >= y_pos && p.x >= start && p.x <= end;
    }

    auto operator<=>(const Hline& other) const = default;
    bool operator==(const Hline& other) const = default;
};

struct Vline
{
    int64_t x_pos;
    int64_t start;
    int64_t end;

    Vline(int64_t x_pos, int64_t start, int64_t end) : x_pos(x_pos), start(start), end(end)
    {
    }

    bool right(const Point& p) const
    {
        return p.x >= x_pos && p.y >= start && p.y <= end;
    }

    bool left(const Point& p) const
    {
        return p.x <= x_pos && p.y >= start && p.y <= end;
    }

    auto operator<=>(const Vline& other) const = default;
    bool operator==(const Vline& other) const = default;
};

int main()
{
    std::string s;
    std::vector<Point> v;

    while (std::cin >> s)
    {
        const size_t comma = s.find(',');
        const int64_t x = std::atoll(s.c_str());
        const int64_t y = std::atoll(s.c_str() + comma + 1);

        v.emplace_back(x, y);
    }

    std::vector<Vline> vlines;
    std::vector<Hline> hlines;

    const auto add_lines = [&](const Point& p1, const Point& p2) {
        if (p1.x == p2.x)
        {
            vlines.emplace_back(p1.x, std::min(p1.y, p2.y), std::max(p1.y, p2.y));
        }
        else
        {
            hlines.emplace_back(p1.y, std::min(p1.x, p2.x), std::max(p1.x, p2.x));
        }
    };

    for (const auto& [p1, p2] : v | std::views::pairwise)
    {
        add_lines(p1, p2);
    }
    add_lines(v.back(), v.front());

    std::ranges::sort(vlines);
    std::ranges::sort(hlines);

    const auto check_inside_boundary = [&](const Point& p) {
        auto it_x =
            std::upper_bound(vlines.begin(), vlines.end(), p.x, [](int64_t x, const Vline& v) { return x <= v.x_pos; });
        if (std::none_of(it_x, vlines.end(), [&](const Vline& v) { return v.left(p); }))
            return false;
        while ((*it_x).x_pos == p.x)
            ++it_x;
        if (std::none_of(vlines.begin(), it_x, [&](const Vline& v) { return v.right(p); }))
            return false;

        auto it_y =
            std::upper_bound(hlines.begin(), hlines.end(), p.y, [](int64_t y, const Hline& h) { return y <= h.y_pos; });
        if (std::none_of(it_y, hlines.end(), [&](const Hline& h) { return h.above(p); }))
            return false;
        while ((*it_y).y_pos == p.y)
            ++it_y;
        if (std::none_of(hlines.begin(), it_y, [&](const Hline& h) { return h.below(p); }))
            return false;

        return true;
    };

    const auto check_all_inside_boundary = [&](const Point& p1, const Point& p2) {
        const int64_t x_min = std::min(p1.x, p2.x);
        const int64_t x_max = std::max(p1.x, p2.x);
        const int64_t y_min = std::min(p1.y, p2.y);
        const int64_t y_max = std::max(p1.y, p2.y);

        for (int64_t x = x_min; x <= x_max; x++)
            if (!check_inside_boundary(Point{x, y_min}))
                return false;
        for (int64_t x = x_min; x <= x_max; x++)
            if (!check_inside_boundary(Point{x, y_max}))
                return false;
        for (int64_t y = y_min; y <= y_max; y++)
            if (!check_inside_boundary(Point{x_min, y}))
                return false;
        for (int64_t y = y_min; y <= y_max; y++)
            if (!check_inside_boundary(Point{x_max, y}))
                return false;

        return true;
    };

    int64_t max_area = 0;
    std::vector<std::pair<Point, Point>> pairs;
    for (size_t i = 0; i < v.size(); i++)
        for (size_t j = i + 1; j < v.size(); j++)
            pairs.emplace_back(v[i], v[j]);

    std::mutex m;

    std::for_each(std::execution::par_unseq, pairs.begin(), pairs.end(), [&](const std::pair<Point, Point>& p) {
        if (check_all_inside_boundary(p.first, p.second))
        {
            const int64_t area = (std::abs(p.first.x - p.second.x) + 1) * (std::abs(p.first.y - p.second.y) + 1);
            std::lock_guard<std::mutex> lock(m);
            if (area > max_area)
                max_area = area;
        }
    });

    std::println("{}", max_area);
}
