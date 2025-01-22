/**
 * @file a1.cpp
 * @author Zirui Wang (21zw105@queensu.ca)
 * @brief
 * @version 0.1
 * @date 2025-01-20
 *
 * @copyright Copyright (c) 2025
 *
 * I confirm that this submission is my own work and is consistent with the
 * Queen's regulations on Academic Integrity
 *
 * Part 3 Answer:
 * The strategy I choose is double the capacity every time I increase the size
 * of array. I would say this is already a good choice consider that we don't
 * know the exact capacity of results, this balance the usage of elements copy
 * and re-alloc memory, we do can increase the capacity by a constant number so
 * we don't waste a ton of memory, but this increase the time of re-alloc array.
 * In addition, as I know, double the capacity is the most common way for
 * ensuring the array or list capacity, Java does the same thing on ArrayList.
 */

#include <cstring>
#include <initializer_list>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

template <typename T>
struct stack
{
    stack(int cap = 10)
        : m_values(new T[cap])
        , m_count(0)
        , m_size(cap)
    {
    }

    ~stack()
    {
        if (m_values != nullptr) {
            delete[] m_values;
        }
        m_count = 0;
        m_size  = 0;
    }

    void ensure() { ensure(m_count + 1); }

    void ensure(int cap)
    {
        if (cap <= m_size) {
            return;
        }
        resize(m_size * 2);
    }

    void resize(int cap)
    {
        if (cap == m_size) {
            return;
        }
        T* arr = new T[cap];
        std::memset(arr, 0, sizeof(T) * cap);

        int c = m_size < cap ? m_size : cap;
        for (int i = 0; i < c; i++) {
            arr[i] = m_values[i];
        }

        delete[] m_values;
        m_values = arr;
        m_size   = cap;
    }

    void push(T val)
    {
        ensure();
        m_values[m_count] = val;
        m_count++;
    }

    T pop()
    {
        if (m_count == 0) {
            return {};
        }
        T val = std::move(m_values[m_count - 1]);
        m_count--;

        return val;
    }

    T const& peek() { return m_values[m_count - 1]; }

    bool isEmpty() { return m_count == 0; }

    T*  m_values;
    // T   m_values[10];
    int m_count{ 0 };
    int m_size{ 10 };
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

void
test(void (*func)(int), std::initializer_list<int> list)
{
    for (int t : list) {
        func(t);
        std::cout << std::endl;
    }
}
void
test(void (*func)(int, int), std::initializer_list<std::tuple<int, int>> list)
{
    for (std::tuple<int, int> tuple : list) {
        func(std::get<0>(tuple), std::get<1>(tuple));
        std::cout << std::endl;
    }
}

int
main()
{
    std::cout << "Function 1 Recursive: \n";
    test(f1, { 7, 18, 19, 22, 105 });
    std::cout << "Function 1 Non-recursive: \n";
    test(sf1, { 7, 18, 19, 22, 105 });

    std::cout << "Function 2 Recursive: \n";
    test(f2, { 7, 18, 19, 22, 43 });
    std::cout << "Function 2 Non-recursive: \n";
    test(sf2, { 7, 18, 19, 22, 43 });

    std::cout << "Function 3 Recursive: \n";
    test(f3, { { 0, 7 }, { 1, 18 }, { 4, 19 }, { -1, 22 } });
    std::cout << "Function 3 Non-recursive: \n";
    test(sf3, { { 0, 7 }, { 1, 18 }, { 4, 19 }, { -1, 22 } });

    std::cout << "Function 4 Recursive: \n";
    test(f4, { { 0, 7 }, { 1, 18 }, { 4, 19 }, { -1, 22 } });
    std::cout << "Function 4 Non-recursive: \n";
    test(sf4, { { 0, 7 }, { 1, 18 }, { 4, 19 }, { -1, 22 } });

    return 0;
}