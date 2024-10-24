#ifndef OPENMP_LOCK_GUARD_H
#define OPENMP_LOCK_GUARD_H

#include "histogram.h"
#include <mutex>

class OpenMPLockGuard : public Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif  // OPENMP_LOCK_GUARD_H
