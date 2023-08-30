#include <stack/leaky_lockfree.h>
#include <stack/waiting.h>
#include <benchmark/benchmark.h>


Stack::WaitFree::Stack<uint8_t> wf;
Stack::Waiting::Stack<uint8_t> ws;
  

void BM_stack_waitfree(benchmark::State& state) {
  Stack::Node<uint8_t>* node = new Stack::Node<uint8_t>(0);
  for (auto _ : state){
    wf.push(node);
    node = nullptr;
    while(!node)
      node = wf.pop();
  }
}

void BM_stack_waiting(benchmark::State& state) {
  Stack::Node<uint8_t>* node = new Stack::Node<uint8_t>(0);
  for (auto _ : state){
    ws.push(node);
    node = ws.pop();
  }
}

BENCHMARK(BM_stack_waitfree)->ThreadRange(1, 32);
BENCHMARK(BM_stack_waiting)->ThreadRange(1, 32);
BENCHMARK_MAIN();