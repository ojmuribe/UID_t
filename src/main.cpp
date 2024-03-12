#include <Arduino.h>
#include "UID.h"
#include "KeySet.h"

void writeFile(fs::FS &fs, const char *path, const char *message);
void listDir(fs::FS &fs, const char *dirname, uint8_t levels);

void setup()
{
    Serial.begin(115200);

    /* pruebecillas con UIDs
    String sUid = "AA BB CC DD";
    key_t auxUid;
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
    */

    KeySet_t keySet;
    Key_t key;
    char fileName[] = "/keys.json";
    keySet.setFileName(fileName);
    if (keySet.loadFromSPIFFS())
    {
        Serial.println("Fichero de llaves leído correctamente");
        Serial.println("Contenido del fichero:");
        keySet.printFile();
        Serial.println("Contenido del keySet:");
        keySet.printKeySet();
        key.fromString("2C61E022");
        if (keySet.contains(key))
            Serial.println("La llave está!!!");
        else
            Serial.println("La llave no está!!!");
    }
    else
        Serial.println("No se ha podido leer el fichero de llaves");

    key.fromString("2C61E022");
    // keySet.remove(key);
    Serial.println("Tras quitar la llave 2C 61 E0 22:");
    keySet.printKeySet();
    Serial.println("Grabando el fichero");
    // keySet.saveToSPIFFS();
    Serial.println("Cargando el fichero");
    keySet.loadFromSPIFFS();
    Serial.println("Imprimiento del fichero");
    keySet.printFile();
    key.fromString("AABBCCDD");
    keySet.insertKey(key);
    keySet.saveToSPIFFS();
    keySet.loadFromSPIFFS();
    keySet.printFile();
    keySet.remove(key);
    keySet.saveToSPIFFS();
    keySet.loadFromSPIFFS();
    keySet.printFile();
    Serial.println(keySet.getJsonKeyName());
}

void loop()
{
}
