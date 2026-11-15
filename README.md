# AZFA_HAIDAR_YUSUF_ARIEF_26-586301-SV-29028_MagangGMRT_Day3
Proyek simulasi kontrol 5 servo menggunakan ESP32, sensor IMU MPU6050, dan PIR untuk Magang GMRT Day 3.


Kontrol 5 Servo dengan Sensor IMU & PIR
Magang GMRT Day 3

 1. Profile

- Nama Lengkap: Azfa Haidar Yusuf Arief
- NIM: 26/586301/SV/29028
- Universitas: Universitas Gadjah Mada
- Program Studi: Teknologi Survei dan Pemetaan Dasar

2. Description

Proyek ini merupakan simulasi sistem kontrol lima servo motor menggunakan mikrokontroler ESP32 dengan sensor IMU MPU6050 dan sensor PIR.

Sistem dirancang untuk mendeteksi perubahan orientasi pada tiga sumbu, yaitu Roll, Pitch, dan Yaw. Selain itu, sensor PIR digunakan untuk mendeteksi gerakan eksternal.

Ketika terjadi perubahan orientasi, servo akan bergerak mengikuti nilai sudut yang dibaca oleh sensor. Ketika sensor PIR mendeteksi gerakan, seluruh servo akan bergerak menuju posisi +45 derajat selama 1,5 detik, kemudian kembali ke posisi awal.


Komponen yang Digunakan

| No. | Komponen | Jumlah | Fungsi |
|:---:|---|:---:|---|
| 1 | ESP32 | 1 | Mikrokontroler utama untuk memproses data sensor dan mengontrol servo. |
| 2 | MPU6050 | 1 | Membaca percepatan dan kecepatan sudut untuk mendeteksi orientasi. |
| 3 | PIR Sensor | 1 | Mendeteksi gerakan eksternal. |
| 4 | Servo Motor | 5 | Menghasilkan gerakan berdasarkan input sensor. |
Protokol Komunikasi

- I2C: Komunikasi ESP32 dengan MPU6050 menggunakan SDA (GPIO 21) dan SCL (GPIO 22).
- GPIO Digital: Membaca sinyal HIGH/LOW dari sensor PIR pada GPIO 13.
- PWM: Mengatur posisi kelima servo menggunakan sinyal PWM.
- Serial: Menampilkan hasil pembacaan sensor dan nilai PWM melalui Serial Monitor dengan baud rate 115200.


Asumsi Simulasi

1. MPU6050 digunakan sebagai pengganti BNO055 karena keterbatasan komponen pada Wokwi.
2. Nilai Roll dan Pitch dihitung menggunakan data accelerometer.
3. Nilai Yaw menggunakan data kecepatan sudut sumbu Z dari gyroscope.
4. Nilai sudut dibatasi pada rentang -90 hingga +90 derajat.
5. Posisi awal servo adalah 0 derajat dengan PWM 1500 µs.
6. Ketika PIR mendeteksi gerakan, seluruh servo bergerak ke +45 derajat dengan PWM 1750 µs.


3. Feature Table

| Fitur | Input (Sensor) | Output (Aktuator) | Perilaku |
|:---|:---|:---|:---|
| **Roll** | Accelerometer (X, Y, Z) | Servo 1 dan Servo 2 | Servo bergerak berlawanan arah mengikuti perubahan sudut Roll. |
| **Pitch** | Accelerometer (Y, Z) | Servo 3 dan Servo 4 | Servo bergerak searah mengikuti perubahan sudut Pitch. |
| **Yaw** | Gyroscope (Z) | Servo 5 | Servo merespons perubahan kecepatan rotasi sumbu Z. Ketika rotasi berhenti, servo kembali ke posisi awal setelah 1 detik. |
| **Gerakan Eksternal** | Sensor PIR | Servo 1–5 | Ketika gerakan terdeteksi, seluruh servo bergerak ke +45° (1750 µs) selama 1,5 detik, kemudian kembali ke posisi awal (1500 µs). |


Pemetaan Pin ESP32

| Komponen | Pin Komponen | Pin ESP32 | Fungsi |
|---|---|---|---|
| MPU6050 | SDA | GPIO 21 | Komunikasi I2C |
| MPU6050 | SCL | GPIO 22 | Komunikasi I2C |
| MPU6050 | VCC | 3V3 | Catu daya |
| MPU6050 | GND | GND | Ground |
| PIR Sensor | OUT | GPIO 13 | Input digital |
| PIR Sensor | VCC | 5V | Catu daya |
| PIR Sensor | GND | GND | Ground |
| Servo 1 | Signal | GPIO 14 | Output PWM |
| Servo 2 | Signal | GPIO 27 | Output PWM |
| Servo 3 | Signal | GPIO 26 | Output PWM |
| Servo 4 | Signal | GPIO 25 | Output PWM |
| Servo 5 | Signal | GPIO 33 | Output PWM |

Catatan:
- MPU6050 menggunakan komunikasi I2C.
- Servo dikendalikan menggunakan sinyal PWM.
- PIR menggunakan input digital.
- Seluruh komponen menggunakan GND bersama.


4. How to Run

A. Link Simulasi Wokwi

https://wokwi.com/projects/480689290038443009


B. Library yang Dibutuhkan

1. Wire
2. ESP32Servo
3. Adafruit MPU6050
4. Adafruit Unified Sensor


C. Cara Menjalankan Simulasi

1. Buka link simulasi Wokwi.
2. Klik tombol Start Simulation.
3. Pastikan sensor MPU6050 dan PIR terhubung dengan benar.
4. Buka Serial Monitor.
5. Atur baud rate menjadi 115200.
6. Ubah nilai input sensor melalui slider pada komponen MPU6050.
7. Amati perubahan nilai Roll, Pitch, Yaw, dan PWM servo pada Serial Monitor.


D. Cara Pengujian

Kasus Uji 1 – Perubahan Orientasi
1. Jalankan simulasi Wokwi.
2. Ubah input Roll dan Pitch menggunakan slider MPU6050.
3. Amati respons Servo 1, 2, 3, dan 4.
4. Ubah input Gyroscope sumbu Z untuk menguji respons Servo 5.
5. Amati perubahan nilai sensor dan PWM pada Serial Monitor.

Kasus Uji 2 – Deteksi Gerakan Eksternal
1. Jalankan simulasi Wokwi.
2. Aktifkan sensor PIR melalui input gerakan.
3. Amati perubahan posisi kelima servo menuju +45 derajat.
4. Setelah 1,5 detik, servo akan kembali ke posisi awal.
5. Amati pesan status pada Serial Monitor.
