#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourAuthToken";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";

BlynkTimer timer;

void notifyUptime()
{
  long uptime = millis() / 60000L;

  // Actually send the message.
  // Note:
  //   We allow 1 notification per 5 seconds for now.
  Blynk.notify(String("Running for ") + uptime + " minutes.");

  // You can also use {DEVICE_NAME} placeholder for device name,
  // that will be replaced by your device name on the server side.
  // Blynk.notify(String("{DEVICE_NAME} running for ") + uptime + " minutes.");
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Notify immediately on startup
  Blynk.notify("Device started");

  // Setup a function to be called every minute
  timer.setInterval(60000L, notifyUptime);
}

void loop()
{
  Blynk.run();
  timer.run();
}
