#include <stack/leaky_lockfree.h>

#include <benchmark/benchmark.h>

void BM_stack(benchmark::State& state) {
  Stack<uint8_t> ll;
  Node<uint8_t>* node = new Node<uint8_t>(0);
  for (auto _ : state){
    ll.push(node);
    node = ll.pop();
  }
}

BENCHMARK(BM_stack)->ThreadRange(1, 32);

BENCHMARK_MAIN();