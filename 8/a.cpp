#include <algorithm>
#include <array>
#include <cassert>
#include <charconv>
#include <iostream>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

using ull = unsigned long long;

class UnionFind
{
private:
    std::vector<int> parent;
    std::vector<int> size;

public:
    UnionFind(int n)
    {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void merge(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY)
            return;

        if (size[rootX] < size[rootY])
        {
            parent[rootX] = rootY;
            size[rootY] += size[rootX];
        }
        else
        {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }

    std::map<int, int> get_component_sizes()
    {
        std::map<int, int> root_to_size;
        for (int i = 0; i < parent.size(); i++)
        {
            const int root = find(i);
            root_to_size[root] = size[root];
        }
        return root_to_size;
    }
};

ull dist_sq(const std::array<ull, 3>& a, const std::array<ull, 3>& b) noexcept
{
    const ull dx = a[0] - b[0];
    const ull dy = a[1] - b[1];
    const ull dz = a[2] - b[2];
    return dx * dx + dy * dy + dz * dz;
}

int main()
{
    std::string s;
    std::vector<std::array<ull, 3>> v;

    while (std::cin >> s)
    {
        auto nums = s | std::views::split(',') | std::views::transform([](auto r) {
                        std::string_view sv(r);
                        ull x = 0;
                        std::from_chars(sv.data(), sv.data() + sv.size(), x);
                        return x;
                    });

        std::array<ull, 3> arr;
        for (auto [i, n] : std::views::enumerate(nums))
        {
            arr[i] = n;
        }
        v.push_back(arr);
    }

    std::vector<std::tuple<ull, int, int>> pairs;

    for (int i = 0; i < v.size(); i++)
        for (int j = i + 1; j < v.size(); j++)
            pairs.push_back(std::make_tuple(dist_sq(v[i], v[j]), i, j));

    std::ranges::sort(pairs);

    UnionFind uf(static_cast<int>(v.size()));

    for (auto [dist, i, j] : pairs | std::views::take(1000))
    {
        uf.merge(i, j);
    }

    std::vector<int> sizes = uf.get_component_sizes() |
                             std::views::transform([](const auto& pair) { return pair.second; }) |
                             std::ranges::to<std::vector>();
    std::ranges::sort(sizes, std::greater<>{});
    const int ans = sizes[0] * sizes[1] * sizes[2];
    std::println("{}", ans);
}