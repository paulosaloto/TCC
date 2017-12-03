#! /bin/sh

if [ -e arquivos/resultadoEmo.csv ] 
then
	sudo rm -f arquivos/resultadoEmo.csv 
fi
if [ -e arquivos/resultadoAlt.csv ] 
then
	sudo rm -f arquivos/resultadoAlt.csv 
fi

echo -n "Selecione o arquivo de áudio: "
read arquivoAudio

if [ -e $arquivoAudio ]
then
    echo "Arquivo encontrado."
else
    echo "Arquivo não existe."
	exit
fi

sudo ./SMILExtract -C config/Classificador.conf -I $arquivoAudio
cd ~/Dropbox/TCC/Programas/
sudo ./Sequencia $arquivoAudio
cd ~/opensmile-2.3.0/
sudo aplay $arquivoAudio


