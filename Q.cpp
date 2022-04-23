// Implements bijective mapping from N to NxN and NxN to N.

#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <tuple>

using std::atoi;
using std::cout;
using std::invalid_argument;
using std::strtoull;
using std::tuple;

using N = unsigned long long int;
using NxN = tuple<N, N>;
using NxNxNxNxN = tuple<N, N, N, N, N>;

constexpr N NxN_to_N(N m, N n) noexcept
{
    if (m == 1 && n == 1)
        return 1;
    if (n != 1)
        return NxN_to_N(m + 1, n - 1) + 1;
    else
        return NxN_to_N(1, m - 1) + 1;
}

namespace detail
{
namespace
{
    constexpr NxNxNxNxN N_to_NxN_recursive(NxNxNxNxN v) noexcept
    {
        auto const [i, j, k, m, n] = v;
        if (j == i)
            return v;
        if (j == k)
            return N_to_NxN_recursive({ i, j + 1, k + n + 1, n + 1, 1 });
        else
            return N_to_NxN_recursive({ i, j + 1, k, m - 1, n + 1 });
    }
} // namespace
} // namespace detail

constexpr NxN N_to_NxN(N i) noexcept
{
    auto const [i_, j, k, m, n] = detail::N_to_NxN_recursive({ i, 1, 1, 1, 1 });
    return { m, n };
}

auto string_to_N(char const* str) -> N
{
    char* endptr = nullptr;
    N const result = strtoull(str, &endptr, 10);
    if (!endptr || *endptr != 0)
        throw invalid_argument("Not a valid number.");
    return result;
}

int main(int argc, char const* argv[])
{
    try
    {
        switch (argc - 1)
        {
            case 1: {
                auto const i = string_to_N(argv[1]);
                auto const [m, n] = N_to_NxN(i);
                cout << i << " -> " << m << '/' << n << '\n';
                break;
            }
            case 2: {
                auto const m = string_to_N(argv[1]);
                auto const n = string_to_N(argv[2]);
                auto const i = NxN_to_N(m, n);
                cout << m << '/' << n << " -> " << i << '\n';
                break;
            }
            default: cout << "Usage error.\n";
        }
    }
    catch (std::exception const& e)
    {
        cout << "Error. " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
