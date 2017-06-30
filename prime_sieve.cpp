#include <vector>
#include <deque>
#include <iostream>

std::size_t prime_sieve(std::size_t n)
{
    std::deque<bool> is_prime(n + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;

    for (auto factor = 2; factor * factor <= n; ++factor) {
        if (is_prime[factor]) {
            for (auto j = factor; factor * j <= n; ++j) {
                is_prime[factor * j] = false;
            }
        }
    }
    auto num_primes = std::size_t{0};
    for (const auto &e : is_prime) {
        num_primes += e ? 1 : 0;
    }
    return num_primes;
}

int main() {
    std::cout << prime_sieve(10) << "\n";
    std::cout << prime_sieve(100) << "\n";
    std::cout << prime_sieve(1'000) << "\n";
    std::cout << prime_sieve(10'000) << "\n";
    std::cout << prime_sieve(100'000) << "\n";
    std::cout << prime_sieve(1'000'000) << "\n";
    std::cout << prime_sieve(10'000'000) << "\n";
    std::cout << prime_sieve(100'000'000) << "\n";
    std::cout << prime_sieve(1'000'000'000) << "\n";
    return 0;
}