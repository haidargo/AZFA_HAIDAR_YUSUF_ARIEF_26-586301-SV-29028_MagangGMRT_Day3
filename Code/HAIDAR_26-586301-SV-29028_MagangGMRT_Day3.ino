/*
 * NAMA LENGKAP : [AZFA HAIDAR YUSUF ARIEF]
 * NIM          : [26/586301/SV/29028]
 * PROYEK       : Kontrol 5 Servo dengan Sensor IMU & PIR (Magang GMRT Day 3)
 *
 * ASUMSI SIMULASI WOKWI:
 * 1. Menggunakan sensor MPU6050 sebagai pengganti BNO055 karena keterbatasan
 *    komponen di Wokwi (sama-sama menggunakan komunikasi I2C pin 21 & 22).
 * 2. Input sudut Roll, Pitch, dan Yaw diambil dari slider Gyroscope (deg/s)
 *    pada komponen MPU6050 di Wokwi agar mudah digeser sesuai derajatnya.
 * 3. Saat PIR mendeteksi gerakan, semua servo bergerak ke +45 derajat (1750 us).
 */

#include <Wire.h>
#include <ESP32Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Membuat objek untuk sensor dan 5 servo
Adafruit_MPU6050 imu;
Servo servo1, servo2, servo3, servo4, servo5;

// Menentukan nomor pin ESP32 (menghindari pin 21 & 22 untuk I2C)
int pinServo1 = 14;
int pinServo2 = 27;
int pinServo3 = 26;
int pinServo4 = 25;
int pinServo5 = 33;
int pinPIR    = 13;

// Variabel untuk menyimpan nilai sudut (-90 sampai +90 derajat)
float roll = 0;
float pitch = 0;
float yaw = 0;
float yawLama = 0;
bool yawSedangPutar = false;

void setup() {
  Serial.begin(115200);
  pinMode(pinPIR, INPUT);

  // Cek apakah sensor IMU terhubung
  if (!imu.begin()) {
    Serial.println("Sensor IMU tidak terdeteksi!");
    while (1); // Berhenti jika sensor error
  }

  // Hubungkan setiap servo ke pin-nya (batas PWM: 1000 us s.d 2000 us)
  servo1.attach(pinServo1, 1000, 2000);
  servo2.attach(pinServo2, 1000, 2000);
  servo3.attach(pinServo3, 1000, 2000);
  servo4.attach(pinServo4, 1000, 2000);
  servo5.attach(pinServo5, 1000, 2000);

  // Posisi awal semua servo tegak lurus (0 derajat = 1500 us)
  servo1.writeMicroseconds(1500);
  servo2.writeMicroseconds(1500);
  servo3.writeMicroseconds(1500);
  servo4.writeMicroseconds(1500);
  servo5.writeMicroseconds(1500);
  delay(1000);
}

void loop() {
  //CEK SENSOR PIR (GERAKAN EKSTERNAL)
  if (digitalRead(pinPIR) == HIGH) {
    Serial.println("PIR Aktif, Semua servo ke +45 derajat (1750 us)");
    
    // Semua servo bergerak bersamaan ke 1750 us (+45 derajat)
    servo1.writeMicroseconds(1750);
    servo2.writeMicroseconds(1750);
    servo3.writeMicroseconds(1750);
    servo4.writeMicroseconds(1750);
    servo5.writeMicroseconds(1750);
    delay(1500); // Tahan 1,5 detik

    // Kembali serentak ke posisi awal 1500 us (0 derajat)
    servo1.writeMicroseconds(1500);
    servo2.writeMicroseconds(1500);
    servo3.writeMicroseconds(1500);
    servo4.writeMicroseconds(1500);
    servo5.writeMicroseconds(1500);
    delay(1000);
    return; 
  }

  //BACA DATA SENSOR IMU
  sensors_event_t a, g, temp;
  imu.getEvent(&a, &g, &temp);

  // Ubah bacaan radian dari sensor menjadi derajat (dikali 57.3)
  roll  = g.gyro.x * 57.3;
  pitch = g.gyro.y * 57.3;
  yaw   = g.gyro.z * 57.3;

  // Batasi sudut agar maksimal hanya -90 sampai +90 derajat
  if (roll > 90)  roll = 90;
  if (roll < -90) roll = -90;
  if (pitch > 90)  pitch = 90;
  if (pitch < -90) pitch = -90;
  if (yaw > 90)  yaw = 90;
  if (yaw < -90) yaw = -90;

  //HITUNG NILAI PWM UNTUK SETIAP SERVO
  // Rumus dasar: 0 derajat = 1500 us. Setiap 1 derajat = 5.55 us
  // Roll berlawanan arah, Pakai tanda MINUS (-roll)
  int pwm1 = 1500 + (-roll * 5.55);
  int pwm2 = 1500 + (-roll * 5.55);

  // Pitch searah, Pakai tanda PLUS (+pitch)
  int pwm3 = 1500 + (pitch * 5.55);
  int pwm4 = 1500 + (pitch * 5.55);

  // Gerakkan Servo 1, 2, 3, dan 4
  servo1.writeMicroseconds(pwm1);
  servo2.writeMicroseconds(pwm2);
  servo3.writeMicroseconds(pwm3);
  servo4.writeMicroseconds(pwm4);

  //LOGIKA YAW (SERVO 5)
  // Cek apakah nilai yaw berubah lebih dari 1 derajat dari sebelumnya
  if (abs(yaw - yawLama) > 1 && abs(yaw) > 1) {
    yawSedangPutar = true;
    int pwm5 = 1500 + (yaw * 5.55);
    servo5.writeMicroseconds(pwm5);
  } 
  else if (yawSedangPutar == true) {
    // Jika yaw berhenti berputar, diam 1 detik lalu kembali ke 1500 us (0 derajat)
    Serial.println("Yaw berhenti, Tunggu 1 detik...");
    delay(1000);
    servo5.writeMicroseconds(1500);
    Serial.println("Servo 5 kembali ke 0 derajat (1500 us).");
    yawSedangPutar = false;
  }
  yawLama = yaw;

  //TAMPILKAN KE SERIAL MONITOR
  Serial.print("Roll: "); Serial.print(roll);
  Serial.print(" | Pitch: "); Serial.print(pitch);
  Serial.print(" | Yaw: "); Serial.print(yaw);
  Serial.print(" ||| PWM S1: "); Serial.print(pwm1);
  Serial.print(" | S2: "); Serial.print(pwm2);
  Serial.print(" | S3: "); Serial.print(pwm3);
  Serial.print(" | S4: "); Serial.println(pwm4);


  delay(200);
}