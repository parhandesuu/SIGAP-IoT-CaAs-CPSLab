# SIGAP-IoT-CaAs-CPSLab

# 🔥 SIGAP - Smart Integrated Gas & Heat Protection

## 📌 Ringkasan Proyek

SIGAP adalah sistem monitoring kebocoran gas dan suhu ruangan berbasis ESP32 yang terintegrasi dengan platform Blynk IoT. Sistem ini mampu mendeteksi kadar gas berbahaya (menggunakan sensor MQ2) serta suhu ruangan (menggunakan DHT11) secara real-time.
Data sensor ditampilkan secara lokal melalui LCD 16x2 dan indikator LED, serta dikirim ke aplikasi Blynk untuk monitoring jarak jauh melalui smartphone.
Sistem ini dirancang sebagai solusi early warning system untuk meningkatkan keamanan ruangan dari risiko kebocoran gas dan suhu berlebih.

---

## ⚙️ Komponen yang Digunakan

1. ESP32-S3-DevkitC-1 
2. Breadboard
3. DHT11 sensor temperatur
4. trafic light (green, yellow, red)
5. MQ2 sensor gas
6. LCD 16 kali 2 l2c
7. Buzzer Passive
8. expansion board IO Shield ESP32-S3-DevkitC-1 
9. Blynk real time

---

## 🔌 Desain Skematik & Pin Mapping

### 📍 Konfigurasi Pin

| Komponen        | GPIO |
|----------------|------|
| MQ2 (Analog)   | 2    |
| DHT11          | 6    |
| Buzzer         | 1    |
| LED Merah      | 7    |
| LED Kuning     | 21   |
| LED Hijau      | 20   |
| LCD SDA        | 8    |
| LCD SCL        | 9    |

### 🧠 Logika Sistem

**Level Gas:**
- < 1500 → Normal
- 1500 – 2499 → Detected
- ≥ 2500 → Danger

**Level Suhu:**
- < 31°C → Normal
- 31 – 34.9°C → Warm
- ≥ 35°C → Danger

### 🚦 Indikator

| Status | LED | Buzzer | LCD |
|--------|-----|--------|------|
| Normal | Hijau | OFF | GAS/TEMP NORMAL |
| Sedang | Kuning | OFF | DETECTED GAS / TEMPERATURE WARM |
| Bahaya | Merah | ON | DANGER GAS HIGH / DANGER TEMP HIGH |

Diagram rangkaian dapat dilihat pada folder `/diagram`.

---

## 🌐 Integrasi IoT (Blynk)

Platform yang digunakan: Blynk IoT

### Virtual Pin:
- V0 → Suhu (°C)
- V1 → Nilai Gas (ADC)

Fitur:
- Monitoring suhu real-time
- Monitoring kadar gas
- Indikator kondisi sistem

---

## 🛠️ Cara Menjalankan Proyek

### 1️⃣ Clone Repository
git clone https://github.com/parhandesuu/SIGAP-IoT-CaAs-CPSLab.git

---

### 2️⃣ Install Dependency (PlatformIO)

Pastikan library berikut terinstall:
- Blynk
- DHT Sensor Library
- LiquidCrystal_I2C

Atau gunakan `platformio.ini` yang sudah tersedia.

---

### 3️⃣ Konfigurasi WiFi & Blynk

Edit bagian berikut di file `main.cpp`:
#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

char ssid[] = "NamaWiFi";
char pass[] = "PasswordWiFi";

---
### 4️⃣ Upload ke ESP32

Gunakan PlatformIO atau Arduino IDE untuk upload program ke board ESP32.

---

## 🚀 Cara Kerja Sistem

1. ESP32 membaca data dari MQ2 dan DHT11 setiap 2 detik.
2. Data ditampilkan di LCD.
3. LED menyala sesuai level kondisi.
4. Jika kondisi bahaya, buzzer aktif.
5. Data dikirim ke Blynk untuk monitoring jarak jauh.

---

## 📊 Output Sistem

- Monitoring real-time via smartphone
- Notifikasi kondisi abnormal
- Sistem peringatan lokal (LED + Buzzer)
- Tampilan langsung di LCD

---

## 👨‍💻 Pengembang

Project CaAS Kelompok 2 - SIGAP  
2026
