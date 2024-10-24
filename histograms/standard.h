#ifndef STANDARD_H
#define STANDARD_H

#include "histogram.h"
#include <mutex>

class Standard : public Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif  // STANDARD_H
