#include "standard.h"
#include <thread>
#include <vector>

std::mutex mtx_estandar;

void calcular_histograma(int* histograma, const int* input, int inicio, int fin) {
  for (int idx = inicio; idx < fin; ++idx) {
    std::lock_guard<std::mutex> lock(mtx_estandar);
    histograma[input[idx] - 1]++;
  }
}

std::vector<int> Standard::calculate(const int* input, const int buckets, const int input_size) {
  std::vector<int> histogram(buckets, 0);
  const int num_threads = std::thread::hardware_concurrency();
  std::vector<std::thread> threads(num_threads);
  int chunk = input_size / num_threads;

  // Aquí se usa std::ref para pasar histogram por referencia
  for (int i = 0; i < num_threads; ++i) {
    int start = i * chunk;
    int end = (i == num_threads - 1) ? input_size : (i + 1) * chunk;
    threads[i] = std::thread(calcular_histograma, histogram.data(), input, start, end);
  }

  for (auto& t : threads) {
    t.join();
  }

  return histogram;
}
