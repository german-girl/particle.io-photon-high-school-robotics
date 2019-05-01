// must manually click library to add the tinyGPS.h file

// This #include statement was automatically added by the Particle IDE.
#include <TinyGPS.h>


// This #include statement was automatically added by the Spark IDE.
//#include "TinyGPS.h"


TinyGPS gps;


float lat, lon;
unsigned long age;




char szInfo[64];
// Every 15 minutes 
//int sleep = 15 * 60 * 1000;

void setup(){
    Serial1.begin(9600);
       Particle.publish("Startup may take a few minutes", " Try going outside ");
}

void loop(){
    bool isValidGPS = false;
    
    for (unsigned long start = millis(); millis() - start < 1000;){
        // Check GPS data is available
        while (Serial1.available()){
            char c = Serial1.read();
            
            // parse GPS data
            if (gps.encode(c))
                isValidGPS = true;
        }
    }

    // If we have a valid GPS location then publish it
    if (isValidGPS){
    
        gps.f_get_position(&lat, &lon, &age);
        
        
        
       Particle.publish("altitude in meters =", String(gps.f_altitude(), 0));
       
       
       Particle.publish("Direction N=0 E=90", String(gps.f_course(), 0));
       
       
       Particle.publish("Km per hour", String(gps.f_speed_kmph(), 2));
       delay(1000);
        
        
        
        lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat;
        lon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon;
        Particle.publish("Longitude =", String(lon));
        delay(10);
        Particle.publish("Lattiude =", String(lat));
        delay(10);
        
        
       
        

       
       
       // sprintf(szInfo, "%.6f,%.6f", (lat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lat), (lon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : lon));
    }
    else{
        // Not a vlid GPS location, jsut pass 0.0,0.0
        // This is not correct because 0.0,0.0 is a valid GPS location, we have to pass a invalid GPS location
        // and check it at the client side
       // sprintf(szInfo, "0.0,0.0");
    }
    
    //Spark.publish("gpsloc", szInfo);
    delay(1000);
   Particle.publish("Put into Google Maps", String(String(lat) +  ", " + String(lon)) );
   Particle.publish("- ", "- ");
    // Sleep for some time
    delay(5000);
}





// note yellow green LED on GPS means searching. Best to go outside
// orange means GPS found
