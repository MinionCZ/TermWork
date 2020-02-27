bool led_timer_on[] = {false, false, false, false};
bool auto_watering[] = {false, false, false, false};
uint16_t watering_duration[] = {0, 0, 0, 0};

#define bt Serial3
const char phone_sequence[] = "#knock!";
/*
   params
   int index - index ledek
*/
bool get_timer_status(int index) {
  return led_timer_on[index];
}

void init_bluetooth_communication() {
  bt.begin(9600);
}

bool get_auto_watering(int index) {
  return auto_watering[index];
}
uint16_t get_watering_duration(int index) {
  return watering_duration[index];
}


/*
   vyhodnocuje situace připojení telefonu
*/

void phone_connect() {
  if (bt.available() == 0) return;
  int last_value = 0;
  while(bt.available()>last_value){
    last_value = bt.available();
    delay(2);
  }
  Serial.println(bt.available());
  if (bt.available() < 7) {
    while (bt.available() != 0) bt.read();
  }
  if (bt.available() == 7) {
    if (check_auth()) {

      bt.println("#knock!");
    } else {
      bt.println("unauth");
    }
  }
  if (bt.available() > 7) {
    if (check_auth()) {
      if (bt.read() == 's') {
        Serial.println("s");
        bt_set_commands();
      } else {
        get_commands();
      }
    }
  }

}
/*
   ověření zda-li se uživatel připojil správně přes aplikaci
*/
bool check_auth() {
  bool auth = true;
  for (int i = 0; i < 7; i++) {
    char readed = (char)bt.read();
    if ( readed != phone_sequence[i]) {
      auth = false;
    }
  }
  return auth;
}
/*
   rozcestnik pro nastavovaci příkazy
*/
void bt_set_commands() {
  if (bt.read() == 'm') {
    manual_set_commands();
    Serial.println("m");
  }
}
/*
   vyhodnocování manuálních příkazů

*/
void manual_set_commands() {
  char command_type = bt.read();
  switch (command_type) {
    case 'w':
      if (get_water_level() > 0) {
        pump_water(to_int(bt.read()), to_int(bt.read()));
        Serial.println("here");
      } else {
        bt.println("#knock!nowater");
      }

      break;
    case 'l': {//rozsviceni ledky
        int i = to_int(bt.read());
        int percent_red = to_int(bt.read()) * 100 + to_int(bt.read()) * 10 + to_int(bt.read());
        int percent_blue = to_int(bt.read()) * 100 + to_int(bt.read()) * 10 + to_int(bt.read());
        lightUpRedLed(i, percent_red * 10);
        lightUpBlueLed(i, percent_blue * 10);
        if(percent_red == 0 && percent_blue == 0){
          change_fan_state(i, 0);
        }else{
          change_fan_state(i, 1);
        }
        break;
      }
    case 'p': {//rozsviti kvetinac
        int index = to_int(bt.read());
        signalize_pot(index);
        break;
      }

  }
}
void get_commands(){
  char ch = bt.read();
  switch(ch){
    case 'm':
    int index = to_int(bt.read());
    bt.println(get_moisture(index));
    Serial.println(index);
    Serial.println(get_moisture(index));
    break;
  }
}
