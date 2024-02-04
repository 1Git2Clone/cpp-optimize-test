#include <chrono>
#include <iostream>
#include <list>
#include <unordered_map>

// https://stackoverflow.com/questions/19964909/returning-an-unordered-map-inside-an-unordered-map-from-a-function
typedef std::unordered_map<uint, uint> keyAndValue;
typedef std::unordered_map<keyAndValue, std::list<int>::iterator> cacheMatch;

void evalResult(uint n, uint res, cacheMatch cmatch) {
  keyAndValue knv = {n, res};
  knv.emplace(n, res);
  cmatch.emplace(knv, res);
}
int checkForMatch(uint n, cacheMatch cmatch);

// RAW Calculation
void calculateSumToZero(uint n) {

  if (n <= 1) {
    std::cout << "Sum of | " << n << " | is -> " << n << '\n';
    return;
  }

  int res = 0;
  std::cout << "Sum of | " << n;

  while (n > 0)
    res += n--;

  std::cout << " | is -> " << res << '\n';
}
int main(int argc, char **argv) {

  auto start = std::chrono::high_resolution_clock::now();

  // PROGRAM:
  //
  cacheMatch values;
  int csize; // maximum capacity of cache

  int nums[] = {100000, 100000, 100000, 100000, 100000};
  for (int num : nums)
    calculateSumToZeroOptimized(num);

  // END OF PROGRAM

  auto end = std::chrono::high_resolution_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(end - start)
          .count();

  std::cout << "Time it took: " << duration << " microseconds." << std::endl;

  return 0;
}
