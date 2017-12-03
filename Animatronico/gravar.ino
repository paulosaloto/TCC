int gravar() //MENSAGEM 0 - manda gravar
{

      {
        Serial.println('3'); // MENSAGEM 4 - Cartão pronto para gravação
        Serial.flush();
        String buffer;
        do
        {   
          buffer = Serial.readStringUntil('\n'); // MENSAGEM 5 - envio do arquivo
          buffer.trim();
         
          if(buffer == "FIM") break;  //MENSAGEM 5.1 - fim do envio
          else myFile.println(buffer);
        } while (buffer != "FIM");
        
        myFile.close();
        //Serial.println("Gravação completada com sucesso.");
      }
      return 0;
}

