// YOU NEED CUSTOM COMPILATION OPTIONS!

// g++ -o hell3 hell3.cpp -mavx -march=native -Ofast
// Ofast isn't required, but if you wish to test
// the most optimized version then It's required.

// AVX optimizations aren't practical here, however
// the simple hash table caching is a really big plus
// My benches (3600X -Ofast -mavx -march=native):
// 450 microseconds, 536 microseconds, 415 microseconds

// considering how the CPU needs to do the calculation once
// and then only look up the hash table a lot. It's not shocking
// that the result here isn't much more different from hell1+3.cpp

#include <chrono>
#include <immintrin.h> // AVX header
#include <iostream>
#include <unordered_map>

std::unordered_map<int, long long int> cache;

long long int sum_up_to_n(int n) {

  if (cache.find(n) != cache.end()) {
    return cache[n];
  }

  // Initialize sum variable
  long long int sum = 0;

  // Use AVX to perform parallel additions
  __m256i sum_vector =
      _mm256_setzero_si256(); // Initialize AVX vector with zeros

  // Loop through integers from 1 to n using AVX
  for (int i = 1; i <= n; i += 8) {
    // Create an AVX vector with consecutive integers [i, i+1, ..., i+7]
    __m256i current_int =
        _mm256_set_epi32(i + 7, i + 6, i + 5, i + 4, i + 3, i + 2, i + 1, i);

    // Add current_int to sum_vector using AVX instructions
    sum_vector = _mm256_add_epi32(sum_vector, current_int);
  }

  // Sum up the elements of the sum_vector
  int avx_sum[8]; // 8 integers in an AVX register
  _mm256_storeu_si256((__m256i *)avx_sum, sum_vector);
  sum = avx_sum[0] + avx_sum[1] + avx_sum[2] + avx_sum[3] + avx_sum[4] +
        avx_sum[5] + avx_sum[6] + avx_sum[7];

  cache[n] = sum;

  return sum;
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();

  int nums[] = {
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000,
      100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000, 100000};
  for (int num : nums)
    std::cout << "Sum of integers up to " << num << ": " << sum_up_to_n(num)
              << '\n';

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  std::cout << "Program finished in " << duration << " microseconds."
            << std::endl;
  return 0;
}
