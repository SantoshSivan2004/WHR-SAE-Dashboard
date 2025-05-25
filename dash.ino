#include <U8g2lib.h>
#include <SPI.h>
#include <string>

// constructor
U8G2_ST7565_NHD_C12864_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/21, /* data=*/12, /* cs=*/9, /* dc=*/22, /* reset=*/19);

int maxTemp = 60; // celsius
int currTemp = 5;
int currTemp2 = 5;
int gear = 0;

void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
}
void loop(void) {

  u8g2.clearBuffer();

// bar width and height
  int barWidth = 10;
  int barHeight = 60;

// bar1 x and y position (left)
  int bar1X = 25;
  int bar1Y = 0;
  int yLabel1;
  int yPosition;

// bar2 x and y position (right)
  int bar2X = 0;
  int bar2Y = 0;

// gear output box width and height
  int boxWidth = 50;
  int boxHeight = 50;

// gear output x and y position
  int boxX1 = ((128 - boxWidth) / 2) + 10;  // 49
  int boxY1 = (64 - boxHeight) / 2;  // 7

// getting height based on sensor*
// *subject to change depending on sensor
  int tempHeight = (currTemp * (barHeight - 4)) / maxTemp;

// sets draw color to 1=solid
  u8g2.setDrawColor(1);

// right most bar
  u8g2.drawFrame(bar1X, bar1Y, barWidth, barHeight); 
  u8g2.drawBox(bar1X, bar1Y, barWidth, tempHeight);


// middle square (gear)
  u8g2.drawFrame(boxX1, boxY1, boxWidth, boxHeight);

// clearing inside the box
  u8g2.setDrawColor(0);
  u8g2.drawBox(boxX1 + 1, boxY1 + 1, boxWidth - 2, boxHeight -2);
  u8g2.setDrawColor(1);

  u8g2.setFont(u8g2_font_helvB24_tf);

  char gearStr[5];
  sprintf(gearStr, "%d", gear);

  int textWidth = u8g2.getStrWidth(gearStr);
  int textAscent = u8g2.getAscent();

  int strX = boxX1 + (boxWidth - textWidth) / 2;
  int strY = boxY1 + (boxHeight + textAscent) /2;

  int flippedX = strX + textWidth;
  int flippedY = strY - textAscent;

  u8g2.setFontDirection(2);
  u8g2.drawStr(flippedX, flippedY, gearStr);

// left bar
  u8g2.drawFrame(bar2X, bar2Y, barWidth, barHeight);
  u8g2.drawBox(bar2X, bar2Y, barWidth, tempHeight);

// sets contrast to max
  u8g2.setContrast(100);

  gear++;
  if (gear > 7)
  {
    gear = 0;
  }

  u8g2.setFontDirection(0);


// simple loop to show temp increasing
  currTemp += 5;
  if (currTemp > maxTemp)
  {
    currTemp = 0;
  }

// same loop as above
  currTemp2 += 5;
  if( currTemp > maxTemp)
  {
    currTemp = 0;
  }

  u8g2.setFont(u8g2_font_3x3basic_tr);

  for (int t= 0; t <= maxTemp; t+=10)
  {
    int yLabel = (bar1Y + barHeight - (t * (barHeight - 4)) / maxTemp) - 1;

    int labelValue = maxTemp - t;

// left most bar
    u8g2.drawLine(bar1X + barWidth, yLabel, bar1X + barWidth + 1, yLabel);
    // u8g2.setCursor(bar1X + barWidth + 5, yLabel + 3);
    u8g2.setCursor(bar1X + barWidth + 4, yLabel + 2);
    u8g2.print(labelValue);      

// right most bar
    u8g2.drawLine(bar2X + barWidth + 1, yLabel, barWidth, yLabel);
    u8g2.setCursor(bar2X + barWidth + 3, yLabel + 2);
    u8g2.print(labelValue);

    // u8g2.setFlipMode(1);
  }

// sends memory frame bufferto display
  u8g2.sendBuffer();

// delay for 1 second
  delay(1000);
}
