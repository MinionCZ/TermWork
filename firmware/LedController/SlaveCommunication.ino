#define Slave Serial1

bool gt_on = false;//bool jestli byl odeslan request o cas
uint32_t last_gt_on = 0;// delay mezi prichodem casu a requestem
uint32_t last_time_requuest = 0;//delay meyi 2 requestama na cas
int water_level = 0;
/*
   inicializuje komunikaci s fancontrollerem
*/
bool init_slave_communication() {
  delay(100);
  Slave.begin(115200);
  Slave.print("au");
  delay(1000);

  while (Slave.available() == 0) delay(1);
  char init_sequence[] = "ok";
  bool is_it_ok = true;

  for (int i = 0; i < 2; i++) {
    char ch = (char)Slave.read();
    if (init_sequence[i] != ch) {
      is_it_ok = false;
    }
    Serial.println(ch);
  }
  Serial.println(is_it_ok);
  return is_it_ok;
}

void check() {
  while (Slave.available() != 0) {
    Serial.print((char) Slave.read());
  }
  Serial.println(Slave.available());
}
/*
   params
   ch - char, ktery se ma prevest na int
   prevadi char na int
*/
int to_int(char ch) {
  char numbers[] = "0123456789";
  for (int i = 0; i < 10; i++) {
    if (numbers[i] == ch) return i;
  }
  return -1;
}
void change_fan_state(int index, int on) {
  Slave.print("sf");
  Slave.print(index);
  Slave.print(on);
}
/*
 * požádá o hladinu vody
 */
int get_water_level(){
  Slave.print("gw");
  delay(5);
  water_level = to_int(Slave.read())*10 + to_int(Slave.read());
  return water_level;
}

/*
 * zapne čerpadlo
 */
void pump_water(int index, int on){
  if(get_water_level()>0){
    Slave.print("sw");
    Slave.print(index-1);
    Slave.print(on);
  }
}
