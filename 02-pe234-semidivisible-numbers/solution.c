/* Project Euler 234 - Semidivisible Numbers
 * https://projecteuler.net/problem=234
 *
 * For consecutive primes p < q, every n in (p^2, q^2-1] has lps(n)=p and ups(n)=q.
 * So instead of testing each n up to N (~1e12), we sweep consecutive prime pairs up
 * to sqrt(N) and sum multiples of p or q (but not both) in that interval directly,
 * via inclusion-exclusion: sum(p) + sum(q) - 2*sum(p*q).
 */
#include <stdio.h>
#include <stdint.h>

#define N 999966663333ULL
#define LIMIT 1050000 /* > sqrt(N), with margin for the prime gap past it */

static unsigned char is_composite[LIMIT + 1];

static uint64_t sum_multiples(uint64_t d, uint64_t a, uint64_t b) {
    uint64_t k1 = (a + d - 1) / d;
    uint64_t k2 = b / d;
    if (k2 < k1) return 0;
    return d * (k1 + k2) * (k2 - k1 + 1) / 2;
}

int main(void) {
    uint64_t primes[85000];
    size_t prime_count = 0;

    for (uint64_t i = 2; i <= LIMIT; i++) {
        if (!is_composite[i]) {
            primes[prime_count++] = i;
            for (uint64_t j = i * i; j <= (uint64_t)LIMIT; j += i)
                is_composite[j] = 1;
        }
    }

    uint64_t total = 0;

    for (size_t idx = 0; idx + 1 < prime_count; idx++) {
        uint64_t p = primes[idx];
        uint64_t q = primes[idx + 1];

        uint64_t lower = p * p; /* n = lower excluded: lps(n)=ups(n)=p there */
        if (lower > N) break;

        uint64_t upper = (q * q - 1 < N) ? (q * q - 1) : N;
        uint64_t a = lower + 1, b = upper;
        if (a > b) continue;

        total += sum_multiples(p, a, b) + sum_multiples(q, a, b) - 2 * sum_multiples(p * q, a, b);
    }

    printf("%llu\n", (unsigned long long)total);
    return 0;
}
