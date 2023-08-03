#include "circularbuffer.h"
#include "mpmc.h"

void BM_mpmc_pushpop(benchmark::State& state) {
  uint8_t val = 42;
  MultiProducer::MultiConsumer::CircularBuffer buff(16);
  for (auto _ : state){
    buff.pushByte(val);
    buff.popByte(val);
  }
}
