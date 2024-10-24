#include <gtest/gtest.h>
#include <random>
#include "sequential.h"
#include "standard.h"
#include "standard_reduction.h"
#include "openmp_reduction.h"  // Faltaba incluir este
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

// Función que testea cualquier implementación de Histogram
void test_histogram_implementation(Histogram* histogramCalculator) {
  auto histograma = histogramCalculator->calculate(randomInput, MAXIMO_VALOR, NUMERO_ELEMENTOS);
  
  int acum = 0;
  for (auto puntuacion : histograma) acum += puntuacion;
  EXPECT_EQ(acum, NUMERO_ELEMENTOS);
}

// Tests para cada implementación

TEST(HistogramTest, SequentialTest) {
  Sequential histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

TEST(HistogramTest, StandardTest) {
  Standard histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

TEST(HistogramTest, StandardReductionTest) {
  StandardReduction histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

TEST(HistogramTest, OpenMPReductionTest) {  // Nuevo test agregado
  OpenMPReduction histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

TEST(HistogramTest, OpenMPAtomicTest) {
  OpenMPAtomic histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

TEST(HistogramTest, OpenMPLockGuardTest) {
  OpenMPLockGuard histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

TEST(HistogramTest, OpenMPLockUnlockTest) {
  OpenMPLockUnlock histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

TEST(HistogramTest, OpenMPCriticalTest) {
  OpenMPCritical histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

TEST(HistogramTest, OpenMPOMPAtomicTest) {
  OpenMPOMPAtomic histogramCalculator;
  test_histogram_implementation(&histogramCalculator);
}

int main(int argc, char** argv) {
  inicializa();
  ::testing::InitGoogleTest(&argc, argv);
  auto ret = RUN_ALL_TESTS();
  finaliza();
  return ret;
}
