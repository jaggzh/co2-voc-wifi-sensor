// Copy me to config.h and then edit

#define AP_SSID "Your SSID Here"
#define AP_PW   "Your bank password here" // plain text :(
// Obviously don't put your ^^^ bank pw there

// Can specify static IP if you want:
//#define USE_IP_STATIC // Uncomment to use static ip settings
#ifdef USE_IP_STATIC
	IPAddress local_ip(192, 168, 0, 100);
	IPAddress gateway(192, 168, 0, 1);
	IPAddress subnet(255, 255, 255, 0);
#endif

// http://co2-bathroom.local/
// http://co2-bathroom.local/update
// http://co2-bathroom.local/v             // last value
#define MDNS_HOSTNAME "co2-bathroom"       // http://foo.local/update

// You can change the OTA MDNS hostname separately here.
// The http server will be at MDNS_HOSTNAME + ".local"
// The OTA server will be a separate host seen by Arduino,
// or whatever, at OTA_UPDATE_HOSTNAME (on port 8266 by default)
// (change the port yourself, if you want, in ota.cpp)
#define OTA_UPDATE_HOSTNAME MDNS_HOSTNAME  // Can change OTA visible host
//#define OTA_UPDATE_PW      "q**##@3" // uncomment to enable OTA pw
