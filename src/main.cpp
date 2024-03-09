#include <Arduino.h>
#include "UID.h"

void setup()
{
    Serial.begin(115200);

    /* pruebecillas */
    String sUid = "prueba de github";
    UID_t auxUid;
    if (auxUid.fromString(sUid))
    {
        auxUid.printUID();
        String s;
        auxUid.toStringPretty(s);
        Serial.printf("UID guapa: %s\n", s);
    }
    else
        Serial.println("LLave no válida");
}

void loop()
{
}