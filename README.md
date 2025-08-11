# Parallel Sum Example in C++

## Overview
This is a simple C++ program that demonstrates how to calculate the **sum** and **average** of an array using:
- **Single-threaded execution**
- **Multi-threaded execution** with the C++ `<thread>` library

The project compares the performance of both approaches.

---

## Files
- `main.cpp` — Source code for the parallel and single-thread sum calculation
---

## How to Compile & Run

### **Single-thread & Multi-thread version**
```bash
g++ main.cpp -o parallel_sum -pthread
./parallel_sum
```

---

## Results from the Report

| Execution Mode   | Sum          | Average      | Execution Time |
|------------------|-------------|--------------|----------------|
| Single-thread    | 500000050000 | 500000.05    | 0.003123 sec   |
| Multi-thread (4) | 500000050000 | 500000.05    | 0.001112 sec   |

> Multi-threading reduced execution time significantly compared to the single-threaded version.

---

## Example Output
```
Single-thread sum: 500000050000
Single-thread average: 500000.05
Execution time (single-thread): 0.003123 sec

Multi-thread sum: 500000050000
Multi-thread average: 500000.05
Execution time (multi-thread): 0.001112 sec
```

---

## Requirements
- C++11 or newer
- POSIX threads support (`-pthread` flag for compilation)

---

## 👨‍💻 Author
**Bekir Bozoklar - MSc Software Engineering **
