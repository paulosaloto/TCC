int sequencia (char modo)
{
  char arduinoMsg = '1';
  Serial.println(arduinoMsg); // MENSAGEM 1 - confirma que pode gravar
  String nome;
  delay(10);
  getName(nome); // MENSAGEM 2 - nome da sequência
  nome.trim();
  if (modo == 'w')
  {
    while(SD.exists(nome))
    {
      Serial.println('2'); // MENSAGEM 3 - nome da sequência formatado / já existe
      Serial.flush();
      getName(nome); // MENSAGEM 3.1 - novo nome da sequência
    }  
    myFile = SD.open(nome, FILE_WRITE);
  }
  else
  {
    while(!SD.exists(nome))
    {
      Serial.println('2'); // MENSAGEM 3 - nome da sequência formatado / já existe
      Serial.flush();
      getName(nome); // MENSAGEM 3.1 - novo nome da sequência
    }  
    myFile = SD.open(nome);
  }
  delay(20);
  Serial.println(nome); // MENSAGEM 3 - nome da sequência formatado
  Serial.flush();
  if (myFile) return(1);
  else return(0);
}


int getName(String &fileName)
{
  while(!Serial.available()) {;}
  fileName = Serial.readStringUntil('\n');
  Serial.flush();
  fileName.trim();
  if (fileName.length() > 8) fileName.remove(8);
  fileName.concat(".csv");
  char nome[fileName.length()];
  fileName.toCharArray(nome,fileName.length()+1);
  return 0;
}

