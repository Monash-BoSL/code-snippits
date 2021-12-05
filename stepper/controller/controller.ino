//A3 A1 D13 D12 D11 D10 D8 D7 D4 D3
//green
void setup(){
	Serial.begin(9600);
	pinMode(A3, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(7, OUTPUT);

	digitalWrite(A3, HIGH);
	digitalWrite(13, HIGH);
	digitalWrite(7, LOW);
	digitalWrite(8,HIGH);
	
}

const int delay_ = 2000;
void loop(){
	digitalWrite(A1, LOW);
	delay(delay_);
	digitalWrite(A1, HIGH);
	delay(delay_);
	
    Serial.println("step");
	
	
}

