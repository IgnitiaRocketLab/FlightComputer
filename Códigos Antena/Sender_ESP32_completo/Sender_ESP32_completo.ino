#include <SPI.h>
#include <LoRa.h>

//define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

int counter =0;
void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Sender");

  //setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
  //replace the LoRa.begin(---E-) argument with your location's frequency 
  //433E6 for Asia
  //868E6 for Europe
  //915E6 for North America
  while (!LoRa.begin(915E6)) {
    Serial.println(".");
    delay(500);
  }
   // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("Mensaje ");
  LoRa.print(counter); //Contador del mensaje
/*
  //Datos elegidos 1
  Serial.print("Presion actual: ");
  Serial.print(presion);
  Serial.print(" Pa, Altura relativa: ");
  Serial.print(altura_rel);
  Serial.println(" m; ");
  Serial.print("Altura (filt): ");
  Serial.print(altura_filtrada, 2);
  Serial.print(" m, Velocidad vertical (filt): ");
  Serial.print(vel_vertical, 2);
  Serial.println(" m/s");

  //Mismos datos de la SD
  String line = fecha + "," + hora + ",";
  line += String(gps.location.lat(), 6) + ",";
  line += String(gps.location.lng(), 6) + ",";
  line += String(gps.satellites.value()) + ",";
  line += String(gps.hdop.hdop()) + ",";
  line += String(temp_bmp, 2) + ",";
  line += String(presion, 0) + ",";
  line += String(q.w, 3) + ",";
  line += String(q.x, 3) + ",";
  line += String(q.y, 3) + ",";
  line += String(q.z, 3);
  Serial.print(line);
*/
  LoRa.endPacket();

  counter++;

  delay(10000);
}