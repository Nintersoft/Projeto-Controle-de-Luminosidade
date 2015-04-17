/*---------------------------------------------------------------------------------------------------------------------------
|   Programa: Controle de luminosidade e automação doméstica                                                                |
|   Organização e direitos autorais: Nintersoft                                                                             |
|   Site: http://www.nintersoft.ml                                                                                          |
|   Desenvolvedor: Mauro Mascarenhas de Araújo                                                                              |
|   Programa incluso na licença de código aberto Nintersoft (Veja nossa política no site)                                   |
|   Códigos fonte disponíveis em: http://www.github.com/Nintersoft                                                          |
|   Atualização: 15/04/2015                                                                                                 |
|   Data: 14/12/2014 (Finalizado)                                                                                           |
|   Versão: 1.1. 0                                                                                                          |
----------------------------------------------------------------------------------------------------------------------------*/

#include <SoftwareSerial.h>                                         //------------------- Inclui a biblioteca Software Serial

#define RxB         7                                               //---------- Define a porta de comunicação Rx com Arduino
#define TxB         6                                               //---------- Define a porta de comunicação Tx com Arduino

#define LED_LIG     0                                               //-- Define LED para verificar se o circuito foi acionado
#define LED_ATIV    13                                              //--------- Define saída para verificar o controle manual
#define NIVEL1      5                                               //----------- Define saídas para controle de luminosidade
#define NIVEL2      4                                               //----------- Define saídas para controle de luminosidade
#define NIVEL3      3                                               //----------- Define saídas para controle de luminosidade
#define NIVEL4      2                                               //----------- Define saídas para controle de luminosidade
#define NIVEL5      1                                               //----------- Define saídas para controle de luminosidade
#define SAIDA1      8                                               //---------------- Define saídas para ativação da Lâmpada
#define SAIDA2      9                                               //---------------- Define saídas para ativação da Lâmpada
#define SAIDA3     10                                               //---------------- Define saídas para ativação da Lâmpada
#define SAIDA4     11                                               //---------------- Define saídas para ativação da Lâmpada
#define SAIDA5     12                                               //---------------- Define saídas para ativação da Lâmpada

boolean manual;                                                     //-- Criação de variável para identicicar controle manual
boolean ativado;                                                    //--------- Criação de variável para verificar o circuito

SoftwareSerial bluetooth (RxB,TxB);                                 //------ Define os pinos de comunicação bluetooth-Arduino

