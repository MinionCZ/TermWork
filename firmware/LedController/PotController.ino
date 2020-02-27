#define pot1_sensor PA8
#define pot2_sensor PA11
#define pot3_sensor PA12
#define pot4_sensor PA15
#define pot1_led = PB12
#define pot2_led = PB13
#define pot3_led = PB14
#define pot4_led = PB15
int pot_sensors[] = {PA8, PA11, PA12, PA15};
int pot_leds[] = {PB12, PB13, PB14, PB15};
uint32_t last_signal_millis[] = {0, 0, 0, 0};
bool is_on[] = {false, false, false, false};
int moisture_percentage[] = {0, 0, 0, 0};
uint32_t last_millis_moisture = 0;

void init_pot_controller() {
  for (int i = 0; i < 4; i++) {
    pinMode(pot_sensors[i], INPUT);
    pinMode(pot_leds[i], OUTPUT);
    digitalWrite(pot_leds[i], LOW);
  }
}

/*
  params
  index - index kvetinace
  zapne ledky na kvetinaci
*/
void signalize_pot(int index) {
  index--;
  digitalWrite(pot_leds[index], HIGH);
  last_signal_millis[index] = millis();
  is_on[index] = true;
}

/*
   automaticky vypne po 5 sekundach roysvicene kvetinace
*/
void turn_pot_auto_off() {
  for (int i = 0; i < 4; i++) {
    if (is_on[i]) {
      if (abs(millis() - last_signal_millis[i]) >= 5000) {
        digitalWrite(pot_leds[i], LOW);
      }
    }
  }
}

/*
   vraci stav zaliti
*/
int get_moisture(int index) {
  index--;
  return digitalRead(pot_sensors[index]);
}
