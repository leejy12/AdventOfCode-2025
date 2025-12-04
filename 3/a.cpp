#include <array>
#include <cassert>
#include <iostream>
#include <print>
#include <string>
#include <utility>

void test();

int max_jolt(const std::string& s)
{
    std::array<std::pair<int, int>, 10> a{};
    a.fill({-1, -1});

    for (int i = 0; i < s.size(); i++)
    {
        int idx = s[i] - '0';
        if (a[idx].first == -1)
        {
            a[idx].first = i;
        }
        else
        {
            a[idx].second = i;
        }
    }

    for (auto& p : a)
    {
        if (p.second == -1)
        {
            p.second = p.first;
        }
    }

    for (int n = 9; n >= 1; n--)
    {
        if (a[n].first != -1 && a[n].first != s.size() - 1)
        {
            for (int m = 9; m >= 1; m--)
            {
                if (a[m].second != -1 && a[m].second > a[n].first)
                {
                    return 10 * n + m;
                }
            }
        }
    }

    std::unreachable();
}

int main()
{
    int sum = 0;
    std::string s;

    while (std::cin >> s)
    {
        sum += max_jolt(s);
    }

    std::println("{}", sum);
}

void test()
{
    assert(max_jolt("987654321111111") == 98);
    assert(max_jolt("811111111111119") == 89);
    assert(max_jolt("234234234234278") == 78);
    assert(max_jolt("818181911112111") == 92);

    assert(max_jolt("1253784") == 84);
    assert(max_jolt("1955558") == 98);
    assert(max_jolt("1955857") == 98);
    assert(max_jolt("9911111") == 99);
    assert(max_jolt("9811119") == 99);
    assert(max_jolt("8711119") == 89);

    exit(0);
}