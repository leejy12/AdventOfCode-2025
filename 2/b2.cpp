#include <cassert>
#include <charconv>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <set>
#include <string>
#include <string_view>

using ull = unsigned long long;

void test();

std::set<ull> g_invalid_ids;

int count_digits(ull n) noexcept
{
    int digits = 0;
    while (n > 0)
    {
        digits++;
        n /= 10;
    }
    return digits;
}

// Create a number that repeats `n` `cnt` times.
// e.g. repeat(789, 3) == 789789789.
ull repeat(ull n, int cnt)
{
    assert(cnt > 0);

    const int digits = count_digits(n);
    ull base = 1;

    // base = 10^digits
    for (int i = 0; i < digits; ++i)
        base *= 10;

    ull result = 0;
    for (int i = 0; i < cnt; ++i)
        result = result * base + n;

    return result;
}

// Adds invalid IDs in range [a, b]
ull sum_invalid_ids(ull a, ull b)
{
    ull sum = 0;

    auto it = g_invalid_ids.lower_bound(a);
    while (true)
    {
        if (it == g_invalid_ids.end() || *it > b)
        {
            break;
        }
        sum += *it;
        ++it;
    }

    return sum;
}

void init_invalid_ids()
{
    for (const int i : std::views::iota(1, 1000000))
        g_invalid_ids.insert(repeat(i, 2));
    for (const int i : std::views::iota(1, 10000))
        g_invalid_ids.insert(repeat(i, 3));
    for (const int i : std::views::iota(1, 100))
        g_invalid_ids.insert(repeat(i, 5));
    for (const int i : std::views::iota(1, 100))
        g_invalid_ids.insert(repeat(i, 7));
    for (const int i : std::views::iota(1, 10))
        g_invalid_ids.insert(repeat(i, 11));
}

int main()
{
    std::string s;
    std::cin >> s;

    init_invalid_ids();

    auto r = s | std::views::split(',') | std::views::transform([](auto r) {
                 return r | std::views::split('-') | std::views::transform([](auto r) {
                            std::string_view sv(r);
                            ull x = 0;
                            std::from_chars(sv.data(), sv.data() + sv.size(), x);
                            return x;
                        });
             }) |
             std::views::transform([](auto r) {
                 const ull a = *r.begin();
                 const ull b = *(std::next(r.begin()));
                 return sum_invalid_ids(a, b);
             });

    const ull answer = std::accumulate(r.begin(), r.end(), 0ULL);
    std::println("{}", answer);
}

void test()
{
    assert(repeat(123, 1) == 123);
    assert(repeat(123, 2) == 123123);
}
