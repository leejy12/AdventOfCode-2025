#include <cstdlib>
#include <iostream>
#include <print>
#include <string>

int mod(int a, int m) noexcept
{
    return (a % m + m) % m;
}

int main()
{
    int dial = 50;
    int cnt = 0;

    std::string s;
    while (std::cin >> s)
    {
        const int d = std::atoi(&s[1]);
        dial += (s[0] == 'R') ? d : -d;
        dial = mod(dial, 100);

        if (dial == 0)
        {
            cnt++;
        }
    }

    std::println("{}", cnt);
}
