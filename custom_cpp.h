// Built-in included libraries
#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <variant>
#include <thread>
#include <chrono>
#include <cstdint>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <type_traits>
#include <random>

using string = std::string;
using D64 = double;
using F32 = float;
using PList = std::vector<std::variant<string, int, D64, F32>>;

// Custom types
inline D64 time_ms() {
    using namespace std::chrono;
    return duration<D64, std::milli>(steady_clock::now().time_since_epoch()).count();
}

inline void write_file(const string &path, const string &content) {
    std::ofstream out(path);
    if (out.is_open()) out << content;
}

inline string read_file(const string &path) {
    std::ifstream in(path);
    if (!in.is_open()) return "";
    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

inline F32 to_F32(double var) {
    return static_cast<F32>(var);
}

inline double to_D64(F32 var) {
    return static_cast<double>(var);
}

// Output functions
template <typename T>
void print(const T &message, bool spec = false) {
    if (spec) {
        std::cout << message;
    } else {
        std::cout << message << std::endl;
    }
}

inline void print(const PList &list_data) {
    std::cout << "[";
    for (const auto &item : list_data) {
        std::visit([](const auto &val) { std::cout << val << ", "; }, item);
    }
    std::cout << " End_of_list_data]" << std::endl;
}

inline void print(int message, bool spec = false) {
    if (spec) {
        std::cout << message;
    } else {
        std::cout << message << std::endl;
    }
}

inline void print(D64 message, bool spec = false) {
    if (spec) {
        std::cout << std::to_string(message);
    } else {
        std::cout << std::to_string(message) << std::endl;
    }
}

inline void print(F32 message, bool spec = false) {
    if (spec) {
        std::cout << std::to_string(message);
    } else {
        std::cout << std::to_string(message) << std::endl;
    }
}

// Custom list functions
template <typename Op>
inline PList apply_PLs(const PList& fl, const PList& sl, Op op) {
    PList result;
    const size_t total = std::min(fl.size(), sl.size());

    for (size_t i = 0; i < total; ++i) {
        std::visit([&](const auto& a, const auto& b) {
            using T1 = std::decay_t<decltype(a)>;
            using T2 = std::decay_t<decltype(b)>;

            if constexpr (std::is_arithmetic_v<T1> &&
                          std::is_arithmetic_v<T2>) {
                result.emplace_back(op(a, b));
            } else {
                throw std::invalid_argument(
                    "List arithmetic requires numeric elements");
            }
        }, fl[i], sl[i]);
    }

    return result;
}

inline PList Add_PLs(const PList& fl, const PList& sl) {
    return apply_PLs(fl, sl, [](const auto& a, const auto& b) {
        return a + b;
    });
}

inline PList Sub_PLs(const PList& fl, const PList& sl) {
    return apply_PLs(fl, sl, [](const auto& a, const auto& b) {
        return a - b;
    });
}

inline PList Mul_PLs(const PList& fl, const PList& sl) {
    return apply_PLs(fl, sl, [](const auto& a, const auto& b) {
        return a * b;
    });
}

inline PList Div_PLs(const PList& fl, const PList& sl) {
    return apply_PLs(fl, sl, [](const auto& a, const auto& b) {
        if (b == 0) {
            throw std::domain_error("Division by zero in list arithmetic");
        }
        return a / b;
    });
}


inline PList list(const PList &var) {
    return var;
}

// Time waiting commands
inline void sleepS(D64 seconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int64_t>(seconds * 1000)));
}

inline void sleepMS(D64 milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int64_t>(milliseconds)));
}

inline void sleepNS(D64 nanoseconds) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(static_cast<int64_t>(nanoseconds)));
}

// Input & String helpers
inline string input(string message = "") {
    string rd;
    std::cout << message;
    std::cout.flush();
    if (!std::getline(std::cin, rd)) {
        rd = "";
    }
    return rd;
}

inline string str(D64 num) {
    return std::to_string(num);
}

inline string str(int num) {
    return std::to_string(num);
}

inline string str(string s) { // Helps function in the backend and programs from the user to run more smoothly without bugs
    return s;
}

inline string str(const PList& UPL) {
    string result;
    for (const auto& item : UPL) {
        std::visit([&result](const auto& value) {
            using T = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<T, string>) {
                result += value;
            } else {
                result += std::to_string(value);
            }
        }, item);
    }

    return result;
}

// Math & Type Conversions
inline D64 power(D64 v1, D64 v2) {
    return std::pow(v1, v2);
}

inline D64 square_root(D64 var) {
    return std::sqrt(var);
}

inline D64 abs(D64 var) {
    return std::abs(var);
}

inline D64 square_root(int var) {
    return std::sqrt(var);
}

inline int abs(int var) {
    return std::abs(var);
}

// PList functions

inline int len(const PList &var) {
    return var.size();
}

inline int len(const string &var) {
    return var.size();
}

inline void pop(PList &l) {
    if (!l.empty()) {
        l.pop_back();
    }
}

inline PList range(int start, int stop, int step = 1) {
    PList RL = {};
    int cn = start;
    if (step > 0) {
        while (cn < stop) {
            RL.push_back(cn);
            cn += step;
        }
    } else if (step < 0) {
        while (cn > stop) {
            RL.push_back(cn);
            cn += step;
        }
    }
    return RL;
}

// Convertion functions

inline D64 Convert_D64(F32 var) {
    return static_cast<D64>(var);
}

inline F32 Convert_C32(D64 var) {
    return static_cast<F32>(var);
}

// Random number functions

inline int RandomNumber() {
    srand(time(0));
    return rand();
}

inline int RandomInRange(int var1=1, int var2=10) {
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(var1, var2);
    return distribution(generator);
}

