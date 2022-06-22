/*
 * File:   teclado.c
 * Author: :'c
 *
 * Created on 19 de junio de 2022, 03:14 PM
 */

#include "config.h"
#include "teclado.h"

//Variables

int intentos=0;
int verifi=0;
int y1,y2,y3,y4; // digitos de la clave
int clave;
int Estado=0; // variable para registrar la cuenta de los números ingresados
int password=7337;



//Procedimientos

//RCO verde
//RC1 Rojo
void prender_led_verde(){
    RC0 = 1;
}
void apagar_led_verde(){
    RC0 = 0;
}
void prender_led_rojo(){
    RC1 = 1;
}
void apagar_led_rojo(){
    RC1 = 0;
}
void pulsar_boton(){
        RC2 = 1;
        __delay_ms(100);
        RC2 = 0;
        __delay_ms(100);
}
void Alarma(){
    for(int a=0; a<=4; a++){
        Lcd_Clear();
        Lcd_Set_Cursor(1,6);
        Lcd_Write_String("Caja");
        Lcd_Set_Cursor(2,4);
        Lcd_Write_String("Bloqueada");
                    
        RC2 = 1;
        __delay_ms(1000);
        RC2 = 0;
        __delay_ms(1000);
    }
}
void ver_clave(char buffer1) {
    
    Lcd_Set_Cursor(2,1);
    Lcd_Write_String(buffer1);           
    __delay_ms(1000); 
    Lcd_Set_Cursor(2,8);
    Lcd_Write_String("****");
   
}

void mover (){
  for(int c=0; c<15; c++){
    __delay_ms(350);
    Lcd_Shift_Left();
  }
    
  for(int c=0; c<15; c++){
    __delay_ms(350);
    Lcd_Shift_Right();
  }
}


//main

int main()
{ 
  
  char buffer1[20];

  TRISD = 0x00; //salidas que van al LCD  
  TRISC = 0x00; //salidas que van al led y buzzer
  TRISB = 0xF0; // 4MSB entradas, 4LSB salidas
  PORTD = 0; 
  PORTC = 0;
  PORTB = 0;
  
  Lcd_Init();
  
  Lcd_Clear();
 
  Lcd_Set_Cursor(1,1);
  Lcd_Write_String("Cerradura Eelectronica");
  mover();
  
 
  Lcd_Clear();
  Lcd_Set_Cursor(1,2);
  Lcd_Write_String("Ingrese Clave:");
  Lcd_Set_Cursor(2,8);
  Lcd_Write_String("____");
  
      
  prender_led_rojo();
  
  
  while(intentos<3 && verifi==0){   
  
      int tecla = Leer_tecla();
      __delay_ms(100);
      
      if(tecla !=100 && tecla != 35 && tecla !=42 ){
          
          //clave=0;
          
            if (Estado==0) {
                pulsar_boton();
                y1=tecla;
                clave=y1;
                Lcd_Set_Cursor(2,8);
                Lcd_Write_String("*");
                __delay_ms(500);
                Estado++;
                
                sprintf(buffer1,"Clave: %i",clave);
            }
            else if (Estado==1){
                pulsar_boton();
                y2=tecla;
                clave= 10*y1+tecla; //para las decenas  

                Lcd_Set_Cursor(2,9);
                Lcd_Write_String("*");
                __delay_ms(500);
                Estado++;
                
                sprintf(buffer1,"Clave: %i",clave);
            }
            else if (Estado==2) {
                pulsar_boton();
                y3=tecla;
                clave=y1*100+y2*10+tecla; //para las centenas

                Lcd_Set_Cursor(2,10);
                Lcd_Write_String("*");
                __delay_ms(500);
                Estado++;
                
                sprintf(buffer1,"Clave: %i",clave);
            }
            else if (Estado==3) {
                pulsar_boton();
                y4=tecla;
                clave=y1*1000+y2*100+y3*10+y4; //para las centenas

                Lcd_Set_Cursor(2,11);
                Lcd_Write_String("*");
                __delay_ms(500);
                Estado++;
                
                sprintf(buffer1,"Clave: %i",clave);
            }
      }
        if(tecla==35){
            pulsar_boton();
            ver_clave(buffer1);
        }   
        if(tecla==42){
            
            pulsar_boton();
            
            if(clave==password){

                verifi=1;

                apagar_led_rojo();
                Lcd_Clear();
                Lcd_Set_Cursor(1,6);
                Lcd_Write_String("Clave");
                Lcd_Set_Cursor(2,5);
                Lcd_Write_String("Correcta");
                prender_led_verde();
                __delay_ms(7000);
            }
            else{
                intentos++;
                Estado=0;
                Lcd_Clear();
                Lcd_Set_Cursor(1,6);
                Lcd_Write_String("Clave");
                Lcd_Set_Cursor(2,4);
                Lcd_Write_String("Incorrecta");
                __delay_ms(1000);
                
                if(intentos<3){
                    
                    Lcd_Clear();
                    Lcd_Set_Cursor(1,2);
                    Lcd_Write_String("Ingrese Clave:");
                    Lcd_Set_Cursor(2,8);
                    Lcd_Write_String("____");
                }
                else{  
                    Alarma(); 
                }
            }    
        }
        
  }
    
  
  return 0;
}

