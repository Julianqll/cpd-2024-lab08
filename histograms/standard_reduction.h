#ifndef STANDARD_REDUCTION_H
#define STANDARD_REDUCTION_H

#include "histogram.h"

class StandardReduction : public Histogram {
 public:
  std::vector<int> calculate(const int*, const int, const int) override;
};

#endif  // STANDARD_REDUCTION_H
