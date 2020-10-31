#include "esphome.h"
#include <SPI.h>
#include "RF24.h"

class NRF24L01Sensor : public PollingComponent, public Sensor {
public:
  const byte address[6] = {0, 0, 0, 0, 0, 1};

  RF24 radio = RF24(4, 15);

  NRF24L01Sensor() : PollingComponent(5000) {}

  void setup() override {
    radio.begin();
    radio.openReadingPipe(0, address);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();
  }

  void update() override {
    ESP_LOGD("custom", "Chip status %d", radio.isChipConnected());
    ESP_LOGD("custom", "Available %d", radio.available());
    publish_state(42.0);

    if (radio.available()) {
      char text[32] = "";
      radio.read(&text, sizeof(text));
      Serial.println(text);
    }
  }
};
