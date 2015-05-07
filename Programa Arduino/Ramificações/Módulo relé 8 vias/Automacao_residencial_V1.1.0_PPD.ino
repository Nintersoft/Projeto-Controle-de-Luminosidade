/*---------------------------------------------------------------------------------------------------------------------------
|   Programa: Controle de luminosidade e automação doméstica                                                                |
|   Organização e direitos autorais: Nintersoft                                                                             |
|   Site: http://www.nintersoft.ml                                                                                          |
|   Desenvolvedor: Mauro Mascarenhas de Araújo                                                                              |
|   Programa incluso na licença de código aberto Nintersoft (Veja nossa política no site)                                   |
|   Códigos fonte disponíveis em: http://www.github.com/Nintersoft                                                          |
|   Atualização: 02/05/2015                                                                                                 |
|   Data: 14/12/2014 (Finalizado)                                                                                           |
|   Versão: 1.1.0 (Base)                                                                                                    |
----------------------------------------------------------------------------------------------------------------------------*/

#include <SoftwareSerial.h>                                         //------------------- Inclui a biblioteca Software Serial

#define RxB         1                                               //---------- Define a porta de comunicação Rx com Arduino
#define TxB         0                                               //---------- Define a porta de comunicação Tx com Arduino
 
#define SAIDA1      4                                               //------------------ Define saídas para ativação da Carga
#define SAIDA2      5                                               //------------------ Define saídas para ativação da Carga
#define SAIDA3      6                                               //------------------ Define saídas para ativação da Carga
#define SAIDA4      7                                               //------------------ Define saídas para ativação da Carga
#define SAIDA5      8                                               //------------------ Define saídas para ativação da Carga
#define SAIDA6      9                                               //------------------ Define saídas para ativação da Carga
#define SAIDA7     10                                               //------------------ Define saídas para ativação da Carga
#define SAIDA8     11                                               //------------------ Define saídas para ativação da Carga

boolean ativado;                                                    //--------- Criação de variável para verificar o circuito

SoftwareSerial bluetooth (RxB,TxB);                                 //------ Define os pinos de comunicação bluetooth-Arduino

void setup(){                                                       //--------- Função para configuração dos pinos do Arduino

  bluetooth.begin(57600);                                           //----------- Inicializa comunicação com Arduino-Bluetooh

  pinMode(SAIDA1 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA2 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA3 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA4 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA5 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA6 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA7 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA8 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  define();                                                         //--------------- Executa a primeira varredura no Arduino
}                                                                   //----------------------------------------- Fim da função

void loop(){                                                        //----- Função que contem o programa principal do Arduino

  char letra;                                                       // Criação da variável que receberá a letra por bluetooth

  if (bluetooth.available()){                                       //--- Verifica se há algum comando recebido por bluetooth
  
    letra = bluetooth.read();                                       //------------- Armazena o caractere recebido na variavel
    
    if (letra == '-') enviaEstado();                                //---- Envia o estado atual do aplicativo para o programa
  
    if (ativado == true){   

      if (letra == 'A')          digitalWrite(SAIDA1 , LOW);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'a')    digitalWrite(SAIDA1 , HIGH);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'B')     digitalWrite(SAIDA2 , LOW);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'b')    digitalWrite(SAIDA2 , HIGH);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'C')     digitalWrite(SAIDA3 , LOW);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'c')    digitalWrite(SAIDA3 , HIGH);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'D')     digitalWrite(SAIDA4 , LOW);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'd')    digitalWrite(SAIDA4 , HIGH);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'E')     digitalWrite(SAIDA5 , LOW);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'e')    digitalWrite(SAIDA5 , HIGH);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'F')     digitalWrite(SAIDA6 , LOW);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'f')    digitalWrite(SAIDA6 , HIGH);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'G')     digitalWrite(SAIDA7 , LOW);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'g')    digitalWrite(SAIDA7 , HIGH);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'H')    digitalWrite(SAIDA8 , LOW);         //----- Compara o caractere para acionar a saida desejada
      else if (letra == 'h')    digitalWrite(SAIDA8 , HIGH);        //----- Compara o caractere para acionar a saida desejada
      else if (letra == '[')    define();                           //--------------------------- Define os estados iniciais;
      
    }

    if (ativado == false){                                          //---------------- Verifica se o circuito está desativado
      if (letra == '['){                                            //-------------- Ativa o circuito - identifica a variável
        ativado = true;                                             //------------- Define a variável ativado como verdadeira
      }
    }
  }
}                                                                   //----------------------------------------- Fim da função

