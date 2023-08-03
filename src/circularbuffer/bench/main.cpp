#include "1p1c.h"
#include "mpmc.h"
#include "linkedList.h"

void BM_linkedlist(benchmark::State& state) {
  LinkedList<uint8_t> ll;
  Node<uint8_t>* node = new Node<uint8_t>(0);
  for (auto _ : state){
    ll.appendNode(node);
    node = ll.popNode();
  }
}


// Register the function as a benchmark
BENCHMARK(BM_mpmc_pushpop)->ThreadRange(1, 32);
BENCHMARK(BM_linkedlist)->ThreadRange(1, 32);
BENCHMARK(BM_1pc1c_pushpop);

BENCHMARK_MAIN();