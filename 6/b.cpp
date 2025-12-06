#include <algorithm>
#include <iostream>
#include <print>
#include <string>
#include <vector>

using ull = unsigned long long;

ull solve(const std::vector<ull>& v, char op)
{
    if (op == '+')
        return std::ranges::fold_left_first(v, [](ull a, ull b) { return a + b; }).value();
    else // op == '*'
        return std::ranges::fold_left_first(v, [](ull a, ull b) { return a * b; }).value();
}

int main()
{
    std::string s;
    std::vector<std::string> input;
    std::vector<std::vector<ull>> nums;

    while (std::getline(std::cin, s))
    {
        input.push_back(s);
    }

    const int R = static_cast<int>(input.size());
    const int C = static_cast<int>(input[0].length());
    ull ans = 0;

    std::vector<ull> v;
    bool skip = false;
    for (int c = C - 1; c >= 0; c--)
    {
        if (skip)
        {
            skip = false;
            continue;
        }

        ull n = 0;
        for (int r = 0; r < R; r++)
        {
            const char ch = input[r][c];
            if (r < R - 1 && ch != ' ')
            {
                n = n * 10 + (ch - '0');
            }
            if (r == R - 1)
            {
                v.push_back(n);
                if (ch == '+' || ch == '*')
                {
                    ans += solve(v, ch);
                    v.clear();
                    skip = true;
                }
            }
        }
    }

    std::println("{}", ans);
}