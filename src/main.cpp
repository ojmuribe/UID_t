#include <Arduino.h>
#include "UID.h"
#include <set>

set<UID_t> validKeys;

void setup()
{
    Serial.begin(115200);

    /* pruebecillas */
    String sUid = "AA BB CC DD";
    UID_t auxUid;
    String s;

    if (auxUid.fromString(sUid))
    {
        auxUid.printUID();
        auxUid.toStringPretty(s);
        validKeys.insert(auxUid);
        Serial.printf("Insertada como válida la llave %s\r\n", s);
    }
    else
        Serial.println("LLave no válida");

    if (auxUid.belongs(validKeys))
        Serial.println("Llave permitida");
    else
        Serial.println("Llave no permitida");

    Serial.printf("Borrada como válida la llave %s\r\n", s);
    validKeys.erase(auxUid);
    if (auxUid.belongs(validKeys))
        Serial.println("Llave permitida");
    else
        Serial.println("Llave no permitida");
}

void loop()
{
}