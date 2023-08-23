#include "singleconsumersingleproducer.h"
#include "1p1c.h"

void BM_1pc1c_pushpop(benchmark::State& state) {
  uint8_t val = 42;
  CircularBuffer::SingleConsumerSingleProducer buff(16);
  for (auto _ : state){
    buff.pushByte(val);
    buff.popByte(val);
  }
}