void setup(){                                                       //--------- Função para configuração dos pinos do Arduino

  bluetooth.begin(57600);                                           //----------- Inicializa comunicação com Arduino-Bluetooh

  pinMode (LED_ATIV , OUTPUT);                                      //------------ Define o led de controle manual como saída
  pinMode (LED_LIG , OUTPUT);                                       //------- Define o LED de ativação do circuito como saída

  pinMode(NIVEL1 , OUTPUT);                                         //------------------- Define os pinos de nível como saida
  pinMode(NIVEL2 , OUTPUT);                                         //------------------- Define os pinos de nível como saida
  pinMode(NIVEL3 , OUTPUT);                                         //------------------- Define os pinos de nível como saida
  pinMode(NIVEL4 , OUTPUT);                                         //------------------- Define os pinos de nível como saida
  pinMode(NIVEL5 , OUTPUT);                                         //------------------- Define os pinos de nível como saida

  pinMode(SAIDA1 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA2 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA3 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA4 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  pinMode(SAIDA5 , OUTPUT);                                         //-------------------- Define os pinos de E/Ss como saída
  
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

      else if (letra == ']'){                                       //---- Verifica se há o caractere que desativa o circuito
        ativado = false;                                            //---- Desativa a variável que checa o estado do circuito
        digitalWrite(LED_LIG, LOW);                                 //---------- O LED informa que o circuito está desativado
        define();                                                   //--------- Reinicia o circuito com as condições iniciais
      }
      
      if (manual == false){                                         //---------- Verifica se o controle manal está desativado
        if (letra == '{'){                                          //----- Verifica se há o comando é para o controle manual
        manual = true;                                              //----------------- Identifica a variável como verdadeira
        digitalWrite(LED_ATIV , HIGH);                              //----- LED que mostra que o controle manual está ativado
        }
      }
      else if (manual == true){                                     //------------ Verifica se o controle manual está ativado 
     
        if (letra == '1'){                                          //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL1 , LOW);                               //------------ Ativa o nível 1 de corrente circuito (PNP)
          digitalWrite(NIVEL2 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL3 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL4 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL5 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }

        else if (letra == '2'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL2 , LOW);                               //------------ Ativa o nível 2 de corrente circuito (PNP)
          digitalWrite(NIVEL1 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL3 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL4 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL5 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }

        else if (letra == '3'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL1 , LOW);                               //------------ Ativa o nível 1 de corrente circuito (PNP)
          digitalWrite(NIVEL2 , LOW);                               //------------ Ativa o nível 2 de corrente circuito (PNP)
          digitalWrite(NIVEL3 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL4 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL5 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }

        else if (letra == '4'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL3 , LOW);                               //------------ Ativa o nível 3 de corrente circuito (PNP)
          digitalWrite(NIVEL1 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL2 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL4 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL5 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }

        else if (letra == '5'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL2, LOW);                                //------------ Ativa o nível 2 de corrente circuito (PNP)
          digitalWrite(NIVEL3 , LOW);                               //------------ Ativa o nível 3 de corrente circuito (PNP)
          digitalWrite(NIVEL1 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL4 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL5 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }

        else if (letra == '6'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL4, LOW);                                //------------ Ativa o nível 4 de corrente circuito (PNP)
          digitalWrite(NIVEL1 , LOW);                               //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL2 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL3 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL5 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }
        
        else if (letra == '7'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL3 , LOW);                               //------------ Ativa o nível 3 de corrente circuito (PNP)
          digitalWrite(NIVEL4 , LOW);                               //------------ Ativa o nível 4 de corrente circuito (PNP)
          digitalWrite(NIVEL1 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL2 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL5 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }

        else if (letra == '8'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL5 , LOW);                               //------------ Ativa o nível 5 de corrente circuito (PNP)
          digitalWrite(NIVEL1 , LOW);                               //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL2 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL3 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL4 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }
        
        else if (letra == '9'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL4 , LOW);                               //------------ Ativa o nível 4 de corrente circuito (PNP)
          digitalWrite(NIVEL5 , LOW);                               //------------ Ativa o nível 5 de corrente circuito (PNP)
          digitalWrite(NIVEL1 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL2 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
          digitalWrite(NIVEL3 , HIGH);                              //-- Desativa outros níveis de corrente no circuito (PNP)
        }

        else if (letra == '0'){                                     //-- Checa o caractere correspondente o nivel de corrente
          digitalWrite(NIVEL5 , LOW);                               //------------ Ativa o nível 5 de corrente circuito (PNP)
          digitalWrite(NIVEL1 , LOW);                               //------------ Ativa o nível 1 de corrente circuito (PNP)
          digitalWrite(NIVEL2 , LOW);                               //------------ Ativa o nível 2 de corrente circuito (PNP)
          digitalWrite(NIVEL3 , LOW);                               //------------ Ativa o nível 3 de corrente circuito (PNP)
          digitalWrite(NIVEL4 , LOW);                               //------------ Ativa o nível 4 de corrente circuito (PNP)
        }
        
        else if (letra == '}'){                                     //----- Verifica se há o comando é para o controle manual
            manual = false;                                         //---------------------- Identifica a variável como falsa
            digitalWrite(LED_ATIV , LOW);                           //------ LED mostra que o controle manual está desativado
            digitalWrite(NIVEL1, LOW);                              //------------------------- Ativa o nível mais alto (PNP)
            digitalWrite(NIVEL2, LOW);                              //------------------------- Ativa o nível mais alto (PNP)
            digitalWrite(NIVEL3, LOW);                              //------------------------- Ativa o nível mais alto (PNP)
            digitalWrite(NIVEL4, LOW);                              //------------------------- Ativa o nível mais alto (PNP)
            digitalWrite(NIVEL5, LOW);                              //------------------------- Ativa o nível mais alto (PNP)
         }      
       }

    }
    if (ativado == false){                                          //---------------- Verifica se o circuito está desativado
      if (letra == '['){                                            //-------------- Ativa o circuito - identifica a variável
        ativado = true;                                             //------------- Define a variável ativado como verdadeira
        digitalWrite(NIVEL5, LOW);                                  //------------------- Ativa o nível mais alto de corrente
        digitalWrite(NIVEL4, LOW);                                  //------------------- Ativa o nível mais alto de corrente
        digitalWrite(NIVEL3, LOW);                                  //------------------- Ativa o nível mais alto de corrente
        digitalWrite(NIVEL2, LOW);                                  //------------------- Ativa o nível mais alto de corrente
        digitalWrite(NIVEL1, LOW);                                  //------------------- Ativa o nível mais alto de corrente
        digitalWrite(LED_LIG, HIGH);                                //--- Ativa o LED informando que o circuito está acionado
      }
    }
  }
}                                                                   //----------------------------------------- Fim da função

