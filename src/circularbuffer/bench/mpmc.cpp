#include "multiconsumermultiproducer.h"
#include "mpmc.h"

void BM_mpmc_pushpop(benchmark::State& state) {
  uint8_t val = 42;
  CircularBuffer::MultiConsumerMultiProducer buff(64);
  for (auto _ : state){
    while(!buff.pushByte(val));
    while(!buff.popByte(val));
  }
}
