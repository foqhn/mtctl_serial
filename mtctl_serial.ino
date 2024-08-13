//Control 2 DC motor using hardware serial communication

#define ENA 5
#define IN1 4
#define IN2 0
#define ENB 15
#define IN3 2
#define IN4 14
int maxSpeed = 255;



void motor(int speedA_pct, int speedB_pct) {
  int speedA = speedA_pct * maxSpeed / 100;
  int speedB = speedB_pct * maxSpeed / 100;
  if (speedA > maxSpeed) speedA = maxSpeed;
  if (speedB > maxSpeed) speedB = maxSpeed;
  if (speedA > 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    speedA = -speedA;
  }
  if (speedB > 0) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    speedB = -speedB;
  }
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB); 
}

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Type speed A and B in percentage");
  Serial.println("Example: 100 100");
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  motor(0, 0);


}

void loop() { // run over and over
  if (Serial.available() > 0) {
    int speedA = Serial.parseInt();
    int speedB = Serial.parseInt();
    motor(speedA, speedB);
    Serial.print("Speed A: ");
    Serial.print(speedA);
    Serial.print(" Speed B: ");
    Serial.println(speedB);
  }
}







