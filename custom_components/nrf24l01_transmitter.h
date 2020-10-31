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
    radio.openWritingPipe(address);
    radio.setPALevel(RF24_PA_MIN);
    radio.stopListening();

  }

  void update() override {
    ESP_LOGD("custom", "Chip status %d", radio.isChipConnected());
    ESP_LOGD("custom", "Chip failure %d", radio.failureDetected);
    ESP_LOGD("custom", "Chip valid %d", radio.isValid());
    ESP_LOGD("custom", "Chip channel %d", radio.getChannel());
    ESP_LOGD("custom", "Chip test carrier %d", radio.testCarrier());
    ESP_LOGD("custom", "Chip test RPD %d", radio.testRPD());
    ESP_LOGD("custom", "Chip PA %d", radio.isPVariant());
    publish_state(42.0);

    radio.printDetails();

    const char text[] = "Hello World";
    bool write_status = radio.write(&text, sizeof(text));
    ESP_LOGD("custom", "Write status %d", write_status);
  }
};
