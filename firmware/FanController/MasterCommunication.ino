#define Master Serial1
/*
   zahajeni komunikace s masterem
*/
bool init_communication() {
  Master.begin(115200);
  while (Master.available() == 0) {
    delay(1);
  }
  bool is_ok = true;
  char init_sequence[] = "au";
  for (int i = 0; i < 2; i++) {
    if (init_sequence[i] != (char) Master.read()) {
      is_ok = false;
    }
  }
  delay(100);
  Master.print("ok");

  return is_ok;
}


void write_shit() {
  Master.print("ahoj");
}

/*
   kontrola jestli neprisel nejaky prikaz os mastera
*/
void check_master() {
  if (Master.available() == 0) return;
  int last_value = 0;
  while(Master.available()>last_value){
    last_value = Master.available();
    delay(2);
  }
  char serial_readed = Master.read();
  if ( serial_readed == 'g' ) {
    get_commands(Master.read());
  } else {
    set_commands(Master.read());
  }
}

/*
   vyhodnocuje get commands
   params
   command - typ prikazu
*/
void get_commands(char command) {
  switch (command) {
    case 'w':
    get_water_level_master();
      break;
    default:
      break;
  }
}
/*
   vyhodnocuje set commands
   params
   command - typ prikazu
*/

void set_commands(char command) {
  switch (command) {
    case 'f'://fans
      master_command_fan();
      break;
    case 'w':
      master_command_water_pump();
      break;
    default:
      break;
  }
}
/*
 * parsuje informace o vetracich od mastera
 */
void master_command_fan() {
  int index = to_int(Master.read());
  int on = to_int(Master.read());
  set_fan_power(index, on == 1);
}
void master_command_water_pump(){
  int index = to_int(Master.read());
  int on = to_int(Master.read());
  change_watering_state(index, on == 1);
}
/*
 * odesle masterovi water level v nadrzi
 */
void get_water_level_master(){
  int water_level = get_water_level();
  if(water_level<10){
    Master.print("0");
    Master.print(water_level);
  }else{
    Master.print(water_level);
  }
}


int to_int(char ch) {
  char number[] = "0123456789";
  for (int i = 0; i < 10; i++) {
    if (number[i] == ch) return i;
  }
  return -1;
}
