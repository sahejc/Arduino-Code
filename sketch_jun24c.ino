#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ImageReader.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

#include <Adafruit_STMPE610.h>
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Adafruit_GFX_Button.h>

#define TFT_CLK 13
#define TFT_RST 12 // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 11
#define TFT_CS 10

Adafruit_TFTLCD tft(TFT_CS, TFT_DC, TFT_RST, TFT_CLK, 9, 8, 7);

#include <Adafruit_Fingerprint.h>
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&Serial1);

#define sclk 13
#define mosi 11
#define miso 12
#define ss 10
Adafruit_ILI9341 tft = Adafruit_ILI9341(ss, sclk, mosi, miso, 2, 3, 4, 5, 6, 7, 8, 9);


#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

#include <Servo.h>
Servo myservo; // create servo object to control a servo

#include "OpenCv_Utility.h"

Adafruit_ImageReader reader;
Adafruit_Image img;
ImageCrop cropped;
ImageGrayscale gray;
ImageResize resized;
ImageEdges edges;

CascadeClassifier faceCascade;
const int minFaceSize = 80; // Minimum face size (in pixels) for detection
const int scaleFactor = 4; // Image downscale factor for detection

void setup() {
  Serial.begin(115200);
  
  // Initialize TFT LCD
  tft.begin(0x9341);
  tft.setRotation(3);

  // Initialize fingerprint sensor
  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1);
  }

  // Initialize thermal sensor
  mlx.begin();

  // Initialize servo
  myservo.attach(6);
  myservo.write(0); // Set initial position
  
  // Initialize OpenCV face detection
  if (!faceCascade.load("haarcascade_frontalface_default.xml")) {
    Serial.println("Failed to load face cascade XML file!");
    while (1);
  }

  Serial.println("Setup complete.");
}

void loop() {
  // Capture image from camera or any other source
  // Save the image as a 24-bit BMP file on an SD card or in the internal SPIFFS

  // Load the image from the SD card or SPIFFS
  if (!reader.loadBMP("image.bmp", img)) {
    Serial.println("
