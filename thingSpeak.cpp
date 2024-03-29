#include <iostream>
#include <sstream>
#include <fstream>
#include "network/SocketClient.h"
#define CPU_TEMP "/sys/class/thermal/thermal_zone0/temp"
using namespace std;
using namespace exploringRPi;

int getCPUTemperature() {          // get the CPU temperature
   int cpuTemp;                    // store as an int
   fstream fs;
   fs.open(CPU_TEMP, fstream::in); // read from the file
   fs >> cpuTemp;
   fs.close();
   return cpuTemp;
}

int main() {
   ostringstream head, data;
   cout << "Starting ThingSpeak Example" << endl;
   //tao socket
   SocketClient sc("api.thingspeak.com",80);
   data << "field1=" << getCPUTemperature() << endl;
   sc.connectToServer();
   //tao request to server
   head << "POST /update HTTP/1.1\n"
        << "Host: api.thingspeak.com\n"
        << "Connection: close\n"
        << "X-THINGSPEAKAPIKEY: 1YUXJW98PSJEKA8X\n"
        << "Content-Type: application/x-www-form-urlencoded\n"
        << "Content-Length:" << string(data.str()).length() << "\n\n";
    //gui request va data
   sc.send(string(head.str()));
   sc.send(string(data.str()));
   string rec = sc.receive(1024);
   cout << "[" << rec << "]" << endl;
   cout << "End of ThingSpeak Example" << endl;

}
