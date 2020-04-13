#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "LCD_Files/HD44780.h"
#include "ADC_Files/adc.h"
#include "HCSR04_Files/HCSR04.h"

#define LED_RED PD2
#define LED_GREEN PD1

//volatile int dlugosc = 0;
int pom1 = 0; // Odleg³osc z ostatniego poamiaru
uint8_t crc = 0; //Flaga kontrolna (1 -> wyje¿d¿a; 2 -> wje¿d¿a; 0-> postój)
int licznik = 0; //licznik odleg³oœci
char stan;
uint8_t flag1 = 0; //flaga do diod

char konwersja[4]; // z ULI na stringa do d³ugoœci
char konwersja_D[4];	// z doubla na stringa
uint8_t flag = 0;  	// flaga do czyszczenia LCD

uint16_t drzwi = 300; // próg kontrolny okreœlaj¹cy czy drzwi s¹ otwarte czy zamkniête

uint8_t count = 0; // licznik do odleglosci

////////////////////////////////
uint16_t odl_parkowania = 20; // odleg³oœc uznawana za odleglosc parkowania
////////////////////////////////

void set_DDRx(void); // ustawienie wejsc i wyjsc
void set_diodes(void); // ustawianie diod
void set_diodes1(void); // ustawianie diod
void Distance_Measure( void ); // pomiar odleg³oœci
void Triger_Run( void ); // start triger pin

void main( void ){

	set_DDRx();
	//TCCR1B |= (1 << CS10);

	LCD_Initalize();
	ADC_Initalize();
	_delay_ms(400);
	LCD_Clear();

	while(1){
		drzwi = ADC_Measure(); // Pomiar czy drzwi otwarte czy zamkniête

		//_delay_ms(2000); Jeszcze nie, ale w produkcji bêdzie sobie takie opóŸnienie

		if(drzwi > 200){ // Drzwi zamkniête
			PORTD |= (1<<LED_RED);
			PORTD |= (1<<LED_GREEN);
			if(flag == 1){
				LCD_Clear();
				flag = 0;
			}

			LCD_GoTo(0,1);
			LCD_WriteText("zamk");

			sprintf(konwersja, "%i", licznik);
			LCD_GoTo(6, 1);
			LCD_WriteText(konwersja);
		}
		else if(drzwi < 200){ //Drzwi otwarte

					Distance_Measure(); // Pomiar odleg³oœci
					_delay_ms(50);

					flag = 1; // wyczysc LCD gdy drzwi siê zamkn¹

					sprintf(konwersja, "%i", licznik);
					LCD_Clear();
					LCD_GoTo(0,0);
					LCD_WriteText(konwersja);

					sprintf(konwersja_D, "%i", pom1);
					LCD_GoTo(6, 0);
					LCD_WriteText(konwersja_D);

					//sprintf(konwersja_D, "%i", stan);
					LCD_GoTo(0, 1);
					LCD_WriteText(stan);


					//set_diodes(); //zapalanie i gaszenie diod bez sprawdzania czy wjezdza czy wyjezdza
					set_diodes1(); //diody ON/OFF w zale¿noœci od wje¿d¿a/wyje¿d¿a
				}
		}
}

void set_diodes(void){

	if(licznik < odl_parkowania){ // Zielona dioda
		PORTD |= (1<<LED_RED);
		PORTD &= ~(1<<LED_GREEN);
	}
	else if(licznik < odl_parkowania + 1 || licznik < odl_parkowania + 2 || licznik < odl_parkowania + 3){
		// wygaszanie stanów przejœciowych przy wahaniu siê odleg³oœci parkowania
	}
	else if(licznik > odl_parkowania){ // Czerwona dioda
		PORTD |= (1<<LED_GREEN);
		PORTD &= ~(1<<LED_RED);
	}
}
void set_diodes1(void){

	switch(crc){
	case 2:  //wje¿d¿anie
		if(licznik <= odl_parkowania){ // Je¿eli przekroczymy odleg³osc parkowania GREEN_ON
			PORTD |= (1<<LED_RED);
			PORTD &= ~(1<<LED_GREEN);
		}
		else if(licznik < odl_parkowania + 1 || licznik < odl_parkowania + 2 || licznik < odl_parkowania + 3){
			// wygaszanie przejœcia przy wahaniu siê pomiaru odleg³oœci
		}
		else if(licznik > odl_parkowania){ // Je¿eli jesteœmy dalej ni¿ odl. parkowania RED_ON
			PORTD |= (1<<LED_GREEN);
			PORTD &= ~(1<<LED_RED);
		}
		break;
	case 1: //wyje¿d¿anie
		if(licznik > odl_parkowania){
			PORTD |= (1<<LED_RED);
			PORTD |= (1<<LED_GREEN);
		}
		break;
	case 0: //postój
		break;
	}

}
void set_DDRx(void){
	DDRD |= (1<<Trig);
	DDRD &= ~(1<<Echo);
	DDRD |= (1<<LED_RED);
	DDRD |= (1<<LED_GREEN);
}
void Distance_Measure( void ){

	Triger_Run();

	while(!(PIND & (1<<Echo))) // Dopóki Echo nic nie zwraca
		{
			 licznik = 0;
		}
		_delay_us(1);
	while(PIND & (1<<Echo)) // Jak echo coœ zwróci zacznij odliczanie "odleg³oœci"
		{
			licznik += 1;
			_delay_us(10);
		}

		if(licznik - pom1 > 50 || pom1 - licznik > 50){
				// jak pomiar zbytnio odbiega to go wywal
			stan = "wywalony";
		}
		else{
			if(licznik > pom1){
				stan = "wyjezdza";
				crc = 1; // wyje¿d¿a
			}
			else if(licznik < pom1){
				stan = "wjezdza";
				crc = 2; // wje¿d¿a
			}
			else{
				stan = "postoj";
				crc = 0; // stoi
			}

			flag1 = flag1 + 1;
			if(flag1 == 4){
				pom1 = licznik;
				flag1 = 0;
			}
		}
}


void Triger_Run( void ){
	PORTD |= (1<<Trig);
	_delay_us(12);
	PORTD &= ~(1<<Trig);
}

