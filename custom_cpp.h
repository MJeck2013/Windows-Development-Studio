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
    for (const auto &item : list_data) {
        std::visit([](const auto &val) { std::cout << val << " "; }, item);
    }
    std::cout << std::endl;
}

// Custom list functions
inline PList Add_Mainlists(const PList &fl, const PList &sl) {
    PList rd;
    size_t total = fl.size();
    if (sl.size() < total) {
        total = sl.size();
    }

    for (size_t cc = 0; cc < total; ++cc) {
        std::visit([&rd](const auto &a, const auto &b) {
            using T1 = std::decay_t<decltype(a)>;
            using T2 = std::decay_t<decltype(b)>;

            if constexpr (std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>) {
                rd.push_back(a + b);
            } 
            else if constexpr (std::is_same_v<T1, string> && std::is_same_v<T2, string>) {
                rd.push_back(a + b);
            } 
            else {
                if constexpr (std::is_arithmetic_v<T1>) {
                    rd.push_back(std::to_string(a) + b);
                } else if constexpr (std::is_arithmetic_v<T2>) {
                    rd.push_back(a + std::to_string(b));
                }
            }
        }, fl[cc], sl[cc]);
    }

    return rd;
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


inline D64 Convert_D64(F32 var) {
    return static_cast<D64>(var);
}

inline F32 Convert_C32(D64 var) {
    return static_cast<F32>(var);
}