// Example by Tom Igoe
// Modified for https://www.dfrobot.com by Lumi, Jan. 2014

/*
   This code should show one colored blob for each detected IR source (max four) at the relative position to the camera.
*/

import processing.serial.*;

int lf = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port
PFont f;

void setup() {
  // List all the available serial ports
  // println(Serial.list());
  
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, "COM4", 19200);
  myPort.clear();
  // Throw out the first reading, in case we started reading
  // in the middle of a string from the sender.
  myString = myPort.readStringUntil(lf);
  myString = null;
  size(1023,1023);
  f = createFont("Arial",16,true); // Arial, 16 point, anti-aliasing on
  //frameRate(30);
}

void draw() {
  background(77);
  int[] white = {255, 255, 255};
  int[] green = {0, 255, 0};
  int[] red = {255, 0, 0};
  int[] blue = {0, 0, 255};
  int[][] colours = { red, blue, green, white };
  //while (myPort.available() > 0) {
    myString = myPort.readStringUntil(lf);
    if (myString != null) {
      int[] output = new int[8];
      String[] sample = split(myString, ','); 
      println("sample length:" + sample.length);
      for(int i = 0; i < sample.length; i++) {
        int toNumber = int(trim(sample[i]));
        println("sample:(" + i + ")" + toNumber);
        //println("int sample:" + int(trim(sample[i])));
        //println("sample length: " + sample[i].length());
        // println(int(sample[i]).length());
        output[i] = toNumber;
      }
      //println(output);
      //println("------------------");
      textFont(f,16);
      
      // reference start blob
      ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
      fill(128);
      ellipse(5, 5, 5, 5);
      text("Reference blob (5x, 5y)", 20, 20);
      
      // bar
      rect(100, 100, 600, 110);
      
      int outputLen = output.length;
      
      println(myString + "-" + myString.length() + "-" + outputLen);
        int index = 0;
        for (int i = 0; i < 4; i++) {
          index = i * 2;
          int xx = output[index + 1]; // think y parama is first
          int yy = output[index]; 
          println("index: (" + i + "): " + "x: "+ xx + " y: - " + output[7]);
          
          if ((xx > 0 && xx < 1023) && (yy > 0 && yy < 1023)) {
            fill(colours[i][0], colours[i][1], colours[i][2]);
            text("item: " + i + "x: " + xx + "y: " + yy, xx + 40, yy);
            
            ellipseMode(RADIUS);  // Set ellipseMode to RADIUS
            fill(colours[i][0], colours[i][1], colours[i][2]);
            ellipse(xx, yy, 20, 20);
          }
        }
    }
}
