# ST7789

Driver mínimo para display **ST7789 240x240** no **ESP32-S3**, com Adafruit_GFX/Adafruit_ST7789 em SPI de hardware.

## Hardware

| ST7789 | ESP32-S3 |
|--------|----------|
| SCL (CLK) | GPIO 42 |
| SDA (MOSI) | GPIO 41 |
| DC | GPIO 37 |
| RES (RST) | GPIO 36 |
| CS | não ligado (módulo com CS interno) |
| BLK | GPIO 8 (ou 3V3) |
| VCC | 3V3 |
| GND | GND |

## Board (Arduino IDE > Tools)

- Board: **ESP32S3 Dev Module**
- Flash Mode: **QIO 80MHz**
- Flash Size: **16MB (128Mb)**
- Partition Scheme: **Default**
- PSRAM: **Disabled**
- CPU Frequency: **240MHz**
- Upload Speed: **921600**

## Bibliotecas

- Adafruit_GFX_Library
- Adafruit_ST7735_and_ST7789_Library

## Uso

Abra `minimal.ino` na Arduino IDE e faça upload. A tela mostra "ola mundo!".

## Notas

- **Use o construtor `Adafruit_ST7789(&SPI, cs, dc, rst)`.** O construtor com pinos soltos
  (`cs, dc, mosi, sclk, rst`) cai em **software SPI (bit-bang)**, ~600x mais lento.
- `initializeDisplay()` faz reset + `SPI.begin()` + `init()` com **retry**, o que torna a
  inicialização confiável (o controlador às vezes não responde no primeiro attempt).
- SPI roda a **40MHz**.
