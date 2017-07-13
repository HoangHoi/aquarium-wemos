#include <SocketIOClient.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

#define POWER D3
#define LED_PIN D4

const char* ssid = "Tang-4";
const char* password = "!@#$%^&*o9";

const char HexLookup[17] = "0123456789ABCDEF";

String host = "192.168.2.109";
int port = 3000;
bool ledState = false;

SocketIOClient socket;
DynamicJsonBuffer jsonBuffer;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupNetwork() {
    WiFi.begin(ssid, password);
    uint8_t i = 0;
    while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
    if (i == 21) {
        while (1) delay(500);
    }
}

void led(String data) {
    JsonObject& root = jsonBuffer.parseObject(data);
    Serial.println("[light] " + data);
    String color = root["1"]["color"];
    String status = root["1"]["status"];
    // Serial.println(color);
    // Serial.println(status);
    // String r = strtoul(data.substring());
}

void setup() {

    pinMode(LED_PIN, OUTPUT);

    Serial.begin(115200);

    setupNetwork();

    // This initializes the NeoPixel library.
    pixels.begin();

    // socket.setChannel("feed-the-fish");
    socket.on("led-change", led);

    socket.connect(host, port);
    // socket.emit("room", "led-room");
}

void loop() {
    socket.monitor();
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
}
