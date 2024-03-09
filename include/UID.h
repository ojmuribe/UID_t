/**************************************************************
   UID
   (c) 2024 Juan M. Uribe

   Class for handling Rfid UID keys
 ***************************************************************/
#pragma once
#include <vector>
#include <set>

using namespace std;

class UID_t
{
private:
  uint8_t keySize;
  vector<uint8_t> keyUID;

public:
  // Get the size of a key UID
  uint8_t size();

  // Set the size of a key UID
  void size(uint8_t size);

  // Print the key UID to Serial
  void printUID();

  // Get the value of the position i of a key UID
  uint8_t keyValue(int i);

  // Set the value of the position i of a key UID
  void keyValue(int i, uint8_t value);

  // Converts a key UID into a string
  void toString(String &s);

  // Set a string with a key UID
  void toStringPretty(String &s);

  // Get a key UID from a string
  bool fromString(const String &s);

  // Compairs if equal two key UIDs
  friend bool operator==(const UID_t &uid1, const UID_t &uid2);

  // Compairs if not equal two key UIDs
  friend bool operator!=(const UID_t &uid1, const UID_t &uid2);

  // Returns true if a key UID size is lower than other
  friend bool operator<(const UID_t &uid1, const UID_t &uid2);

  // Returns true if a key UID size is greater than other
  friend bool operator>(const UID_t &uid1, const UID_t &uid2);

  // Copy a key UID to another
  UID_t &operator=(const UID_t &value);

  // Check if a key UID belongs to a set
  bool belongs(const set<UID_t> &validKeys);

  // Insert a key UID into a key UID set
  bool insertInto(set<UID_t> &key);

  // Erase a key UID from a key UID set
  bool eraseFrom(set<UID_t> &key);
};

uint8_t UID_t::size()
{
  return keySize;
}

void UID_t::size(uint8_t size)
{
  keySize = size;
  keyUID.resize(size);
}

uint8_t UID_t::keyValue(int i)
{
  return keyUID[i];
}

void UID_t::keyValue(int i, uint8_t value)
{
  keyUID[i] = value;
}

void UID_t::printUID()
{
  for (int i = 0; i < keySize; i++)
  {
    Serial.printf("%02X ", keyUID[i]);
  }
  Serial.println();
}

void UID_t::toString(String &s)
{
  char aux[10];
  for (int i = 0; i < keySize; i++)
  {
    sprintf(aux, "%02X", keyUID[i]);
    s += aux;
  }
}

void UID_t::toStringPretty(String &s)
{
  char aux[10];
  for (int i = 0; i < keySize - 1; i++)
  {
    sprintf(aux, "%02X ", keyUID[i]);
    s += aux;
  }
  sprintf(aux, "%02X", keyUID[keySize - 1]);
  s += aux;
}

bool UID_t::fromString(const String &s)
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
  // Convert
  size(len);
  String substring;
  char str[2];
  unsigned char data;
  for (int i = 0; i < keySize; i++)
  {
    substring = auxString.substring(i * 2, (i + 1) * 2);
    substring.toCharArray(str, substring.length() + 1);
    data = strtoul(str, nullptr, 16);
    keyUID[i] = data;
  }
  return true;
}

bool operator!=(const UID_t &uid1, const UID_t &uid2)
{
  bool result = false;
  if (uid1.keySize != uid2.keySize)
    result = true;
  else
  {
    for (int i = 0; i < uid1.keySize; i++)
    {
      if (uid1.keyUID[i] != uid2.keyUID[i])
        result = true;
    }
  }
  return result;
}

bool operator==(const UID_t &uid1, const UID_t &uid2)
{
  return !(uid1 != uid2);
}

bool operator<(const UID_t &uid1, const UID_t &uid2)
{
  return uid1.keySize < uid2.keySize;
}

bool operator>(const UID_t &uid1, const UID_t &uid2)
{
  return uid1.keySize > uid2.keySize;
}

UID_t &UID_t::operator=(const UID_t &value)
{
  keySize = value.keySize;
  keyUID = value.keyUID;
  return *this;
}

bool UID_t::belongs(const set<UID_t> &validKeys)
{
  return validKeys.find(*this) != validKeys.end();
}

bool UID_t::insertInto(set<UID_t> &key)
{
  std::pair<std::set<UID_t>::iterator, bool> ret;
  ret = key.insert(*this);
  return ret.second;
}

bool UID_t::eraseFrom(set<UID_t> &key)
{
  int ret;
  ret = key.erase(*this);
  return ret != 0;
}
