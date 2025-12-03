#include <algorithm>
#include <cassert>
#include <charconv>
#include <iostream>
#include <numeric>
#include <print>
#include <ranges>
#include <string>
#include <string_view>

using ull = unsigned long long;

void test();

// Determine if `sv` is a repetition of a substring of length `len`.
bool is_repeated_sequence(std::string_view sv, int len)
{
    if (sv.length() % len != 0 || len >= sv.length())
    {
        return false;
    }

    const int rep = sv.length() / len - 1;

    for (int i = 0; i < rep; i++)
    {
        if (!std::equal(sv.begin(), sv.begin() + len, sv.begin() + len * (i + 1), sv.begin() + len * (i + 2)))
        {
            return false;
        }
    }

    return true;
}

bool is_invalid(ull id)
{
    if (id < 10)
    {
        return false;
    }

    const std::string s = std::to_string(id);
    for (int divisor = 1; divisor < s.length(); divisor++)
    {
        if (is_repeated_sequence(s, divisor))
        {
            return true;
        }
    }
    return false;
}

// Adds invalid IDs in range [a, b]
ull sum_invalid_ids(ull a, ull b)
{
    ull sum = 0;

    for (ull n = a; n <= b; n++)
    {
        if (is_invalid(n))
        {
            sum += n;
        }
    }

    return sum;
}

int main()
{
    std::string s;
    std::cin >> s;

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
    assert(!is_repeated_sequence("1", 1));
    assert(is_repeated_sequence("11", 1));
    assert(!is_repeated_sequence("11", 2));
    assert(!is_repeated_sequence("12341234", 1));
    assert(!is_repeated_sequence("12341234", 2));
    assert(is_repeated_sequence("12341234", 4));
    assert(is_repeated_sequence("123123123", 3));

    assert(!is_invalid(1));
    assert(is_invalid(11));
    assert(is_invalid(222222));
    assert(is_invalid(1188511885));
    assert(!is_invalid(12345678));
}
