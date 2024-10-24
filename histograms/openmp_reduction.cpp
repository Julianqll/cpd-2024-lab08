#include "openmp_reduction.h"
#include <omp.h>

std::vector<int> OpenMPReduction::calculate(const int* input, const int buckets, const int input_size) {
  // Utilizamos un array C-style para la reducción de OpenMP
  int* histogram = new int[buckets]();  // Inicializamos el arreglo a 0

#pragma omp parallel for reduction(+ : histogram[:buckets])
  for (int idx = 0; idx < input_size; ++idx) {
    histogram[input[idx] - 1]++;
  }

  // Convertimos el array C-style a un std::vector para devolver
  std::vector<int> result(buckets);
  for (int i = 0; i < buckets; ++i) {
    result[i] = histogram[i];
  }

  // Liberamos la memoria del array C-style
  delete[] histogram;

  return result;
}