void define(){                                                      //---------- Função para inicializar as saidas do Arduino
  digitalWrite(SAIDA1, HIGH);                                       //----------------- Desativa a saída 1 do Arduino (Placa)
  digitalWrite(SAIDA2, HIGH);                                       //----------------- Desativa a saída 2 do Arduino (Placa)
  digitalWrite(SAIDA3, HIGH);                                       //----------------- Desativa a saída 3 do Arduino (Placa)
  digitalWrite(SAIDA4, HIGH);                                       //----------------- Desativa a saída 4 do Arduino (Placa)
  digitalWrite(SAIDA5, HIGH);                                       //----------------- Desativa a saída 5 do Arduino (Placa)
  digitalWrite(SAIDA6, HIGH);                                       //----------------- Desativa a saída 6 do Arduino (Placa)
  digitalWrite(SAIDA7, HIGH);                                       //----------------- Desativa a saída 7 do Arduino (Placa)
  digitalWrite(SAIDA8, HIGH);                                       //----------------- Desativa a saída 8 do Arduino (Placa)
  ativado = false;                                                  //--- Define a variável de circuito ativado igual à falso
}                                                                   //----------------------------------------- Fim da função

void enviaEstado(){                                                 //------- Função que envia o estado da saídas do circuito
  delay(1000);                                                      //------ Atraso para o fispositivo remoto criar variáveis
  if (ativado == true) bluetooth.write('+');                        //------------------- Verifica se o circuito está ativado
  else bluetooth.write('0');                                        //---------------- Verifica se o circuito está desativado
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  bluetooth.write('0');                                             //----------- Controle manual indisponível neste programa
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  bluetooth.write('0');                                             //------------------ Envia o nivel de luminosidade máximo
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(SAIDA1) == LOW) bluetooth.write('+');             //---------- Envia o estado da saída número 1 como ligada
  else bluetooth.write('0');                                        //------- Envia o estado da saída número 1 como desligada
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(SAIDA2) == LOW) bluetooth.write('+');             //---------- Envia o estado da saída número 2 como ligada
  else bluetooth.write('0');                                        //------- Envia o estado da saída número 2 como desligada
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(SAIDA3) == LOW) bluetooth.write('+');             //---------- Envia o estado da saída número 3 como ligada 
  else bluetooth.write('0');                                        //------- Envia o estado da saída número 3 como desligada
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(SAIDA4) == LOW) bluetooth.write('+');             //---------- Envia o estado da saída número 4 como ligada 
  else bluetooth.write('0');                                        //------- Envia o estado da saída número 4 como desligada
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(SAIDA5) == LOW) bluetooth.write('+');             //---------- Envia o estado da saída número 5 como ligada 
  else bluetooth.write('0');                                        //------- Envia o estado da saída número 5 como desligada
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(SAIDA6) == LOW) bluetooth.write('+');             //---------- Envia o estado da saída número 6 como ligada 
  else bluetooth.write('0');                                        //------- Envia o estado da saída número 6 como desligada
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(SAIDA7) == LOW) bluetooth.write('+');             //---------- Envia o estado da saída número 7 como ligada 
  else bluetooth.write('0');                                        //------- Envia o estado da saída número 7 como desligada
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(SAIDA8) == LOW) bluetooth.write('+');             //---------- Envia o estado da saída número 8 como ligada 
  else bluetooth.write('0');                                        //------- Envia o estado da saída número 8 como desligada
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  for (int i = 1; i <= 17; i++){                                    //-- Loop que complementa a quantidade de caracteres (28)
    delay(50);                                                      //---------------------------------------- Atraso inicial
    bluetooth.write('0');                                           //------------ Envia caracteres de nível lógico igual à +
    delay(50);                                                      //------------------------- Complemento do atraso inicial
  }                                                                 //------------------------------------------- Fim do Loop
}                                                                   //----------------------------------------- Fim da função
