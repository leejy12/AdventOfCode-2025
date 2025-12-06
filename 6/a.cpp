#include <algorithm>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

using ull = unsigned long long;

ull add(ull a, ull b) noexcept
{
    return a + b;
}

ull mul(ull a, ull b) noexcept
{
    return a * b;
}

using op_type = ull (*)(ull, ull);

int main()
{
    std::string s;
    std::vector<std::string> input;
    std::vector<std::vector<ull>> nums;
    std::vector<op_type> ops;

    while (std::getline(std::cin, s))
    {
        input.push_back(s);
    }

    // Parse numbers to initialize nums in column-major order.
    for (size_t i = 0; i < input.size() - 1; i++)
    {
        std::stringstream ss(input[i]);

        size_t col = 0;
        ull k = 0;
        while (ss >> k)
        {
            if (nums.size() <= col)
            {
                nums.emplace_back();
            }
            nums[col].push_back(k);
            col++;
        }
    }

    // Parse operators.
    std::stringstream ss(input.back());
    char c = 0;
    while (ss >> c)
    {
        ops.push_back(c == '+' ? add : mul);
    }

    const auto r = std::views::zip(nums, ops) | std::views::transform([](std::tuple<std::vector<ull>&, op_type&> elem) {
                       const std::vector<ull>& n = std::get<0>(elem);
                       const op_type op = std::get<1>(elem);
                       return std::ranges::fold_left_first(n, op).value();
                   });

    const auto ans = std::accumulate(r.begin(), r.end(), 0ULL);
    std::println("{}", ans);
}