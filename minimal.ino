// =====================================================================
//  MINIMAL: só mostrar cor na tela. Sem WiFi, sem stream, sem buffer.
//  ST7789 240x240 | ESP32-S3
// ---------------------------------------------------------------------
//  Fiacao informada: SCL=42  MOSI=41  DC=37  RST=36  CS=-1  BLK=8
//  (36/37 estao livres na variante default esp32s3 - SDMMC so usa em outras)
// =====================================================================

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_SCL   42
#define TFT_MOSI  41
#define TFT_DC    37
#define TFT_RST   36
#define TFT_CS    -1
#define TFT_BLK    8
#define SPI_CLOCK_HZ 40000000
#define MAX_RETRIES  5

// &SPI = HARDWARE SPI (o construtor com pinos soltos faz software SPI=lento)
Adafruit_ST7789 tft = Adafruit_ST7789(&SPI, TFT_CS, TFT_DC, TFT_RST);

void initializeDisplay() {
  pinMode(TFT_BLK, OUTPUT);
  digitalWrite(TFT_BLK, HIGH);

  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, HIGH);

  for (int attempt = 1; attempt <= MAX_RETRIES; attempt++) {
    // Garante que o controlador saia de um estado anterior.
    digitalWrite(TFT_RST, LOW);
    delay(150);
    digitalWrite(TFT_RST, HIGH);
    delay(250);

    // Reinicia o SPI usando os GPIOs definidos acima.
    SPI.end();
    delay(50);
    SPI.begin(TFT_SCL, -1, TFT_MOSI, -1);
    delay(100);

    // Reinicializa o controlador.
    tft.setSPISpeed(SPI_CLOCK_HZ);
    tft.init(240, 240, SPI_MODE3);
    tft.setRotation(1);
  }
}

void setup() {
  Serial.begin(115200);
  delay(800);
  Serial.println("\n=== MINIMAL ST7789 ===");
  Serial.printf("PSRAM: %s\n", psramFound() ? "SIM" : "NAO");
  Serial.flush();

  initializeDisplay();
  
  tft.fillScreen(ST77XX_BLACK);;

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.setCursor(10, 10); 
  tft.print("ola mundo!");
}

void loop() {
}
