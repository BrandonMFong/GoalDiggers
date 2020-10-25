#include "mod.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>


ESP8266WebServer server(80);   //Web server object. Will be listening in port 80 (default for HTTP)
//https://techtutorialsx.com/2016/10/22/esp8266-webserver-getting-query-parameters/
//volatile int AQI = 0;
//volatile double TempF = 0;
void handleSpecificArg() 
{ 
  String AQImessage = "";
  String TempFmessage = "";
  
  if (server.arg("AQI")== "")
  {
    AQImessage = "AQI Argument not found";
  }
  else
  {     
    AQImessage = "\nAQI Argument = ";
    AQImessage += server.arg("AQI");     //Gets the value of the query parameter
    AQI = server.arg("AQI").toInt();
  }
  
  if (server.arg("TempF")== "")
  {
    TempFmessage = "TempF Argument not found";
  }
  else
  {     
    TempFmessage = "\nTempF Argument = ";
    TempFmessage += server.arg("TempF");     //Gets the value of the query parameter
    TempF = server.arg("TempF").toInt();
  }
  String msg = AQImessage + TempFmessage;
  server.send(200, "text/plain", msg);   
}

void init_Network() 
{
  WiFi.begin(SSIDstring, key); //Connect to the WiFi network
  
  while (WiFi.status() != WL_CONNECTED) //Wait for connection
  { 
    delay(500);
    Serial.println("Waiting to connect…");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP to access the server
  
  server.on("/Values", handleSpecificArg);   //Associate the handler function to the path
  
  server.begin();                                       //Start the server
  Serial.println("Server listening");   
}

void Network() 
{
  server.handleClient();    //Handling of incoming requests
//  Serial.println(AQI);
}
