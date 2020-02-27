bool watered = false;
uint32_t starting_millis_watering[] = {0, 0, 0, 0};

/*
   kontroluje samo zalevani
*/
void check_watering() {
  if (watered) {
    for(int i = 0; i < 4; i++){
      if(get_auto_watering(i)){
        if(abs(millis() - starting_millis_watering[i])>get_watering_duration(i)){
          pump_water(i + 1, 0);
        }
      }
    }
    return;
  }
  watered = true;
  for (int i = 0; i < 4; i++) {
    if (get_auto_watering(i)) {
      starting_millis_watering[i] = millis();
      pump_water(i + 1, 1);
    }
  }




}
