#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <vector>

class Histogram {
 public:
  virtual std::vector<int> calculate(const int*, const int, const int) = 0;
  virtual ~Histogram() = default;
};

#endif  // HISTOGRAM_H
