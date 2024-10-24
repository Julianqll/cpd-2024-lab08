#include "standard_reduction.h"
#include <thread>
#include <vector>

void calcular_local_histograma(int* local_histogram, const int* input, int start, int end) {
  for (int idx = start; idx < end; ++idx) {
    local_histogram[input[idx] - 1]++;
  }
}

std::vector<int> StandardReduction::calculate(const int* input, const int buckets, const int input_size) {
  std::vector<int> histogram(buckets, 0);
  const int num_threads = std::thread::hardware_concurrency();
  std::vector<std::vector<int>> local_histograms(num_threads, std::vector<int>(buckets, 0));
  std::vector<std::thread> threads(num_threads);
  int chunk = input_size / num_threads;

  for (int i = 0; i < num_threads; ++i) {
    int start = i * chunk;
    int end = (i == num_threads - 1) ? input_size : (i + 1) * chunk;
    threads[i] = std::thread(calcular_local_histograma, local_histograms[i].data(), input, start, end);
  }

  for (auto& t : threads) {
    t.join();
  }

  for (int i = 0; i < num_threads; ++i) {
    for (int j = 0; j < buckets; ++j) {
      histogram[j] += local_histograms[i][j];
    }
  }

  return histogram;
}
