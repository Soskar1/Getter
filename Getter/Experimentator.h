#ifndef EXPERIMENTATOR_H
#define EXPERIMENTATOR_H

#define EXPERIMENT_COUNT 50

#include <functional>
#include <chrono>

double GetAverageExecutionTime(const std::function<void()>& function, const std::function<void()>& inputFunction = []() {});

#endif