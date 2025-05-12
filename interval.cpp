#include "interval.h"

const Interval Interval::empty = Interval(kInfinity, -kInfinity);
const Interval Interval::universe = Interval(-kInfinity, kInfinity);