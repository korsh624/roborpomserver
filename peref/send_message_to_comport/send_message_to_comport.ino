#define pinX    A2  // ось X джойстика
#define pinY    A3  // ось Y джойстика


void setup() {

Serial.begin(9600);


pinMode(pinX, INPUT);
pinMode(pinY, INPUT);

}

void loop() {


int X = analogRead(pinX);              // считываем значение оси Х
int Y = analogRead(pinY);              // считываем значение оси Y

 
Serial.print("j1");
Serial.print(X);
Serial.println(" ");
delay(10);             

}
