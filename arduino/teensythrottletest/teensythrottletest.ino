void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.printf("begin\n");
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.printf("serial began\n");
    

    // Initialize inputs.
    
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.printf("loop\n");
  uint32_t cur_millis = millis();
  static uint32_t blink_period = 0;
    if (throttle_ms(1000, cur_millis, &blink_period)) {
        digitalWriteFast(LED_BUILTIN, (uint8_t)(!digitalReadFast(LED_BUILTIN)));
    Serial.printf("throttled\n");
    
  }
}

bool throttle_ms(uint32_t period_ms, uint32_t cur_time, uint32_t *prev_period) {
    uint32_t cur_period = cur_time / period_ms;
    if (cur_period == *prev_period) {
        return false;  // We're in the same period
    } else {
        //if (slips && *prev_period && cur_period != *prev_period+1)(*slips)++;
        *prev_period = cur_period;
        return true;
    }
}