void define(){                                                      //---------- Função para inicializar as saidas do Arduino
  digitalWrite(LED_LIG, LOW);                                       //---------- Mostra que o circuito ainda não foi acionado
  digitalWrite(LED_ATIV, LOW);                                      //--------- Mostra que o controle manual não está ativado
  digitalWrite(NIVEL1, HIGH);                                       //--------- Desativa o nível mais baixo de corrente (PNP)
  digitalWrite(NIVEL2, HIGH);                                       //- Desativa o segundo nível mais baixo de corrente (PNP)
  digitalWrite(NIVEL3, HIGH);                                       // Desativa o terceiro nível mais baixo de corrente (PNP)
  digitalWrite(NIVEL4, HIGH);                                       //-- Desativa o segundo nível mais alto de corrente (PNP)
  digitalWrite(NIVEL5, HIGH);                                       //---------------- Desativa o nível mais alto de corrente
  digitalWrite(SAIDA1, HIGH);                                       //----------------- Desativa a saída 1 do Arduino (Placa)
  digitalWrite(SAIDA2, HIGH);                                       //----------------- Desativa a saída 2 do Arduino (Placa)
  digitalWrite(SAIDA3, HIGH);                                       //----------------- Desativa a saída 3 do Arduino (Placa)
  digitalWrite(SAIDA4, HIGH);                                       //----------------- Desativa a saída 4 do Arduino (Placa)
  digitalWrite(SAIDA5, HIGH);                                       //----------------- Desativa a saída 5 do Arduino (Placa)
  manual = false;                                                   //------------------- Define a variável manual como falsa
  ativado = false;                                                  //------------------ Define a variável ativado como falsa
}                                                                   //----------------------------------------- Fim da função

void enviaEstado(){                                                 //------- Função que envia o estado da saídas do circuito
  delay(1000);                                                      //------ Atraso para o fispositivo remoto criar variáveis
  if (digitalRead(LED_LIG) == HIGH) bluetooth.write('+');           //------------------- Verifica se o circuito está ativado
  else bluetooth.write('0');                                        //---------------- Verifica se o circuito está desativado
  delay(100);                                                       //--------- Atraso para garantir a leitura da transmissão
  if (digitalRead(LED_ATIV) == HIGH) bluetooth.write('+');          //------------ Verifica se o controle manual está ativado
  else bluetooth.write('0');                                        //--------- Verifica se o controle manual está desativado
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
  for (int i = 1; i <= 20; i++){                                    //-- Loop que complementa a quantidade de caracteres (28)
    delay(50);                                                      //---------------------------------------- Atraso inicial
    bluetooth.write('0');                                           //------------ Envia caracteres de nível lógico igual à +
    delay(50);                                                      //------------------------- Complemento do atraso inicial
  }                                                                 //------------------------------------------- Fim do Loop
}                                                                   //----------------------------------------- Fim da função
