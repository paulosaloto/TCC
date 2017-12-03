void setup()
{
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(4, OUTPUT);
  SD.begin(4);

  pwmHead.begin();
  pwmBody.begin();

  pwmHead.setPWMFreq(333);  // Analog servos run at ~60 Hz updates
  pwmBody.setPWMFreq(333);  // Analog servos run at ~60 Hz updates
  
  for (int i=4; i<16; i++){
  pwmHead.setPWM(i, 0, 1000);  
  delay(50);
  }
  pwmHead.setPWM(0, 0, 2750);  

  memcpy(atualEtapa, expressoes[1], 6*sizeof(int));

  for(int i=0;i<6;i++){
    pwmBody.setPWM(i, 0, atualEtapa[i]); 
    //Serial.println(atualEtapa[i]);
  }

}

