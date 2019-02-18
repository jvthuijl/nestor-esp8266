const int LDR = A0;
const int BUTTON = 4;
const int RED = 15;
const int GREEN = 12;
const int BLUE = 13;

const int ON = 25;
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
    int lightValue = analogRead(LDR);
    
    Serial.print("LDR: ");
    Serial.println(lightValue);
    Serial.print("BUTTON: ");
    Serial.println(digitalRead(BUTTON));

    counter++;
    
    if (counter > 2) {
      counter = 0;
    }

    if (counter == 0) {
      analogWrite(RED, ON);
      analogWrite(GREEN, OFF);
      analogWrite(BLUE, OFF);      
    } else if (counter == 1) {
      analogWrite(RED, OFF);
      analogWrite(GREEN, ON);
      analogWrite(BLUE, OFF);            
    } else if (counter == 2) {
      analogWrite(RED, OFF);
      analogWrite(GREEN, OFF);
      analogWrite(BLUE, ON);                  
    }

    int wait = lightValue + 25;

    delay(wait);
}
