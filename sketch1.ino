
#include <Arduino_APDS9960.h>

void setup() {
  Serial.begin(9600);
  while (!Serial)
    ; // Wait for Serial Monitor to open

  if (!APDS.begin()) {
    Serial.println("Error initializing APDS-9960 sensor.");
    while (true)
      ; // Stop forever
  }
}

int proximity = 0;
int r = 0, g = 0, b = 0;
unsigned long lastUpdate = 0;

void loop() {

  // Check if a proximity reading is available.
  if (APDS.proximityAvailable()) {
    proximity = APDS.readProximity();
  }

  // Check if a gesture reading is available
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    switch (gesture) {
    case GESTURE_UP:
      Serial.println("Detected UP gesture");
      break;

    case GESTURE_DOWN:
      Serial.println("Detected DOWN gesture");
      break;

    case GESTURE_LEFT:
      Serial.println("Detected LEFT gesture");
      break;

    case GESTURE_RIGHT:
      Serial.println("Detected RIGHT gesture");
      break;

    default:
      // Ignore
      break;
    }
  }
  if(!APDS.gestureAvailable()){
  Serial.println("Gestures not properly enabled.");
  }
  

 // Check if a color reading is available
  if (APDS.colorAvailable()) {
    APDS.readColor(r, g, b);
  }

  // Print updates every 100 ms
  if (millis() - lastUpdate > 100) {
    lastUpdate = millis();
    Serial.print("PR=");
    Serial.print(proximity);
    Serial.print(" RGB=");
    Serial.print(r);
    Serial.print(",");
    Serial.print(g);
    Serial.print(",");
    Serial.println(b);
  }
}
