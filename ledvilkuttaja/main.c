/*
 * main.c
 *
 * Created: 8/28/2024 9:08:01 AM
 *  Author: kv
 */ 

#include <xc.h>
#define F_CPU 16000000UL  // 16 MHz kide

#include <util/delay.h>

#define LED_PIN PD6        // LED kytketty porttiin PD6
#define BUTTON_PIN PD5     // Painonappi kytketty porttiin PD5

void init() {
	// Aseta LED_PIN lähtötilaan
	DDRD |= (1 << LED_PIN);
	
	// Aseta BUTTON_PIN tulotilaan
	DDRD &= ~(1 << BUTTON_PIN);
	
	// Aseta pull-up vastus BUTTON_PIN:lle
	PORTD |= (1 << BUTTON_PIN);
}

int main() {
	// Alustetaan portit ja pinnit
	init();
	
	// Alustetaan tila muuttujaan, joka pitää kirjaa LED:n tilasta
	uint8_t led_on = 0;

	while (1) {
		// Tarkista, onko painonappia painettu (BUTTON_PIN tilassa LOW)
		if (!(PIND & (1 << BUTTON_PIN))) {
			// LED vilkkuu kun painiketta painetaan
			led_on = !led_on;  // Vaihda LED:n tila
			
			// Aseta LED_PIN tilaan HIGH tai LOW
			if (led_on) {
				PORTD |= (1 << LED_PIN);  // Kytke LED päälle
				} else {
				PORTD &= ~(1 << LED_PIN); // Kytke LED pois päältä
			}
			
			_delay_ms(250);  // Odota 0.25 sekuntia (250 ms)
			} else {
			// Jos painiketta ei paineta, pidä LED pois päältä
			PORTD &= ~(1 << LED_PIN);  // Varmista, että LED on sammutettu
		}
	}

	return 0;
}