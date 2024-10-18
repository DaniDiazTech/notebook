/*
Function that generates a pseudo-random unsigned 64 bit number

Usage:
unsigned long long random_number = rng();
*/

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

/*
Static random number given an unsigned long long x
Complexity: O(1)
*/

static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
}

