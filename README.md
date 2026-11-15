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

| Komponen      | Fungsi                                        |
|               |                                               |
| ESP32         | Mikrokontroler utama                          |
| MPU6050       | Membaca percepatan dan kecepatan sudut        |
| PIR Sensor    | Mendeteksi gerakan eksternal                  |
| 5 Servo Motor | Menghasilkan gerakan berdasarkan input sensor |

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

| Fitur | Input (Sensor)      | Output (Aktuator)| Perilaku                                                               |
|       |                     |                  |                                                                        |
| Roll  | Accel sumbu X, Y, Z | Servo 1 dan 2    | Servo bergerak berlawanan arah terhadap perubahan Roll.                |
| Pitch | Accel sumbu Y dan Z | Servo 3 dan 4    | Servo bergerak searah terhadap perubahan Pitch.                        |
| Yaw   | Gyroscope sumbu Z   | Servo 5          | Servo merespons perubahan kecepatan sudut Z dan kembali ke posisi awal.|
|Gerakan| PIR Sensor          | Servo 1-5        | Semua servo gerak ke +45 derajat 1,5 detik, dan kembali ke posisi awal.|


Pemetaan Pin ESP32

| Komponen    | Pin ESP32 |
|             |           |
| MPU6050 SDA | GPIO 21   |
| MPU6050 SCL | GPIO 22   |
| PIR OUT     | GPIO 13   |
| Servo 1     | GPIO 14   |
| Servo 2     | GPIO 27   |
| Servo 3     | GPIO 26   |
| Servo 4     | GPIO 25   |
| Servo 5     | GPIO 33   |


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
