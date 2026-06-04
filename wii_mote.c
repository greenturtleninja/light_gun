// Wii Remote IR sensor  test sample code  by kako http://www.kako.com
// modified output for Wii-BlobTrack program by RobotFreak http://www.letsmakerobots.com/user/1433
// modified for https://dfrobot.com by Lumi, Jan. 2014

#include <Wire.h>

int IRsensorAddress = 0xB0;
//int IRsensorAddress = 0x58;
int slaveAddress;
int ledPin = 13;
boolean ledState = false;
byte data_buf[16];
int i;

int Ix[4];
int Iy[4];
int s;
int b;

void Write_2bytes(byte d1, byte d2)
{
    Wire.beginTransmission(slaveAddress);
    Wire.write(d1); Wire.write(d2);
    Wire.endTransmission();
}

void setup()
{
    slaveAddress = IRsensorAddress >> 1;   // This results in 0x21 as the address to pass to TWI
    Serial.begin(19200);
    pinMode(ledPin, OUTPUT);      // Set the LED pin as output
    Wire.begin();
    // IR sensor initialize
    Write_2bytes(0x30,0x01); delay(10);
    Write_2bytes(0x30,0x08); delay(10);
    Write_2bytes(0x06,0x90); delay(10);
    Write_2bytes(0x08,0xC0); delay(10);
    Write_2bytes(0x1A,0x40); delay(10);
    Write_2bytes(0x33,0x33); delay(10);
    delay(100);
}

void write_to_dataBuf(int index, int index_data_buf) {


  Ix[index] = data_buf[index_data_buf];
  Iy[index] = data_buf[index_data_buf + 1];
  s   = data_buf[index_data_buf + 2];
  Ix[index] += (s & 0x30) <<4;
  Iy[index] += (s & 0xC0) <<2;
}

void loop()
{
    ledState = !ledState;
    if (ledState) { digitalWrite(ledPin,HIGH); } else { digitalWrite(ledPin,LOW); }

    //IR sensor read
    Wire.beginTransmission(slaveAddress);
    Wire.write(0x36);
    Wire.endTransmission();

    Wire.requestFrom(slaveAddress, 16);        // Request the 2 byte heading (MSB comes first)
    for (i=0;i<16;i++) { data_buf[i]=0; }
    i=0;
    while(Wire.available() && i < 16) {
        data_buf[i] = Wire.read();
        i++;
    }

    for(i=0; i<4; i++) {
      b = (i * 3) + 1;
      write_to_dataBuf(i, b);
    }

    for(i=0; i<4; i++)
    {
      if (Ix[i] < 1000)
        Serial.print("");
      if (Ix[i] < 100)
        Serial.print("");
      if (Ix[i] < 10)
        Serial.print("");
      Serial.print( int(Ix[i]) );
      Serial.print(",");
      if (Iy[i] < 1000)
        Serial.print("");
      if (Iy[i] < 100)
        Serial.print("");
      if (Iy[i] < 10)
        Serial.print("");
      Serial.print( int(Iy[i]) );
      if (i<3)
        Serial.print(",");
    }
    Serial.println("");
    delay(15);
}

