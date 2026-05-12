// LibelleSWDemo.ino
#include <Libelle.h>

Libelle pyroUp(UP);

void setup() {
	Serial.begin(38400);
	pyroUp.begin();
	Serial.println("Welcome to the lepidopterarium...");
	Serial.println(pyroUp.getHeader());
}

void loop() {
	Serial.println(pyroUp.getString());
	delay(1000);
}
