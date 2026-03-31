#include <avr/io.h>
#include <avr/iotn85.h>
#include <util/delay.h>
#include <utility>
using namespace std;
///yayyy beginnning the codeeeee

#define VREF 5.0 ///the Vcc source reference



#define SWITCH PB0  //PB0 - Switch activator (5v out) pin 5
#define PUSH PB1    //PB1 - Trigger response (5v in) pin 6
#define LED PB2     //PB2 - Led status (out 5v) pin 7 ADC1
#define CAP PB3     //PB3 - Capactior bank reader (5v in) pin 2 ADC3
#define BAT PB4     //PB4 - Battery reader (5v in) pin 3 ADC2

void ADC_init() {
    ADMUX = (1 << REFS0); // Vcc as reference
    ADCSRA = (1 << ADEN)  // enable ADC
           | (1 << ADPS2)
           | (1 << ADPS1)
           | (1 << ADPS0); // prescaler 128
}

#define CAP_LIM 920
//Cap divider: 90kΩ + 10kΩ, VCC = 5V, full = 50V → ADC = 1023
#define BAT_LIM 507
// 12V LiPo: full = 12.6V, cutoff = 9.9V
// Divider: 30kΩ + 10kΩ, VCC = 5V
// 9.9V → ADC = (9.9 * 10/40) / 5 * 1023 = 507


//example ig
float readADC(uint8_t channel)
{
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // select channel

    ADCSRA |= (1 << ADSC); // start conversion

    while (ADCSRA & (1 << ADSC)); // wait until finished
    
    return (ADC * VREF) / 1023.0;

}

float read12(uint8_t channel)
{
    return 4*readADC(channel);
}

float read50(uint8_t channel)
{
    return 10*readADC(channel);
}

//to do
class Railgun {
bool bat;
bool cap;

//from status to led - a function controlling the led after receiveing an integer
void led_on()
{
    PORTB |=  (1 << LED);
}

void led_off()
{
    PORTB &=  ~(1 << LED);
    PORTB &= PORTB;
}
pair <float,bool> get_status()//function that gets all parameters returns float for bat and bool for cap readiness
{
    //battery check - return a percentage like variable with the battey's charge
    float cap_voltage = read50(3);
    float bat_voltage = read12(2);
    if(cap_voltage >= CAP_LIM && bat_voltage >= BAT_LIM)
    {
        led_on();
    }
    else led_off();
    //capacitor check - return a percentage like variable with the capacitor bank charge
}


//fire function that turns on and off the sdr switch

//main loop for putting it all togheter
};