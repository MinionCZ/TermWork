uint32_t last_control = 0;
uint8_t starting_hours [7] = {0, 0, 0, 0, 0, 0, 0};
uint8_t starting_minutes [7] = {0, 0, 0, 0, 0, 0, 0};
uint8_t duration_hours[7] = {0, 0, 0, 0, 0, 0, 0};
uint8_t duration_minutes[7] = {0, 0, 0, 0, 0, 0, 0};
uint8_t ending_hours[7] = {0, 0, 0, 0, 0, 0, 0};
uint8_t ending_minutes[7] = {0, 0, 0, 0, 0, 0, 0};
bool led_on [] = {false, false, false, false};


/*
   params
   long duration - delka mezi kontrolami v ms
   slouzi k automatickemu vypnuti a zapnuti svetla podle casu
*/
void auto_led_(uint32_t duration) {
  if (abs(millis() - last_control) < duration) return;
  last_control = millis();
  for (int i = 0; i < 4; i++) {
    if (get_timer_status(i)) {
      if (starting_hours[i] == get_hour() && starting_minutes[i] == get_minute()) {
        led_on[i] = true;
      }
      if (led_on[i]) {
        if (ending_hours[i] == get_hour() && ending_minutes[i] == get_minute()) {
          led_on [i] = false;
        }
      }


    }
  }



}
