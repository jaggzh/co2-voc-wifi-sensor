/*
	To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>

#include "config.h"     // main config
#include "co2-sensor.h" // uint16_t eco2, etvoc, errstat, raw;

const char* host = MDNS_HOSTNAME;
const char* ssid = AP_SSID;         // see config.h
const char* password = AP_PW;       // see line above

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;

void handle_v() {
	// uint16_t eco2, etvoc, errstat, raw;
	httpServer.send(200, "text/plain",
		"eco2:\t" + String(eco2) + 
		"\tetvoc:\t" + String(etvoc) + 
		"\terrstat:\t" + String(errstat) + 
		"\traw:\t" + String(raw) + 
		"\n");
}

void handle_root() {
	httpServer.send(200, "text/html",
		"<div>Last reading <a href=/v>/v</a></div>"
		"<div>[ Update <a href=/update>/update</a> ]</div>");
}

void handle_404(){
	httpServer.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

void setup_wifi(void) {
	// Serial.begin(115200);
	// Serial.println();
	Serial.println("Init wifi...");
	#ifdef USE_IP_STATIC
		//if (!WiFi.config(local_ip, gateway, subnet, primaryDNS, secondaryDNS)) {
		if (!WiFi.config(local_ip, gateway, subnet)) {
			Serial.println("WiFi Static: failed to configure");
		}
	#endif
	WiFi.mode(WIFI_AP_STA);
	WiFi.begin(ssid, password);

	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		WiFi.begin(ssid, password);
		Serial.println("WiFi failed, retrying.");
	}

	MDNS.begin(host);

	httpUpdater.setup(&httpServer);
	httpServer.begin();
	httpServer.on("/", handle_root);
	httpServer.on("/v", handle_v); // value of last reading
	httpServer.onNotFound(handle_404);

	MDNS.addService("http", "tcp", 80);
	Serial.println("HTTPUpdateServer ready!");
	Serial.printf("Open http://%s.local/update in your browser\n", host);
}

void loop_wifi(void) {
	httpServer.handleClient();
	MDNS.update();
}

