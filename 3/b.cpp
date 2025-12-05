#include <array>
#include <cassert>
#include <deque>
#include <iostream>
#include <print>
#include <string>
#include <utility>

using ull = unsigned long long;

void test();

ull max_jolt(const std::string& s, int N)
{
    std::array<std::deque<int>, 10> a{};

    for (int i = 0; i < s.size(); i++)
    {
        const int idx = s[i] - '0';
        a[idx].push_back(i);
    }

    ull jolt = 0;
    for (int n = N; n >= 1; n--)
    {
        for (int k = 9; k >= 1; k--)
        {
            if (a[k].empty())
            {
                continue;
            }

            const int k_pos = a[k].front();
            if (k_pos <= s.size() - n)
            {
                jolt = jolt * 10 + k;

                for (std::deque<int>& d : a)
                {
                    while (!d.empty() && d.front() <= k_pos)
                    {
                        d.pop_front();
                    }
                }
                break;
            }
        }
    }

    return jolt;
}

int main()
{
    ull sum = 0;
    std::string s;

    while (std::cin >> s)
    {
        sum += max_jolt(s, 12);
    }

    std::println("{}", sum);
}

void test()
{
    const int N = 12;

    assert(max_jolt("987654321111111", N) == 987654321111);
    assert(max_jolt("811111111111119", N) == 811111111119);
    assert(max_jolt("818181911112111", N) == 888911112111);
    assert(max_jolt("234234234234278", N) == 434234234278);
}