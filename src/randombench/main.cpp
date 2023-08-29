#include <benchmark/benchmark.h>
#include <mutex>
#include <atomic>

class Spinlock
{
private:
    std::atomic_flag atomic_flag = ATOMIC_FLAG_INIT;

public:
    void lock()
    {
       while (atomic_flag.test_and_set(std::memory_order_acquire))
        {
        }
     
    }
    void unlock()
    {
        atomic_flag.clear(std::memory_order_release);
    }
};

Spinlock g_spin;

void BM_spinlock(benchmark::State& state) {
  Spinlock& spin = g_spin;
  for (auto _ : state){
    spin.lock();
    spin.unlock();
  }
}

std::mutex m;

void BM_mutex(benchmark::State& state) {
  for (auto _ : state){
    std::unique_lock<std::mutex> lock(m);
  }
}

// Register the function as a benchmark
BENCHMARK(BM_spinlock)->ThreadRange(1, 32);
BENCHMARK(BM_mutex)->ThreadRange(1, 32);
BENCHMARK_MAIN();