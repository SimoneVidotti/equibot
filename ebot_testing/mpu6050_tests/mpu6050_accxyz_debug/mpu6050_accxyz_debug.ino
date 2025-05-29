#include <vidottiequibotlib.h>

equibot myebot(0);

void setup() {
  myebot.ebot_setup();
}

void loop() {
  myebot.mpu_loop_update();
  myebot.debug_accxyz();
}
