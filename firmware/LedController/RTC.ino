/*
   založí rtc
*/
HardwareTimer timer(1);
#define one_second 1000000
volatile uint8_t hours = 14;
volatile uint8_t minutes = 59;
volatile uint8_t seconds = 0;
volatile uint8_t day_in_week = 0;
void init_rtc() {
  timer.pause();
  timer.setPeriod(one_second);
  timer.attachCompare1Interrupt(add_second);
  timer.refresh();
  timer.resume();
}
void add_second() {
  seconds++;
  if(seconds == 60){
    seconds = 0;
    minutes++;
    if(minutes == 60){
      minutes = 0;
      hours++;
      if(hours == 24){
        hours = 0;
        day_in_week++;
        if(day_in_week == 8){
          day_in_week = 1;
          watered = false;
        }
      }
    }
  }
}
/*
   vraci aktualni hodinu
*/
uint8_t get_hour() {
  return hours;
}
/*
   vraci aktualni minutu
*/
uint8_t get_minute() {
  return minutes;
}

/*
   vraci aktualni sekundu
*/
uint8_t get_second() {
  return seconds;
}
void print_time(){
  Serial.print(hours);
  Serial.print(":");
   Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  
}
