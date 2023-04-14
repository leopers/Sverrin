#pragma once

#include <functional>
#include <vector>

#include "heap.hpp"

template <typename T, typename F = std::less_equal<>>
class Priority_Queue {
public:
  T front() const { elements.front(); }

  void enqueue(T element) {
    elements.push_back(std::move(element));

    sift_up(elements, elements.size() - 1, f);
  }

  T dequeue() {
    auto first = std::move(elements.front());

    std::swap(elements.front(), elements.back());
    elements.pop_back(); 

    sift_down(elements, 0, f);

    return first;
  }

  auto size() const { return elements.size(); }

private:
  std::vector<T> elements;
  F f;
};
