#include <flash_stm32.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
delay(100);
led_setup();
init_slave_communication();
init_rtc();
init_bluetooth_communication();
init_pot_controller();
}

void loop() {
  // put your main code here, to run repeatedly:
//print_time();
phone_connect();
check_watering();
turn_pot_auto_off();
//Serial.println(get_moisture(1));
delay(1);

}
