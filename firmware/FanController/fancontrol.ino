#define fan1 PA1
#define fan2 PB6
#define fan3 PA0
#define fan4 PB7
#define fan5 PA2//chladic buck convereteru
int fans[] = {PB7, PA1 ,PA0 ,PB6 , PA2};
bool fans_on[] = {0, 0, 0, 0, 0};
void init_fans() {

  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(fan3, OUTPUT);
  pinMode(fan4, OUTPUT);
  pinMode(fan5, OUTPUT);
  digitalWrite(fan1, LOW);
  digitalWrite(fan2, LOW);
  digitalWrite(fan3, LOW);
  digitalWrite(fan4, LOW);
  digitalWrite(fan5, LOW);
}
bool is_fan_on(int index) {
  return fans_on[index];
}
/*
   nastavuje vykon na vetraku
*/
void set_fan_power(int index, bool on) {
  index--;
  digitalWrite(fans[index], on);
  fans_on[index] = on;
  set_boost_on();
  delay(1);
}
void set_boost_on() {
  bool on = false;
  for (int i = 0; i < 4; i++) {
    if (fans_on[i]) {
      digitalWrite(fan5, HIGH);
      return;
    }
  }
  digitalWrite(fan5, LOW);
}
