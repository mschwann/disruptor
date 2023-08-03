#include "circularbuffer.h"
#include "1p1c.h"

void BM_1pc1c_pushpop(benchmark::State& state) {
  uint8_t val = 42;
  SingleProducer::SingleConsumer::CircularBuffer buff(16);
  for (auto _ : state){
    buff.pushByte(val);
    buff.popByte(val);
  }
}
