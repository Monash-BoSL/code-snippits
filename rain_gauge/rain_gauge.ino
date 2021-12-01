#include <avr/power.h>
#include <LowPower.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define HALL_SIG A0 //singal pin for hall effect
#define HALL_PWR 6 //power pin for hall effect

#define TRIG 50//change in analog read needed for trigger

#define SAMPLE_TIME 4// number of seconds to measure rain sensor in one sample

//millis timer variable 
extern volatile unsigned long timer0_millis;


void setup() {
	Serial.begin(9600);
	Serial.println("Begin");
	pinMode(HALL_SIG, INPUT);
	pinMode(HALL_PWR, OUTPUT);
	digitalWrite(HALL_PWR, LOW);
	
	Serial.flush();
}


void loop() {
	uint32_t edges = count_edges(SAMPLE_TIME);
	Serial.print(edges);
	Serial.print(F(" flips over "));
	Serial.print(SAMPLE_TIME);
	Serial.print(F("s. Frequency: "));
	Serial.print((float)edges/((float)SAMPLE_TIME));
	Serial.println(F(" flips/s"));
	Serial.flush();
}


uint32_t count_edges(uint32_t time_s){
	uint32_t time_ms = 1000*time_s;
	uint32_t edge_count = 0;
	uint32_t tik = millis();
	uint32_t sdel = 160;
	while(millis()-tik < time_ms){
		digitalWrite(HALL_PWR, HIGH);
		delayMicroseconds(100);
		int16_t mag = analogRead(HALL_SIG);
		digitalWrite(HALL_PWR, LOW);
		edge_count += is_edge(mag);
		
		sdel = MIN(sdel, time_ms - (millis() - tik));
		
		xdelay(sdel);
	}
	return edge_count;
}


int16_t l_mag = -1;
int8_t rising = -1;
uint8_t is_edge(int16_t mag){
	if(l_mag == -1){
		l_mag = mag;
		return 0;
	}else{
		int16_t change = mag - l_mag;
		if((change > 0) == rising){
			l_mag = mag;
			return 0;
		}else{
			if (abs(change) > TRIG){
				l_mag = mag;
				rising = !rising;
				return 1;
			}
		}
	}
	return 0;
}

//like delay but lower power and more dodgy//
void xdelay(uint32_t tmz){
	uint32_t tmzslc = tmz/64;
	//64 chosen as ballance between power savings and time spent in full clock mode
	clock_prescale_set(clock_div_64);
		delay(tmzslc);
	clock_prescale_set(clock_div_1);
	
	cli();
	timer0_millis += 63*tmzslc;	
	sei();
	
	delay(tmz-64*tmzslc);
}
