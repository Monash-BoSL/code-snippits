//A3 A1 D13 D12 D11 D10 D8 D7 D4 D3
//green
void setup(){
	Serial.begin(9600);
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
}

const int delay_ = 2000;
void loop(){

	set_A(1);
	set_B(-1);
	delay(delay_);
	set_A(1);
	set_B(0);
	delay(delay_);
	set_A(1);
	set_B(1);
	delay(delay_);
	set_A(0);
	set_B(1);
	delay(delay_);
	set_A(-1);
	set_B(1);
	delay(delay_);
	set_A(-1);
	set_B(0);
	delay(delay_);
	set_A(-1);
	set_B(-1);
	delay(delay_);
	set_A(0);
	set_B(-1);
	delay(delay_);
	
	
    Serial.println("step");
	
	
}

void set_A(int dir){
	if(dir == 0){
		digitalWrite(3, LOW);
		digitalWrite(7, LOW);
	}
	if(dir == 1){
		digitalWrite(3, HIGH);
		digitalWrite(7, LOW);
	}
	if(dir == -1){
		digitalWrite(3, LOW);
		digitalWrite(7, HIGH);
	}
}

void set_B(int dir){
	if(dir == 0){
		digitalWrite(4, LOW);
		digitalWrite(8, LOW);
	}
	if(dir == 1){
		digitalWrite(4, HIGH);
		digitalWrite(8, LOW);
	}
	if(dir == -1){
		digitalWrite(4, LOW);
		digitalWrite(8, HIGH);
	}
}