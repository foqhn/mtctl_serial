#define ENA 5  // モータAの速度制御ピン（PWMピン）
#define IN1 4  // モータAの方向制御ピン1
#define IN2 0  // モータAの方向制御ピン2
#define ENB 15 // モータBの速度制御ピン（PWMピン）
#define IN3 2  // モータBの方向制御ピン1
#define IN4 14 // モータBの方向制御ピン2

int maxSpeed = 255; // PWMの最大値（速度の最大値）

// モータの速度を制御する関数
// speedA_pct: モータAの速度（パーセンテージで指定）
// speedB_pct: モータBの速度（パーセンテージで指定）
void motor(int speedA_pct, int speedB_pct) {
  int speedA = speedA_pct * maxSpeed / 100; // モータAの速度をPWM値に変換
  int speedB = speedB_pct * maxSpeed / 100; // モータBの速度をPWM値に変換

  // 速度が最大値を超えた場合、最大値に制限
  if (speedA > maxSpeed) speedA = maxSpeed;
  if (speedB > maxSpeed) speedB = maxSpeed;

  // モータAの回転方向の制御
  if (speedA > 0) {
    digitalWrite(IN1, HIGH); // モータAを前進方向に設定
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);  // モータAを後進方向に設定
    digitalWrite(IN2, HIGH);
    speedA = -speedA;  // 負の速度を正のPWM値に変換
  }

  // モータBの回転方向の制御
  if (speedB > 0) {
    digitalWrite(IN3, HIGH); // モータBを前進方向に設定
    digitalWrite(IN4, LOW);
  } else {
    digitalWrite(IN3, LOW);  // モータBを後進方向に設定
    digitalWrite(IN4, HIGH);
    speedB = -speedB;  // 負の速度を正のPWM値に変換
  }

  // PWM信号をモータAとモータBに出力して速度を制御
  analogWrite(ENA, speedA);
  analogWrite(ENB, speedB); 
}

void setup() {
  // シリアル通信を開始し、ポートが開くのを待つ
  Serial.begin(115200);
  while (!Serial) {
    ; // ネイティブUSBポートが必要な場合、シリアルポートが接続されるのを待つ
  }
  Serial.println("Type speed A and B in percentage");
  Serial.println("Example: 100 100");

  // モータの制御ピンを出力モードに設定
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // 初期状態としてモータを停止
  motor(0, 0);
}

void loop() { // 繰り返し実行されるループ
  // シリアル通信でデータが受信された場合
  if (Serial.available() > 0) {
    int speedA = Serial.parseInt(); // 受信したモータAの速度（パーセンテージ）を取得
    int speedB = Serial.parseInt(); // 受信したモータBの速度（パーセンテージ）を取得

    // モータの速度を設定
    motor(speedA, speedB);

    // 現在の速度をシリアルモニタに出力
    Serial.print("Speed A: ");
    Serial.print(speedA);
    Serial.print(" Speed B: ");
    Serial.println(speedB);
  }
}
