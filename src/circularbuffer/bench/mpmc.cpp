#include "multiconsumermultiproducer.h"
#include "mpmc.h"


CircularBuffer::MultiConsumerMultiProducer buff(128);

void BM_mpmc_pushpop(benchmark::State& state) {
  uint8_t val = 42;
  for (auto _ : state){
    while(!buff.pushByte(val));
    while(!buff.popByte(val));
  }
}
