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

ull my_pow(ull b, ull e) noexcept
{
    ull result = 1;
    for (int i = 0; i < e; i++)
    {
        result *= b;
    }
    return result;
}

ull next(ull n) noexcept
{
    const int d = count_digits(n);
    if (d % 2 == 1)
    {
        // e.g. n == XXX => return 1010.
        const int h = (d + 1) / 2;
        return my_pow(10, d) + my_pow(10, h - 1);
    }
    else
    {
        const int h = d / 2;
        const ull div = my_pow(10, h);
        const ull a = n / div; // first half
        const ull b = n % div; // second half

        // e.g. n == 4321 => return 4343.
        if (a > b)
        {
            return a * (div + 1);
        }
        // e.g. n == 9999 => return 100100.
        else if (a == div - 1)
        {
            return div * (div * 10 + 1);
        }
        // e.g. n == 1234 => return 1313.
        else
        {
            return (a + 1) * (div + 1);
        }
    }
}

// Adds invalid IDs in range [a, b]
ull sum_invalid_ids(ull a, ull b)
{
    ull sum = 0;

    // This is to make `next(n)` equal to `a` when `a` is an invalid id.
    ull n = a - 1;

    while (true)
    {
        n = next(n);
        if (n > b)
        {
            break;
        }
        sum += n;
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
    assert(next(5) == 11);
    assert(next(10) == 11);
    assert(next(123) == 1010);
    assert(next(1234) == 1313);
    assert(next(4321) == 4343);
    assert(next(999'999) == 1000'1000);

    assert(sum_invalid_ids(11, 22) == 33);
    assert(sum_invalid_ids(998, 1012) == 1010);
    assert(sum_invalid_ids(998, 1222) == 3333); // 1010, 1111, 1212
}
