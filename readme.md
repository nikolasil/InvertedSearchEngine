# Multi-Threaded Inverted Search Engine & Parallel Optimizer

Inspired by the **SIGMOD 2013 Programming Contest**, this system is a high-performance search engine optimized for massive document streams. It manages thousands of concurrent queries (Exact, Edit Distance, and Hamming Distance) using a custom-built parallel execution framework.



---

## 🚀 Core Architecture: The Job Scheduler

The backbone of the system is a custom **Job Scheduler** that manages a thread-safe task queue with $O(1)$ insertion and removal.

### Parallel Execution Model
To prevent data race conditions and maintain cache locality, the scheduler implements **Type-Based Batching**:
* **Group Execution:** Jobs are grouped by type (`StartQuery`, `MatchDocument`, `EndQuery`). 
* **Synchronization Barriers:** A barrier-based synchronization mechanism ensures that all query updates (`StartQuery`) are fully committed before matching begins, preventing "dirty reads" without the overhead of heavy locking.
* **Main Thread Sync:** Uses condition variables to allow the main thread to wait for batch completion, ensuring results are only gathered once parallel processing is finalized.



---

## 🔍 Search & Optimization Engines

### 1. Exact Match (Inverted Hash Table)
* **Optimization:** Replaced standard SHA1 with a lightweight, thread-optimized hash function to minimize CPU cycles.
* **Lock-Free Read Path:** By isolating `MatchArray` storage to thread-local heap space, lookup operations are entirely lock-free, significantly reducing contention during high-load document matching.

### 2. Fuzzy Match (BK-Trees)
The system supports Edit and Hamming distance thresholds (1-3) via **BK-Trees**.
* **Pruning Logic:** Instead of multiple tree traversals for different thresholds, the lookup function was optimized to recursively prune subtrees using the current threshold as a dynamic bound.
* **Complexity:** Search time is reduced to $O(log N)$, making fuzzy matching viable for real-time streams.



---

## 📈 Performance & Scalability

The system achieves near-linear scaling by minimizing the critical section size. Mutexes are placed only where strictly necessary (e.g., final result aggregation).

| Configuration | Execution Time (ms) | Speedup |
| :--- | :--- | :--- |
| **Serial (1 Thread)** | 1395ms | 1.0x |
| **Parallel (2 Threads)** | 771ms | 1.8x |
| **Parallel (4 Threads)** | 522ms | 2.6x |

*Tested on 4-core Linux environment. Performance peaks at 4 threads, matching physical core count, proving minimal synchronization overhead.*

---

## 🛠️ Technical Keypoints
* **Memory Management:** Utilized a centralized Query Object registry with reference-passing to reduce the memory footprint to just **4MB** for millions of operations.
* **Thread Safety:** Replaced `strtok()` with `strtok_r()` and implemented `pthread_barrier` for rigid task-group boundaries.
* **Data Locality:** High-performance `MatchArray` design ensures each thread writes to localized memory, avoiding "False Sharing" and cache misses.

---



## 🎓 Academic Context
Developed as part of the National and Kapodistrian University of Athens (UoA).

## Getting Started

### Compilation
```bash
make       # Compile project
make test  # Compile unit tests
```
