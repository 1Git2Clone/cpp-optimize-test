#include <chrono>
#include <emmintrin.h> // SSE header
#include <iostream>
#include <unordered_map>

std::unordered_map<int, long long int> cache;

void sum_up_to_n(int n) {
  // Initialize sum variable
  long long int sum = 0;

  // Use SSE to perform parallel additions
  __m128i sum_vector = _mm_setzero_si128(); // Initialize SSE vector with zeros

  // Loop through integers from 1 to n using SSE
  for (int i = 1; i <= n; i += 4) {
    // Create an SSE vector with consecutive integers [i, i+1, i+2, i+3]
    __m128i current_int = _mm_setr_epi32(i, i + 1, i + 2, i + 3);

    // Add current_int to sum_vector using SSE instructions
    sum_vector = _mm_add_epi32(sum_vector, current_int);
  }

  // Sum up the elements of the sum_vector
  int sse_sum[4]; // 4 integers in an SSE register
  _mm_storeu_si128((__m128i *)sse_sum, sum_vector);
  sum = sse_sum[0] + sse_sum[1] + sse_sum[2] + sse_sum[3];

  cache[n] = sum;

  std::cout << "Sum of integers up to " << n << ": " << sum << '\n';
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
    sum_up_to_n(num);

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  std::cout << "Program finished in " << duration << " microseconds."
            << std::endl;
  return 0;
}
