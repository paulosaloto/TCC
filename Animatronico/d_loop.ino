void loop()
{
  if (Serial.available())
  {
    String comando = Serial.readStringUntil('\n');
    if (comando == "gravar")
    {
      if(sequencia('w'))
        gravar();
    }
    else if (comando == "executar")
    {
      if (sequencia('r'))
      {
        unsigned long contage = millis();
        executar();
        Serial.print("Tempo total de execução: ");
        Serial.println(millis() - contage);
      }
      memcpy(atualEtapa, expressoes[1], 6*sizeof(int));
      for(int i=0;i<6;i++){
        pwmBody.setPWM(i, 0, atualEtapa[i]); 
      } 
    }
    
    else Serial.println(comando);
  }
    if (random(900000) > 899998) pwmBody.setPWM(4, 0, random(1800,2200));
}

