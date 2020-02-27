






void setup() {
  // put your setup code here, to run once:
init_communication();
init_fans();
init_water();
}

void loop() {
  
  // put your main code here, to run repeatedly:
check_master();
delay(1);
 
}
