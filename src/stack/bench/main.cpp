#include <stack/leaky_lockfree.h>
#include <stack/waiting.h>
#include <benchmark/benchmark.h>



void BM_stack_waitfree(benchmark::State& state) {
  Stack::WaitFree::Stack<uint8_t> ll;
  Stack::Node<uint8_t>* node = new Stack::Node<uint8_t>(0);
  for (auto _ : state){
    ll.push(node);
    node = ll.pop();
  }
}

void BM_stack_waiting(benchmark::State& state) {
  Stack::Waiting::Stack<uint8_t> ll;
  Stack::Node<uint8_t>* node = new Stack::Node<uint8_t>(0);
  for (auto _ : state){
    ll.push(node);
    node = ll.pop();
  }
}

BENCHMARK(BM_stack_waitfree)->ThreadRange(1, 32);
BENCHMARK(BM_stack_waiting)->ThreadRange(1, 32);
BENCHMARK_MAIN();