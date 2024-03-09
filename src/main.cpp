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

    Serial.printf("Número de llaves: %d\n", validKeys.size());
    if (auxUid.fromString(sUid))
    {
        auxUid.printUID();
        auxUid.toStringPretty(s);
        if (auxUid.insertInto(validKeys))
            Serial.printf("Insertada como válida la llave %s\r\n", s);
        else
            Serial.printf("No se ha podido insertar como válida la llave %s\r\n", s);
    }
    Serial.printf("Número de llaves: %d\n", validKeys.size());

    if (validKeys.find(auxUid) != validKeys.end())
        Serial.println("Llave permitida");
    else
        Serial.println("Llave no permitida");

    Serial.printf("Borrada como válida la llave %s\r\n", s);
    auxUid.eraseFrom(validKeys);
    Serial.printf("Número de llaves: %d\n", validKeys.size());

    if (auxUid.belongs(validKeys))
        Serial.println("Llave permitida");
    else
        Serial.println("Llave no permitida");
}

void loop()
{
}