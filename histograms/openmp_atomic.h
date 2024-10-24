#ifndef OPENMP_ATOMIC_H
#define OPENMP_ATOMIC_H

#include "histogram.h"
#include <atomic>

class OpenMPAtomic : public Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif  // OPENMP_ATOMIC_H
