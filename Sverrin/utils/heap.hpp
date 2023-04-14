#pragma once

#include <vector>

template <typename T, typename F>
std::size_t sift_down(std::vector<T>& x, std::size_t i, F f) {
  const auto n = x.size();
  const auto l = 2 * i + 1;
  const auto r = 2 * i + 2;
  auto highest_priority = i;

  if (l < n && !f(x[highest_priority], x[l]))
    highest_priority = l;

  if (r < n && !f(x[highest_priority], x[r]))
    highest_priority = r;

  if (highest_priority != i) {
    std::swap(x[i], x[highest_priority]);
    return sift_down(x, highest_priority, f);
  }

  return i;
}

template <typename T, typename F>
std::size_t sift_up(std::vector<T>& x, std::size_t i, F f) {
  if (i == 0)
    return i;

  const auto p = (i - 1) / 2;

  if (!f(x[p], x[i])) {
    std::swap(x[p], x[i]);
    return sift_up(x, p, f);
  }

  return i;
}
