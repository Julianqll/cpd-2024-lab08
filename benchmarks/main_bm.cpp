#include <benchmark/benchmark.h>
#include <random>
#include "sequential.h"
#include "standard.h"
#include "standard_reduction.h"
#include "openmp_reduction.h"
#include "openmp_atomic.h"
#include "openmp_lock_guard.h"
#include "openmp_lock_unlock.h"
#include "openmp_critical.h"
#include "openmp_ompatomic.h"

static int* randomInput = nullptr;
static const int MAXIMO_VALOR = 5;
static const int NUMERO_ELEMENTOS = 100000000;

void inicializa() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> uni_dis(1, MAXIMO_VALOR);

  if (randomInput == nullptr) {
    randomInput = new int[NUMERO_ELEMENTOS];
    for (int i = 0; i < NUMERO_ELEMENTOS; ++i) {
      randomInput[i] = uni_dis(gen);
    }
  }
}

void finaliza() {
  if (randomInput != nullptr) {
    delete[] randomInput;
    randomInput = nullptr;
  }
}

static void BM_secuencial(benchmark::State& state) {
  Sequential histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_standard(benchmark::State& state) {
  Standard histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_standard_reduction(benchmark::State& state) {
  StandardReduction histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_openmp_reduction(benchmark::State& state) {
  OpenMPReduction histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_openmp_atomic(benchmark::State& state) {
  OpenMPAtomic histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_openmp_lock_guard(benchmark::State& state) {
  OpenMPLockGuard histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_openmp_lock_unlock(benchmark::State& state) {
  OpenMPLockUnlock histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_openmp_critical(benchmark::State& state) {
  OpenMPCritical histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

static void BM_openmp_ompatomic(benchmark::State& state) {
  OpenMPOMPAtomic histogramCalculator;
  for (auto _ : state) {
    auto histograma = histogramCalculator.calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
    benchmark::DoNotOptimize(histograma);
  }
}

BENCHMARK(BM_secuencial)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_standard)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_standard_reduction)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_reduction)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_atomic)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_lock_guard)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_lock_unlock)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_critical)->UseRealTime()->Unit(benchmark::kMillisecond);
BENCHMARK(BM_openmp_ompatomic)->UseRealTime()->Unit(benchmark::kMillisecond);

int main(int argc, char** argv) {
  inicializa();
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  finaliza();
}
