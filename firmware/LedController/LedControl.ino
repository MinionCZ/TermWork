#define red_led1 PA6
#define red_led2 PA7
#define red_led3 PA3
#define red_led4 PB0
#define blue_led1 PA2
#define blue_led2 PA1
#define blue_led3 PA0
#define blue_led4 PB7

int red_led_pins[] = {PA6, PA7, PA3, PB0};
int blue_led_pins[] = {PB7, PA1, PA0, PA2};
float power_factor[] = {0, 0, 0, 0};
float red_permilles[] = {0, 0, 0, 0};
float blue_permilles[] = {0, 0, 0, 0};


void led_setup() {
  pinMode(red_led1, PWM);
  pinMode(red_led2, PWM);
  pinMode(red_led3, PWM);
  pinMode(red_led4, PWM);
  pinMode(blue_led1, PWM);
  pinMode(blue_led2, PWM);
  pinMode(blue_led3, PWM);
  pinMode(blue_led4, PWM);
  pwmWrite(red_led1, 65535);
  pwmWrite(red_led2, 65535);
  pwmWrite(red_led3, 65535);
  pwmWrite(red_led4, 65535);
  pwmWrite(blue_led1, 65535);
  pwmWrite(blue_led2, 65535);
  pwmWrite(blue_led3, 65535);
  pwmWrite(blue_led4, 65535);
}

/*
   params
   int led_number - cislo ledky
   int permilles - vykon v promilich
*/
void lightUpRedLed(uint8_t led_number, float permilles) {
  float power = 65535 - 65535 * (permilles / 1000);
  pwmWrite(red_led_pins[led_number - 1], power);
  red_permilles[led_number] = power;
  update_power(led_number);
}
/*
   params
   int led_number - cislo ledky
   int permilles - vykon v promilich
   max 35W
*/
void lightUpBlueLed(uint8_t led_number, float permilles) {
  float power = 65535 - 39321 * (permilles / 1000);
  pwmWrite(blue_led_pins[led_number - 1], power);
  blue_permilles[led_number] = power;
  update_power(led_number);
  
}
/*
   params
   int index pro ktere 2 ledky ma vypocitat vykon
*/
void update_power(int index) {
  power_factor[index] = red_permilles[index] / 1000 * 30 + blue_permilles[index] / 1000 * 30;
}
