#pragma once
// Needed when compiling c++17 and Eigen library
#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mutex>
#include <shared_mutex>
#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <array>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <functional>
#include <optional>
#include <cassert>
#include <thread>
#include <mutex>
#include <atomic>
#include <list>
#include <future>
#include <execution>
#include <exception>
#include <type_traits>

#ifdef WINDOWS
#include <Windows.h>
#include <numbers>
#else
#define _USE_MATH_DEFINES
#include <cmath>
#ifndef M_PI
  #define M_PI (3.14159265358979323846)
#endif
constexpr double pi = 3.14159265358979323846;
#endif