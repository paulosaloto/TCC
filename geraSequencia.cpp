#include <stdio.h>
#include <stdlib.h>
#include <iostream>       // std::cout, std::endl
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <sstream>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <fcntl.h>
#include <termios.h>

#include <unistd.h>
#include <stdint.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[])
{
    long lSize;
    char * buffer;
    size_t result;
    int i=0;
    char gravar[] = "gravar\n";
    printf("Abrindo o arquivo...\n");
    //std::ifstream dataFile("espectral.csv");             //Abrindo o arduino

    ///////////////////////////////////////////////////////////////////////////////
    int alturaVocal=2750;
    double emoTempo=0;
    double emoProb[5]={0, 0, 0, 0, 0};
    int emoClasse=0;
    double numeros[6];
    ofstream sequencia;
    //if (argv[1]) sequencia.open (argv[1]);
    sequencia.open ("sequencia.csv");
    ifstream espectral("/home/paulo/opensmile-2.3.0/arquivos/resultadoAlt.csv");
    ifstream emo("/home/paulo/opensmile-2.3.0/arquivos/resultadoEmo.csv");

    if(espectral.is_open())
    {
        if(emo.is_open()){
            emo>>emoTempo;
            for(i=0;i<5;i++){
                emo>>emoProb[i];    
            }
            emoProb[1] = emoProb[1];
            emoProb[3] = emoProb[3];
            emoClasse = distance(emoProb,max_element(emoProb,emoProb+5));
            
        }
        else 
        {
            printf("Não conseguiu abrir o arquivo de emoções :(\n");
            return(0);
        }
        
        while(!espectral.eof())
        {

            for(int j=0;j<6;j++)
            {
                espectral>>numeros[j];
            }
            if (numeros[5]<0.090) alturaVocal = 2750;
            else alturaVocal = 2750 - 250*distance(numeros,max_element(numeros+1,numeros+5));
            int tempoMs = 1000*numeros[0];

            if(numeros[0] > emoTempo)
            {
                emo>>emoTempo;       
                if(numeros[0] < emoTempo)
                {              
                    int emoTempoMs = 1000*emoTempo;
                    sequencia << tempoMs << ";"   << alturaVocal << ";" << emoClasse << ";" << emoTempoMs << endl;
                    //emo>>emoClasse; 

                    for(i=0;i<5;i++){
                        emo>>emoProb[i];    
                    }
                    //emoProb[1] = emoProb[1]-.13;
                    //emoProb[2] = emoProb[2]-.19;
                    emoClasse = distance(emoProb,max_element(emoProb,emoProb+5));
                }
                else sequencia << tempoMs << ";"   << alturaVocal  << ";" << endl;
            }
            else sequencia << tempoMs << ";"   << alturaVocal  << ";" << endl;
        }
        espectral.close();
        emo.close();
        sequencia.close();
        printf("Sequência gerada com sucesso!\n");
    }
    else {
            printf("Não conseguiu abrir o arquivo de alturas vocais :(\n");
            return(0);

    }


    //FILE *arduino;
    struct termios toptions;
    int arduino = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    std::this_thread::sleep_for (std::chrono::seconds(3));  //Espera 5 segundos para inicializar a serial
     ////////////////////////////////////////////////////////////////
    /* get current serial port settings */
      tcgetattr(arduino, &toptions);
      /* set 9600 baud both ways */
      cfsetispeed(&toptions, B9600);
      cfsetospeed(&toptions, B9600);
      /* 8 bits, no parity, no stop bits */
      toptions.c_cflag &= ~PARENB;
      toptions.c_cflag &= ~CSTOPB;
      toptions.c_cflag &= ~CSIZE;
      toptions.c_cflag |= CS8;
      /* Canonical mode */
      toptions.c_lflag |= ICANON;
      /* commit the serial port settings */
      tcsetattr(arduino, TCSANOW, &toptions);
/////////////////////////////////////////////////////////////////


    printf("Conectou ao Arduino...\n");
    write (arduino,gravar,strlen(gravar)); // MENSAGEM 0 - manda gravar
    char arduinoMsg[64] = "temp xxxxxxxxxx";
    int n = read (arduino,arduinoMsg,64); // MENSAGEM 1 - confirma que pode gravar
    arduinoMsg[n] = 0;

       if(arduinoMsg[0] == '1')
    {
        cout << "Arduino está pronto para gravar" << endl;
    
        char nomedoarquivo[11];//strcpy(arduinoMsg,"\0"); 
        if (argv[1]) {
            strncpy(nomedoarquivo, argv[1], strlen(argv[1])-4); 
            strcat(nomedoarquivo,"\n");
        }
        else strcpy(nomedoarquivo, "Default\n");
        write (arduino,nomedoarquivo,strlen(nomedoarquivo)); /// MENSAGEM 2 - nome da sequência
        n = read (arduino,arduinoMsg,64);   // MENSAGEM 3 - nome da sequência formatado / já existe
        arduinoMsg[n] = 0;
        //std::this_thread::sleep_for (std::chrono::seconds(1));  //Espera 5 segundos para inicializar a serial

        while(arduinoMsg[0] == '2')
        {
            printf("\nSequência já existe. Escolha outro nome\n");
            cin >> arduinoMsg; 
            strcat(arduinoMsg, "\n"); 
            write (arduino,arduinoMsg,64); /// MENSAGEM 3.1 - novo nome da sequência
            n = read (arduino,arduinoMsg,64);
            arduinoMsg[n] = 0;
        }
        std::this_thread::sleep_for (std::chrono::seconds(1));  //Espera 5 segundos para inicializar a serial

        cout << "Sequência será gravada no arquivo " << arduinoMsg << endl;
        n = read (arduino,arduinoMsg,64); // MENSAGEM 4 -  Cartão pronto para gravação
        arduinoMsg[n] = 0;
        //std::this_thread::sleep_for (std::chrono::seconds(1));  //Espera 5 segundos para inicializar a serial

        if(arduinoMsg[0] != '3')
        {
            printf("deu ruim no cartão %s\n",arduinoMsg);
            close(arduino);
            return(0);
        }
        else 
        {
            cout << "SD pronto para gravação." << endl;
            
            ifstream sequenciaEnvio("sequencia.csv");             //Abrindo o arduino

            for (string buffer; getline(sequenciaEnvio, buffer);)
            {
                buffer.append("\n");
                char *buffer2 = &buffer[0];
                write (arduino,buffer2,buffer.size()); // MENSAGEM 5 - envio do arquivo

                printf("\rForam enviadas %d linhas.",1+i++);
                fflush(stdout);
            }
            strcpy(arduinoMsg, "FIM\n");
            write (arduino,arduinoMsg,strlen(arduinoMsg)); //MENSAGEM 5.1 - fim do envio
            
            sequenciaEnvio.close();
            printf("\nGravação concluida. Deseja executar a sequência? (s/n)\n");    
        }
        char resposta;
        cin >> resposta;
        if (resposta == 's')
        {
            printf("\nEXECUTANDOOOOO\n");    
            char executar[] = "executar\n";
            write (arduino,executar,strlen(executar)); // MENSAGEM 0 - manda gravar
            int n = read (arduino,arduinoMsg,64); // MENSAGEM 1 - confirma que pode gravar
            arduinoMsg[n] = 0;

            if(arduinoMsg[0] == '1')
            {
                write (arduino,nomedoarquivo,strlen(nomedoarquivo)); /// MENSAGEM 2 - nome da sequência
            }
        }
        else close(arduino);
    }
    else close(arduino);

    ///////////////////////////////////////////////////////////////////////////////
    

    return(0);
}