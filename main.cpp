#include "mbed.h"

AnalogIn pot(PC_0);
InterruptIn botao(USER_BUTTON);

// Motor
DigitalOut EN_A(PA_10);
DigitalOut IN1A(PB_4);
DigitalOut IN2A(PB_5);

//Variável auxiliar
float f;

//Serial
Serial pc(USBTX, USBRX);

//printa dados do potênciometro na tela, ao apertar o botão
void print_pot(){
    pc.printf("\r duty cycle: %f % \n",f*100);
    pc.printf("\r tensao: %f V \n\n",f*12);
}

int main() {
    botao.fall(&print_pot);
    while(1) {

        //lê o potenciômetor
        f = pot.read();

        //Liga o Enable
        EN_A = 1;

        //Liga em uma direção
        IN1A = 0;
        IN2A = 1;

        wait_ms(60*f);

        //desliga
        IN1A = 0;
        IN2A = 0;

        wait_ms(60-(60*f));

        //Período total de acionamento: 60 ms

    }
}

