#define BLYNK_TEMPLATE_ID "TMPL6Q136Ecva"
#define BLYNK_TEMPLATE_NAME "Project CaAS Kel 2 SIGAP"
#define BLYNK_AUTH_TOKEN "AzGAEDoR2Rsqq5o_emmaTYNs8NL-QdtN"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// --- KONFIGURASI WIFI ---
char ssid[] = "Galaxy A73 5GCB26";
char pass[] = "dzyy6328";

// --- DEKLARASI PIN ---
#define MQ2_PIN       2   
#define DHT_PIN       6  
#define BUZZER_PIN    1   
#define LED_RED       7  
#define LED_YELLOW    21  
#define LED_GREEN     20  
#define I2C_SDA       8  
#define I2C_SCL       9  

#define DHTTYPE DHT11

DHT dht(DHT_PIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); 
BlynkTimer timer;

// Batas setiap sensor 
int gasSedang = 1500; 
int gasTinggi = 2500; 
float suhuSedang = 31.0; 
float suhuTinggi = 35.0; 

// --- FUNGSI PEMBACAAN SENSOR & LOGIKA ---
void bacaSensorDanLogika() {
  int gasValue = analogRead(MQ2_PIN);
  float suhuValue = dht.readTemperature();

  // Fallback jika DHT11 gagal terbaca
  if (isnan(suhuValue)) {
    Serial.println("Gagal membaca DHT11!");
    suhuValue = 0;
  }

  // Kirim data ke Blynk
  Blynk.virtualWrite(V0, suhuValue);
  Blynk.virtualWrite(V1, gasValue);

  // Print ke Serial Monitor
  Serial.printf("Suhu: %.1f C | Gas: %d\n", suhuValue, gasValue);

  // --- TAMPILAN LCD BARIS 1 ---
  char line1[17];
  // %-4d angka gas disiapkan 4 digit rata kiri
  // %.1f angka suhu disiapkan 1 angka di belakang koma
  snprintf(line1, sizeof(line1), "G:%-4d T:%.1fC ", gasValue, suhuValue);
  
  lcd.setCursor(0, 0);
  lcd.print(line1);

  // --- LOGIKA FLOW & TAMPILAN LCD BARIS 2 (Pesan) ---
  lcd.setCursor(0, 1);

  // 1. KONDISI HIGH / BAHAYA
  if (gasValue >= gasTinggi) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    tone(BUZZER_PIN, 1000);
    lcd.print("DANGER GAS HIGH"); 
  } 
  else if (suhuValue >= suhuTinggi) {
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    tone(BUZZER_PIN, 1000);
    lcd.print("DANGER TEMP HIGH");
  } 
  
  // 2. KONDISI MEDIUM / SEDANG
  else if (gasValue >= gasSedang) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    noTone(BUZZER_PIN);
    lcd.print("DETECTED GAS"); 
  } 
  else if (suhuValue >= suhuSedang) {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    noTone(BUZZER_PIN);
    lcd.print("TEMPERATURE WARM");
  } 
  
  // 3. KONDISI LOW / NORMAL
  else {
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
    noTone(BUZZER_PIN);
    
    // Bergantian menampilkan status Normal
    static bool toggleText = false;
    toggleText = !toggleText;
    if (toggleText) {
      lcd.print("GAS NORMAL");
    } else {
      lcd.print("TEMP NORMAL");
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(3000); // MEMBERI WAKTU LCD UNTUK BOOTING

  // Inisialisasi I2C dengan frekuensi standar (100kHz) agar sinyal stabil
  Wire.begin(I2C_SDA, I2C_SCL, 100000); 
  
  // Urutan inisialisasi yang lebih "sopan" untuk LCD
  lcd.init();
  delay(500);
  lcd.clear();
  delay(500);
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Sistem SIGAP");
  lcd.setCursor(0, 1);
  lcd.print("Online...");

  // Pin mode dan sensor
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, bacaSensorDanLogika); 
}

void loop() {
  Blynk.run();
  timer.run();
}