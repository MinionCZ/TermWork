#define water_pump1 PB12
#define water_pump2 PB13
#define water_pump3 PB14
#define water_pump4 PB15
#define sh PB4
#define clk PB5
#define data_out PB9
#define data_in PB8
const int water_pumps[] = {PA7, PA6, PA4, PA5};
bool water_levels[10];


void init_water() {

  for(int i = 0; i<4; i++){
    pinMode(water_pumps[i], OUTPUT);
    digitalWrite(water_pumps[i], LOW);
  }
  
  for (int i = 0; i < 10; i++) {
    water_levels[i] = false;
  }
  pinMode(sh, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(data_out, INPUT);
  pinMode(data_in, INPUT);
}


void change_watering_state(int index, bool on) {
  digitalWrite(water_pumps[index], on);
}
/*
   zjisti uroven vody v nadrzi
*/
int get_water_level() {
  
  
  return digitalRead(data_in) + digitalRead(data_out);
}
