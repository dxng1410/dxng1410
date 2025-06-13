/*  
  Rui Santos & Sara Santos - Random Nerd Tutorials
  https://RandomNerdTutorials.com/esp32-web-server-beginners-guide/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*/
#include "TaskWebSever.h"

// Username and password for web page access
const char* http_username = "admin";
const char* http_password = "admin";

// Assign output variables to GPIO pins
const int output10 = 10;
const int output17 = 17;
String output10State = "off";
String output17State = "off";

// Create a web server object
WebServer server(80);

// Function to authenticate user
bool isAuthenticated() {
  if (!server.authenticate(http_username, http_password)) {
    server.requestAuthentication();
    return false;
  }
  return true;
}

// Function to handle the root URL and show the current states
void handleRoot() {
  if (!isAuthenticated()) return;

  String html = "<!DOCTYPE html><html><head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<link rel=\"icon\" href=\"data:,\">";
  html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  html += ".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  html += ".button2 { background-color: #555555; }</style></head>";
  html += "<body><h1>ESP32 Web Server</h1>";

  // Display GPIO 26 controls
  html += "<p>GPIO 26 - State " + output10State + "</p>";
  if (output10State == "off") {
    html += "<p><a href=\"/26/on\"><button class=\"button\">ON</button></a></p>";
  } else {
    html += "<p><a href=\"/26/off\"><button class=\"button button2\">OFF</button></a></p>";
  }

  // Display GPIO 27 controls
  html += "<p>GPIO 27 - State " + output17State + "</p>";
  if (output17State == "off") {
    html += "<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>";
  } else {
    html += "<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>";
  }

  html += "</body></html>";
  server.send(200, "text/html", html);
}

// Function to handle turning GPIO 26 on
void handleGPIO10On() {
  if (!isAuthenticated()) return;
  output10State = "on";
  digitalWrite(output10, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 26 off
void handleGPIO10Off() {
  if (!isAuthenticated()) return;
  output10State = "off";
  digitalWrite(output10, LOW);
  handleRoot();
}

// Function to handle turning GPIO 27 on
void handleGPIO17On() {
  if (!isAuthenticated()) return;
  output17State = "on";
  digitalWrite(output17, HIGH);
  handleRoot();
}

// Function to handle turning GPIO 27 off
void handleGPIO17Off() {
  if (!isAuthenticated()) return;
  output17State = "off";
  digitalWrite(output17, LOW);
  handleRoot();
}

bool check=false;

void InitWebsever() {
  // Initialize the output variables as outputs
  if(check)
    return;
  pinMode(output10, OUTPUT);
  pinMode(output17, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output10, LOW);
  digitalWrite(output17, LOW);

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println("ACLAB");
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  publishData("webseverIP", WiFi.localIP().toString());
  
  // Set up the web server to handle different routes with authentication
  server.on("/", handleRoot);
  server.on("/26/on", handleGPIO10On);
  server.on("/26/off", handleGPIO10Off);
  server.on("/27/on", handleGPIO17On);
  server.on("/27/off", handleGPIO17Off);

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
  check=true;
}

void WebSeverloop() {
  // Handle incoming client requests
    if ( WiFi.status() != WL_CONNECTED)
    {
        return ;
    }
    InitWebsever();
  server.handleClient();
}