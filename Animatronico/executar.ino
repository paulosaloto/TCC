int executar()
{
  bool x = true;
  uint8_t proximaExpressao = 0;
  unsigned int tempoFinal = 0;
  int boca = 2700;
  unsigned long contiauge = millis();
  unsigned long tempo = 0;
  unsigned long cronometro = millis(); // COMEÇA A CONTAR O TEMPO PARA MANTER A SINCRONIA COM O ÁUDIO
  unsigned int tempoAnterior=0;
  Serial.print("size ");
  Serial.println(myFile.size());
  Serial.print("available ");
  Serial.println(myFile.available());
  unsigned int filePosition = 0;
  for (int n=0; n<12; n++) {
    unsigned int valore = 1500*bitRead(1755,n);
    pwmHead.setPWM(4+n, 0, valore);  
  }
  while (myFile.available()) 
  {
    
    while(x)
    {

      x = leituraArquivo(tempo, boca, proximaExpressao, tempoFinal);

      if(tempoAnterior == tempo) return(0);

      cronometro = millis() - cronometro;
      if ((tempo-tempoAnterior) > cronometro) delay(tempo-(tempoAnterior+cronometro));
      cronometro = millis();
      if (myFile.position() == filePosition) return(0);  
      else filePosition = myFile.position();
      tempoAnterior= tempo;

    }
    
    int posicaoInicial = tabelaPosicao[atualExpressao][proximaExpressao];
    int posicaoFinal;
  
    if (proximaExpressao!=5) posicaoFinal=tabelaPosicao[atualExpressao][proximaExpressao+1];
    else posicaoFinal=tabelaPosicao[proximaExpressao+1][0];
    if (posicaoInicial == 59) posicaoFinal = 62;  // ULTIMA POSIÇÃO DA TABELA

    //memcpy(atualEtapa, proximaEtapa, 6*sizeof(int));
    int etapas = posicaoFinal - posicaoInicial;
    int frames = (tempoFinal - tempo)/5;                    //para frame de 50ms
    //frames = 200;                    //para frame de 50ms
    int framesPorEtapa = frames/etapas; //etapas de acordo com os frames
    framesPorEtapa = (5+framesPorEtapa)/10;
    frames = (5+frames)/10;                  //arredondadinho



    for (int i=0; i<etapas; i++) {

      for (int n=0; n<12; n++) {
        unsigned int valore = 1000*bitRead(olhos[posicaoInicial+i],n);
        pwmHead.setPWM(4+n, 0, valore);  
      }
      
      memcpy(proximaEtapa, expressoes[posicaoInicial+i], 6*sizeof(int));
      for (int j=1; j<=framesPorEtapa; j++) {
        for (int k=0; k<6; k++){
  
          int valorJunta = atualEtapa[k]+j*(proximaEtapa[k]-atualEtapa[k])/(framesPorEtapa);
          //if (k==4) valorJunta = valorJunta + random(-100,100);
          if (valorJunta > valorJuntaMax[k]) valorJunta = valorJuntaMax[k];
          if (valorJunta < valorJuntaMin[k]) valorJunta = valorJuntaMin[k];
  
          pwmBody.setPWM(numServo[k], 0, valorJunta);    
        }


        x = !leituraArquivo(tempo, boca, proximaExpressao, tempoFinal);

        if(tempoAnterior == tempo) return(0);

        cronometro = millis() - cronometro;
        if ((tempo-tempoAnterior) > cronometro) delay(tempo-(tempoAnterior+cronometro));
        cronometro = millis();
        tempoAnterior= tempo;
      }
      
      memcpy(atualEtapa, proximaEtapa, 6*sizeof(int));
      atualExpressao = proximaExpressao;
    }
    if((millis()-cronometro)>10) 
    {
      x = true;
      Serial.print("alerta cronometro: ");
      Serial.println(cronometro);
      Serial.print("momento do alerta: ");
      Serial.println(millis()-contiauge);
    }

  }
    return(0);
   
}



bool leituraArquivo(unsigned long &tempo, int &boca, uint8_t &proximaExpressao, unsigned int &tempoFinal)
{
  String buffer = myFile.readStringUntil('\n');
  while(buffer[0]<49 || buffer[0]>57) buffer = myFile.readStringUntil('\n');
  //Serial.println(buffer);
  int indiceT = buffer.indexOf(';');
  tempo = buffer.substring(0,indiceT).toInt();
  int indiceB = buffer.indexOf(';',indiceT+1);
  boca = buffer.substring(indiceT+1,indiceB).toInt();
  pwmHead.setPWM(0, 0, boca);
  if (random(30) > 27) pwmBody.setPWM(4, 0, random(1900,2100));
  if (buffer.lastIndexOf(';') != indiceB)
  {
    proximaExpressao = buffer.substring(indiceB+1,indiceB+2).toInt();
    tempoFinal = 90+ buffer.substring(indiceB+3).toInt();
    
    return(false);
  } 
  else return(true);
}


