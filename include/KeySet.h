/**************************************************************
   KeySet
   (c) 2024 Juan M. Uribe

   Class for handling sets of UID keys
 ***************************************************************/
#pragma once
#include "UID.h"
#include <ArduinoJson.h>
#include <FS.h>
#include <SPIFFS.h>

using namespace std;

// typedef String keyType;

class KeySet_t
{
private:
  set<Key_t> keySet;
  char *fileName;
  String jsonKeyName = "Key";

public:
  void setFileName(char *name);
  char *getFileName(void);
  bool isValidStringKey(const String &s);
  bool loadFromSPIFFS(void);
  bool saveToSPIFFS(void);
  void printFile(void);
  void printKeySet(void);
  bool contains(const Key_t &key);
  bool insertKey(const Key_t &key);
  bool remove(const Key_t &key);
  void setJsonKeyName(const String &s);
  String getJsonKeyName(void);
};

void KeySet_t::setFileName(char *name)
{
  fileName = name;
}

char *KeySet_t::getFileName(void)
{
  return fileName;
}

bool KeySet_t::loadFromSPIFFS(void)
{
  SPIFFS.begin();
  File file = SPIFFS.open(fileName);
  if (!file)
    return false;
  else
  {
    JsonDocument doc;
    deserializeJson(doc, file);
    JsonObject obj = doc.as<JsonObject>();
    keySet.clear();
    for (JsonPair p : obj)
    {
      String keyValue = p.value().as<String>();
      if (isValidStringKey(keyValue))
      {
        Key_t key;
        key.fromString(keyValue);
        if (!insertKey(key))
          return false;
      }
    }
    file.close();
    return true;
  }
}

bool KeySet_t::saveToSPIFFS(void)
{
  JsonDocument doc;
  bool result = true;
  int count = 0;
  for (auto uid : keySet)
  {
    if (uid.toString() != "")
    {
      String keyString = jsonKeyName + "_";
      String auxString;
      auxString = uid.toString();
      char stringNumber[2];
      sprintf(stringNumber, "%02d", count++);
      keyString += stringNumber;
      doc[keyString] = auxString;
    }
  }
  SPIFFS.begin();
  File file = SPIFFS.open(fileName, FILE_WRITE);
  if (!file)
    result = false;
  else
  {
    serializeJson(doc, file);
  }
  return result;
}

void KeySet_t::printFile(void)
{
  // Open file for reading
  File file = SPIFFS.open(fileName);
  if (!file)
  {
    Serial.println(F("Failed to read file"));
    return;
  }

  // Extract each characters by one by one
  while (file.available())
  {
    Serial.print((char)file.read());
  }
  Serial.println();

  // Close the file
  file.close();
}

bool KeySet_t::remove(const Key_t &key)
{
  return keySet.erase(key);
}

void KeySet_t::printKeySet(void)
{
  for (Key_t uid : keySet)
  {
    Serial.println(uid.toString());
  }
}

bool KeySet_t::isValidStringKey(const String &s)
{
  // Check valid characters and remove spaces
  String auxString;
  for (int i = 0; i < s.length(); i++)
  {
    if (int(s[i]) != 0x20 && isxdigit(s[i]))
    {
      auxString += s[i];
    }
  }
  // Check the proper length
  uint16_t len = auxString.length() / 2;
  if ((len != 4) && (len != 7) && (len != 10) || (auxString.length() % 2 != 0))
  {
    return false;
  }
  return true;
}

bool KeySet_t::contains(const Key_t &key)
{
  return keySet.count(key) != 0;
}

bool KeySet_t::insertKey(const Key_t &key)
{
  pair<set<Key_t>::iterator, bool> ret;
  ret = keySet.insert(key);
  return ret.second;
}

void KeySet_t::setJsonKeyName(const String &s)
{
  jsonKeyName = s;
}

String KeySet_t::getJsonKeyName(void)
{
  return jsonKeyName;
}
