#include <collar.h>

int vibrateLevels[10];
int vibrateTimes[10];
int shockLevels[10];
int shockTimes[10];

CollarTx *_tx;

void send_vibrate(int level) {
  _tx->transmit(CH1, VIBE, level);
}

void send_shock(int level) {
  _tx->transmit(CH1, SHOCK, level);
}