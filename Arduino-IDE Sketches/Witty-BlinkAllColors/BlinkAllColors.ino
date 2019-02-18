const int LDR = A0;
const int BUTTON = 4;
const int RED = 15;
const int GREEN = 12;
const int BLUE = 13;

const int WAITTIME = 1000; // 1 second
const int ON = 100;
const int OFF = 0;
int counter = 0;  

void setup() 
{
    Serial.begin(9600);
 
    pinMode(LDR, INPUT);
    pinMode(BUTTON, INPUT);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(BLUE, OUTPUT);
}
 
void loop()
{
    analogWrite(RED, ON);
    delay(WAITTIME);
    analogWrite(RED, OFF);
    delay(WAITTIME);
    analogWrite(GREEN, ON);
    delay(WAITTIME);
    analogWrite(GREEN, OFF);
    delay(WAITTIME);
    analogWrite(BLUE, ON);
    delay(WAITTIME);
    analogWrite(BLUE, OFF);
    delay(WAITTIME);
}
