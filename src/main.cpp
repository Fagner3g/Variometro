#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_BMP280.h>

// Define e configura display
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define BMP_SCK (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS (10)
#define BMP085_ADDRESS 0x76
Adafruit_BMP280 bmp;

void setup()
{
  // Inicializa I2C
  Wire.begin();

  // Inicializa display no endereço 0x3C do I2C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  display.setCursor(0, 10);
  display.print("Iniciando novo...");
  display.display();
  delay(1000);

  while (!Serial)
    delay(10); // wait for native usb
  unsigned status;

  status = bmp.begin(BMP085_ADDRESS);
  if (!status)
  {
    // Apaga display
    display.clearDisplay();
    // Configurar tamanho da fonte
    display.setCursor(50, 0);
    display.print("Erro");
    display.setCursor(0, 12);
    display.print("Sensor not found.");
    display.display();
    while (1)
      delay(10);
  }

  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop()
{
  // Apaga display
  display.clearDisplay();

  // Configura cor, utilizar White mesmo que display seja de outra cor
  display.setTextColor(WHITE);

  // Configurar tamanho da fonte
  display.setTextSize(1);

  // Imprime texto
  display.setCursor(0, 0);
  display.print(bmp.readTemperature());
  display.print(" C");
  display.setCursor(0, 12);
  display.print("Altitude: ");
  display.print(bmp.readAltitude(1013.25));
  display.setCursor(0, 25);
  display.print("Pressao: ");
  display.print(bmp.readPressure());
  display.setCursor(0, 30);

  display.display();
}
