#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

template <typename T, unsigned N = 100>
struct stack
{
    void push(T val)
    {
        if (m_size >= N) {
            return;
        }
        m_values[m_size++] = val;
    }

    T pop()
    {
        if (m_size == 0) {
            return {};
        }
        T val = std::move(m_values[m_size - 1]);
        m_size--;

        return val;
    }

    T const& peek() { return m_values[m_size - 1]; }

    bool isEmpty() { return m_size == 0; }

    T   m_values[N];
    int m_size{ 0 };
};

template <typename T1, typename T2>
struct pair
{
    T1 t1;
    T2 t2;
};

void
f(int n)
{
    if (n >= 2) {
        f(n / 2);
    }
    std::cout << n;
}

void
sf(int n)
{
    stack<int> s{};
    while (n >= 2) {
        n /= 2;
        s.push(n);
    }
    while (!s.isEmpty()) {
        std::cout << s.pop();
    }
}

void
f1(int n)
{
    if (n > 1) {
        if (n % 2 == 0)
            f1(n / 2);
        else
            f1(3 * n + 1);
    }
    std::cout << n << ' ';
}

void
sf1(int n)
{
    stack<int> s{};
    s.push(n);

    while (n > 1) {
        if (n % 2 == 0) {
            n /= 2;
            s.push(n);
        } else {
            n = 3 * n + 1;
            s.push(n);
        }
    }
    while (!s.isEmpty())
        std::cout << s.pop() << ' ';

    std::cout << std::endl;
}

void
f2(int n)
{
    if (n >= 6) {
        f2(n / 3);
        f2(2 * n / 3);
    }
    std::cout << n << ' ';
}

void
sf2(int n)
{
    stack<std::tuple<int, bool>> s{};
    s.push({ n, false });

    while (!s.isEmpty()) {
        auto [val, visited] = s.pop();

        if (visited)
            std::cout << val << ' ';
        else {
            if (val >= 6) {
                s.push({ val, true });
                s.push({ 2 * val / 3, false });
                s.push({ val / 3, false });
            } else
                std::cout << val << ' ';
        }
    }

    std::cout << std::endl;
}

void
f3(int a, int b)
{
    if (a <= b) {
        int m = (a + b) / 2;
        f3(a, m - 1);
        std::cout << m << ' ';
        f3(m + 1, b);
    }
}

void
sf3(int a, int b)
{
    stack<pair<int, int>> s{};
    s.push({ a, b });

    while (!s.isEmpty()) {
        pair<int, int> val = s.pop();

        if (val.t1 > val.t2) {
            continue;
        }

        int m = (val.t1 + val.t2) / 2;
        if (val.t1 < val.t2) {
            s.push({ m + 1, val.t2 });
            s.push({ m, m });
            s.push({ val.t1, m - 1 });
            continue;
        }

        std::cout << val.t1 << ' ';
    }
}

void
f4(int a, int b)
{
    if (a <= b) {
        int m = (a + b) / 2;
        f4(a, m - 1);
        f4(m + 1, b);
        std::cout << m << ' ';
    }
}

void
sf4(int a, int b)
{
    stack<std::tuple<int, int, bool>> s{};
    s.push({ a, b, false });

    while (!s.isEmpty()) {
        auto [t1, t2, visited] = s.pop();

        if (t1 <= t2) {
            int m = (t1 + t2) / 2;

            if (visited)
                std::cout << m << ' ';
            else {
                s.push({ t1, t2, true });
                s.push({ m + 1, t2, false });
                s.push({ t1, m - 1, false });
            }
        }
    }
}

int
main()
{
    std::cout << "Recursive: \n";
    f4(4, 19);
    std::cout << std::endl;
    std::cout << "Non-recursive: \n";
    sf4(4, 19);
    std::cout << std::endl;

    return 0;
}