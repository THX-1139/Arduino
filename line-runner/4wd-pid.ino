// ===== ПІНИ ДАТЧИКА ЛІНІЇ =====
const int lineSensor = 2;   // Цифровий датчик лінії (LOW = чорна лінія)

// ===== ПІНИ МОТОРІВ =====
// Лівий передній
const int LF1 = 3;
const int LF2 = 4;

// Правий передній
const int RF1 = 5;
const int RF2 = 6;

// Лівий задній
const int LB1 = 7;
const int LB2 = 8;

// Правий задній
const int RB1 = 9;
const int RB2 = 10;

// ===== ПАРАМЕТРИ PID =====
float Kp = 40.0;   // Пропорційний коефіцієнт
float Ki = 0.0;    // Інтегральний (можна залишити 0)
float Kd = 25.0;   // Диференційний

float error = 0;
float lastError = 0;
float integral = 0;
float derivative = 0;

int baseSpeed = 150;  // Базова швидкість моторів (0–255)

void setup() {
  pinMode(lineSensor, INPUT);

  pinMode(LF1, OUTPUT);
  pinMode(LF2, OUTPUT);
  pinMode(RF1, OUTPUT);
  pinMode(RF2, OUTPUT);
  pinMode(LB1, OUTPUT);
  pinMode(LB2, OUTPUT);
  pinMode(RB1, OUTPUT);
  pinMode(RB2, OUTPUT);
}

void loop() {

  // ===== Зчитуємо датчик =====
  int sensor = digitalRead(lineSensor);

  // Якщо датчик бачить чорну лінію → помилка = 0
  // Якщо білий фон → помилка = 1
  error = (sensor == HIGH) ? 1 : 0;

  // ===== PID РОЗРАХУНОК =====
  integral += error;
  derivative = error - lastError;

  float output = Kp * error + Ki * integral + Kd * derivative;

  lastError = error;

  // ===== РОЗРАХУНОК ШВИДКОСТІ МОТОРІВ =====
  int leftSpeed = baseSpeed - output;
  int rightSpeed = baseSpeed + output;

  // Обмеження швидкості в межах 0–255
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // ===== РУХ МОТОРІВ =====
  driveMotors(leftSpeed, rightSpeed);
}

// ===== ФУНКЦІЯ КЕРУВАННЯ МОТОРАМИ =====
void driveMotors(int left, int right) {

  // Ліві мотори вперед
  analogWrite(LF1, left);
  digitalWrite(LF2, LOW);
  analogWrite(LB1, left);
  digitalWrite(LB2, LOW);

  // Праві мотори вперед
  analogWrite(RF1, right);
  digitalWrite(RF2, LOW);
  analogWrite(RB1, right);
  digitalWrite(RB2, LOW);
}
