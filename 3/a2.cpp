#include <iostream>
#include <print>
#include <string>

void test();

int to_int(char c)
{
    return c - '0';
}

int max_jolt(const std::string& s)
{
    char x = 0;
    char y = 0;

    for (const char c : s)
    {
        if (x < y)
        {
            x = y;
            y = c;
        }
        else if (y < c)
        {
            y = c;
        }
    }

    return 10 * to_int(x) + to_int(y);
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
