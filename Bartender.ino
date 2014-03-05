int motorPin1 = 2;
int motorPin2 = 3;
int motorPin3 = 4;
int motorPin4 = 5;
int delayTime = 3;


void setup()
{
	pinMode(motorPin1, OUTPUT);
	pinMode(motorPin2, OUTPUT);
	pinMode(motorPin3, OUTPUT);
	pinMode(motorPin4, OUTPUT);
}

void loop()
{
	digitalWrite(motorPin1, HIGH);
	digitalWrite(motorPin2, LOW);
	digitalWrite(motorPin3, HIGH);
	digitalWrite(motorPin4, LOW);
	delay(delayTime);
	
	digitalWrite(motorPin1, LOW);
	digitalWrite(motorPin2, HIGH);
	digitalWrite(motorPin3, HIGH);
	digitalWrite(motorPin4, LOW);
	delay(delayTime);
	
	digitalWrite(motorPin1, LOW);
	digitalWrite(motorPin2, HIGH);
	digitalWrite(motorPin3, LOW);
	digitalWrite(motorPin4, HIGH);
	delay(delayTime);
	
	digitalWrite(motorPin1, HIGH);
	digitalWrite(motorPin2, LOW);
	digitalWrite(motorPin3, LOW);
	digitalWrite(motorPin4, HIGH);
	delay(delayTime);
	
}