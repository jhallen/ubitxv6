#ifndef _NANO_GUI_H_
#define _NANO_GUI_H_

/* UI functions */
struct Point {
  int x, y;
};
extern struct Point ts_point;

void displayInit();
void displayClear(unsigned int color);
void displayPixel(unsigned int x, unsigned int y, unsigned int c);
void displayHline(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void displayVline(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void displayRect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);
void displayFillrect(unsigned int x,unsigned int y,unsigned int w,unsigned int h,unsigned int c);
void displayChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg);
int displayTextExtent(char *text);
void displayRawText(char *text, int x1, int y1, int color, int background);
void displayText(char *text, int x1, int y1, int w, int h, int color, int background, int border, int just);

/* touch functions */
boolean readTouch();

void setupTouch();
void scaleTouch(struct Point *p);

// Color definitions
#define DISPLAY_BLACK       0x0000  ///<   0,   0,   0
#define DISPLAY_NAVY        0x000F  ///<   0,   0, 123
#define DISPLAY_DARKGREEN   0x03E0  ///<   0, 125,   0
#define DISPLAY_DARKCYAN    0x03EF  ///<   0, 125, 123
#define DISPLAY_MAROON      0x7800  ///< 123,   0,   0
#define DISPLAY_PURPLE      0x780F  ///< 123,   0, 123
#define DISPLAY_OLIVE       0x7BE0  ///< 123, 125,   0
#define DISPLAY_LIGHTGREY   0xC618  ///< 198, 195, 198
#define DISPLAY_DARKGREY    0x7BEF  ///< 123, 125, 123
#define DISPLAY_BLUE        0x001F  ///<   0,   0, 255
#define DISPLAY_GREEN       0x07E0  ///<   0, 255,   0
#define DISPLAY_CYAN        0x07FF  ///<   0, 255, 255
#define DISPLAY_RED         0xF800  ///< 255,   0,   0
#define DISPLAY_MAGENTA     0xF81F  ///< 255,   0, 255
#define DISPLAY_YELLOW      0xFFE0  ///< 255, 255,   0
#define DISPLAY_WHITE       0xFFFF  ///< 255, 255, 255
#define DISPLAY_ORANGE      0xFD20  ///< 255, 165,   0
#define DISPLAY_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define DISPLAY_PINK        0xFC18  ///< 255, 130, 198

#define TEXT_LINE_HEIGHT 18
#define TEXT_LINE_INDENT 5

#define BUTTON_PUSH
#define BUTTON_CHECK
#define BUTTON_SPINNER

#define CENTERED 1
#define LEFT 0

/// Font data stored PER GLYPH
typedef struct {
  uint16_t bitmapOffset;     ///< Pointer into GFXfont->bitmap
  uint8_t  width;            ///< Bitmap dimensions in pixels
        uint8_t  height;           ///< Bitmap dimensions in pixels
  uint8_t  xAdvance;         ///< Distance to advance cursor (x axis)
  int8_t   xOffset;          ///< X dist from cursor pos to UL corner
        int8_t   yOffset;          ///< Y dist from cursor pos to UL corner
} GFXglyph;

/// Data stored for FONT AS A WHOLE
typedef struct { 
  uint8_t  *bitmap;      ///< Glyph bitmaps, concatenated
  GFXglyph *glyph;       ///< Glyph array
  uint8_t   first;       ///< ASCII extents (first char)
        uint8_t   last;        ///< ASCII extents (last char)
  uint8_t   yAdvance;    ///< Newline distance (y axis)
} GFXfont;

const uint8_t ubitxBitmaps[] PROGMEM = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC,
  0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80,
  0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
  0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F,
  0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC,
  0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80,
  0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
  0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F,
  0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC,
  0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80,
  0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
  0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F,
  0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC,
  0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80,
  0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
  0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F,
  0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC,
  0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80,
  0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
  0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F,
  0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC,
  0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80,
  0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0,
  0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F,
  0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0,
  0xFF, 0xFF, 0xFF, 0xFF, 0x21, 0xFF, 0xE0, 0xF3, 0xF9, 0xFC, 0xFE, 0x7E,
  0x3B, 0x1D, 0x84, 0x0E, 0x70, 0x73, 0x83, 0x9C, 0x18, 0xC7, 0xFF, 0xBF,
  0xFD, 0xFF, 0xE3, 0x9C, 0x18, 0xC0, 0xC6, 0x0E, 0x7D, 0xFF, 0xEF, 0xFF,
  0x18, 0xC0, 0xC6, 0x0E, 0x70, 0x73, 0x83, 0x9C, 0x00, 0x04, 0x01, 0xF8,
  0x7F, 0xCF, 0xDE, 0xE4, 0xEE, 0x4E, 0xE4, 0x0F, 0x40, 0x7E, 0x03, 0xFC,
  0x0F, 0xE0, 0x5E, 0x04, 0xFE, 0x4F, 0xE4, 0xFF, 0x4E, 0x7F, 0xE3, 0xFC,
  0x04, 0x00, 0x40, 0x04, 0x00, 0x3C, 0x06, 0x07, 0xE0, 0x60, 0xFF, 0x0C,
  0x0C, 0x30, 0x80, 0xC3, 0x18, 0x0C, 0x31, 0x00, 0xFF, 0x30, 0x07, 0xE6,
  0x00, 0x3C, 0x60, 0x00, 0x0C, 0x7C, 0x00, 0xCF, 0xE0, 0x19, 0xC6, 0x01,
  0x98, 0x70, 0x31, 0x87, 0x03, 0x1C, 0x60, 0x60, 0xFE, 0x04, 0x07, 0xC0,
  0x0F, 0x80, 0x1F, 0xC0, 0x3D, 0xE0, 0x38, 0xE0, 0x3C, 0xE0, 0x1D, 0xC0,
  0x1F, 0xC0, 0x0F, 0x00, 0x3F, 0x8C, 0x7B, 0xDC, 0x71, 0xDC, 0xF1, 0xFC,
  0xF0, 0xF8, 0xF0, 0x78, 0x79, 0xFC, 0x7F, 0xFC, 0x3F, 0x9E, 0x00, 0x00,
  0xFF, 0xFF, 0xE6, 0x60, 0x0C, 0x71, 0x8E, 0x31, 0xC7, 0x38, 0xE3, 0x8E,
  0x38, 0xE3, 0x8E, 0x38, 0x71, 0xC7, 0x0E, 0x38, 0x70, 0xC0, 0xC3, 0x86,
  0x1C, 0x70, 0xE3, 0x8E, 0x1C, 0x71, 0xC7, 0x1C, 0x71, 0xCE, 0x38, 0xE7,
  0x1C, 0x63, 0x8C, 0x00, 0x10, 0x10, 0x10, 0xFE, 0x7C, 0x38, 0x6C, 0x44,
  0x06, 0x00, 0x60, 0x06, 0x00, 0x60, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x60,
  0x06, 0x00, 0x60, 0x06, 0x00, 0xFF, 0xF2, 0xFE, 0xFF, 0xFF, 0xC0, 0xFF,
  0xF0, 0x04, 0x08, 0x30, 0x60, 0x83, 0x06, 0x08, 0x10, 0x60, 0xC1, 0x06,
  0x0C, 0x10, 0x20, 0xC0, 0x3F, 0x8F, 0xF9, 0xEF, 0x78, 0xFE, 0x0F, 0xC1,
  0xF8, 0x3F, 0x07, 0xE0, 0xFC, 0x1F, 0x83, 0xF0, 0x7E, 0x0F, 0xE3, 0xDE,
  0xF3, 0xFE, 0x3F, 0x80, 0x80, 0x06, 0x1C, 0x7F, 0xFF, 0xE1, 0xC3, 0x87,
  0x0E, 0x1C, 0x38, 0x70, 0xE1, 0xC3, 0x87, 0x0E, 0x3F, 0x8F, 0xFB, 0xEF,
  0xF8, 0x7E, 0x0F, 0xC1, 0xC0, 0x38, 0x0F, 0x03, 0xC0, 0xF0, 0x7C, 0x1F,
  0x07, 0x80, 0xE0, 0x3F, 0xFF, 0xFF, 0xFF, 0xE0, 0x3F, 0x8F, 0xFB, 0xCF,
  0xF0, 0xFE, 0x1E, 0x03, 0xC0, 0x70, 0x7C, 0x0F, 0xC0, 0xFC, 0x03, 0x80,
  0x7E, 0x0F, 0xC1, 0xFC, 0xFB, 0xFE, 0x3F, 0x80, 0x80, 0x07, 0xC0, 0x7C,
  0x0F, 0xC0, 0xFC, 0x1F, 0xC3, 0xBC, 0x33, 0xC7, 0x3C, 0x63, 0xCE, 0x3C,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x3C, 0x03, 0xC0, 0x3C, 0x03, 0xC0, 0x3F,
  0xEF, 0xFD, 0xFF, 0xB8, 0x06, 0x00, 0xC0, 0x1F, 0xE7, 0xFE, 0xF1, 0xE0,
  0x1C, 0x03, 0x80, 0x70, 0x0F, 0xC1, 0xFC, 0xFB, 0xFE, 0x3F, 0x80, 0x80,
  0x1F, 0x87, 0xF9, 0xE7, 0xB8, 0x7E, 0x01, 0xC0, 0x3B, 0xE7, 0xFE, 0xFB,
  0xFE, 0x1F, 0x83, 0xF0, 0x7E, 0x0F, 0xE1, 0xDE, 0xFB, 0xFE, 0x3F, 0x80,
  0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x0E, 0x01, 0xC0, 0x3C, 0x03, 0x80,
  0x70, 0x0F, 0x00, 0xE0, 0x0E, 0x01, 0xE0, 0x1C, 0x01, 0xC0, 0x1C, 0x03,
  0xC0, 0x3C, 0x00, 0x3F, 0x87, 0xFC, 0xF9, 0xEE, 0x0E, 0xE0, 0xEE, 0x0E,
  0x71, 0xC3, 0xF8, 0x7F, 0xCF, 0x1E, 0xE0, 0xEE, 0x0F, 0xE0, 0xFE, 0x0E,
  0xF1, 0xE7, 0xFC, 0x3F, 0x80, 0x40, 0x3F, 0x0F, 0xFB, 0xEF, 0x70, 0xFE,
  0x0F, 0xC1, 0xF8, 0x3F, 0x0F, 0xF3, 0xEF, 0xFC, 0xFB, 0x80, 0x70, 0x0F,
  0xC3, 0xFE, 0xF3, 0xFE, 0x3F, 0x80, 0x80, 0xFF, 0x80, 0x00, 0xFF, 0xF0,
  0xFF, 0x80, 0x00, 0xFF, 0xF2, 0xDE, 0x00, 0x70, 0x1F, 0x0F, 0xE7, 0xF0,
  0xF8, 0x0E, 0x00, 0xFC, 0x03, 0xF8, 0x0F, 0xE0, 0x1F, 0x00, 0x30, 0xFF,
  0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
  0xF0, 0xC0, 0x0F, 0x80, 0x7F, 0x00, 0xFC, 0x03, 0xF0, 0x07, 0x03, 0xF1,
  0xFC, 0xFE, 0x0F, 0x80, 0xC0, 0x00, 0x1F, 0x0F, 0xF3, 0xFF, 0x78, 0xFE,
  0x0F, 0xC1, 0xC0, 0x38, 0x0F, 0x03, 0xE0, 0xF8, 0x3C, 0x07, 0x00, 0xE0,
  0x00, 0x03, 0x80, 0x70, 0x0E, 0x01, 0xC0, 0x00, 0xFC, 0x00, 0x0F, 0xFE,
  0x00, 0xF0, 0x3C, 0x07, 0x00, 0x38, 0x38, 0x00, 0x30, 0xC0, 0x00, 0xE6,
  0x0F, 0xF1, 0x98, 0x73, 0xC7, 0xC3, 0x87, 0x0F, 0x0C, 0x1C, 0x3C, 0x30,
  0x61, 0xF1, 0xC1, 0x86, 0xC7, 0x0E, 0x1B, 0x1C, 0x38, 0xEC, 0x3B, 0xEF,
  0x38, 0xFD, 0xF8, 0x70, 0xC1, 0x80, 0xE0, 0x00, 0x01, 0xC0, 0x10, 0x03,
  0xFF, 0xC0, 0x03, 0xFF, 0x00, 0x03, 0xC0, 0x07, 0xC0, 0x07, 0xE0, 0x07,
  0xE0, 0x0F, 0xE0, 0x0E, 0xF0, 0x0E, 0xF0, 0x1E, 0x70, 0x1C, 0x78, 0x1C,
  0x78, 0x3C, 0x38, 0x3F, 0xFC, 0x3F, 0xFC, 0x7F, 0xFC, 0x70, 0x1E, 0xF0,
  0x1E, 0xF0, 0x0E, 0xE0, 0x0F, 0xFF, 0x03, 0xFF, 0xCF, 0xFF, 0xBC, 0x7E,
  0xF0, 0x3B, 0xC0, 0xEF, 0x03, 0xBF, 0xFE, 0xFF, 0xE3, 0xFF, 0xCF, 0x0F,
  0xBC, 0x0F, 0xF0, 0x1F, 0xC0, 0xFF, 0x03, 0xFF, 0xFE, 0xFF, 0xFB, 0xFF,
  0x80, 0x03, 0xC0, 0x1F, 0xF0, 0xFF, 0xF1, 0xF1, 0xE7, 0x81, 0xEF, 0x01,
  0xFC, 0x00, 0x78, 0x00, 0xF0, 0x01, 0xE0, 0x03, 0xC0, 0x07, 0x80, 0x0F,
  0x00, 0xEF, 0x01, 0xDE, 0x07, 0x9F, 0xFE, 0x1F, 0xFC, 0x1F, 0xE0, 0x04,
  0x00, 0xFE, 0x03, 0xFF, 0x8F, 0xFF, 0x38, 0x7E, 0xE0, 0x7B, 0x80, 0xFE,
  0x03, 0xF8, 0x07, 0xE0, 0x1F, 0x80, 0x7E, 0x01, 0xF8, 0x07, 0xE0, 0x3F,
  0x80, 0xFE, 0x07, 0xBF, 0xFE, 0xFF, 0xF3, 0xFF, 0x00, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xE0, 0x0F, 0x00, 0x78, 0x03, 0xC0, 0x1F, 0xFE, 0xFF, 0xF7,
  0xFF, 0xBC, 0x01, 0xE0, 0x0F, 0x00, 0x78, 0x03, 0xC0, 0x1F, 0xFF, 0xFF,
  0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0xE0, 0x0E, 0x00,
  0xE0, 0x0F, 0xFE, 0xFF, 0xEF, 0xFE, 0xE0, 0x0E, 0x00, 0xE0, 0x0E, 0x00,
  0xE0, 0x0E, 0x00, 0xE0, 0x0E, 0x00, 0x03, 0xE0, 0x0F, 0xF8, 0x1F, 0xFC,
  0x3E, 0x3E, 0x78, 0x0F, 0x70, 0x0F, 0xF0, 0x00, 0xF0, 0x00, 0xF0, 0x00,
  0xF0, 0x7F, 0xF0, 0x7F, 0xF0, 0x7F, 0xF0, 0x07, 0x78, 0x0F, 0x7C, 0x1F,
  0x3F, 0xFF, 0x1F, 0xFB, 0x0F, 0xF3, 0xE0, 0x3F, 0x80, 0xFE, 0x03, 0xF8,
  0x0F, 0xE0, 0x3F, 0x80, 0xFE, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE,
  0x03, 0xF8, 0x0F, 0xE0, 0x3F, 0x80, 0xFE, 0x03, 0xF8, 0x0F, 0xE0, 0x3F,
  0x80, 0xF0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x01, 0xE0, 0x3C,
  0x07, 0x80, 0xF0, 0x1E, 0x03, 0xC0, 0x78, 0x0F, 0x01, 0xE0, 0x3C, 0x07,
  0x80, 0xFE, 0x1F, 0xC3, 0xF8, 0x7F, 0xFE, 0xFF, 0xCF, 0xF0, 0x00, 0x00,
  0xE0, 0x3D, 0xC0, 0xFB, 0x83, 0xE7, 0x07, 0x8E, 0x1E, 0x1C, 0x78, 0x39,
  0xE0, 0x77, 0x80, 0xFF, 0x01, 0xFF, 0x03, 0xFE, 0x07, 0x9E, 0x0E, 0x1E,
  0x1C, 0x1E, 0x38, 0x3C, 0x70, 0x3C, 0xE0, 0x3D, 0xC0, 0x3C, 0xF0, 0x0F,
  0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F,
  0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0xFF, 0xFF, 0xFF,
  0xFF, 0xF8, 0x1F, 0xFC, 0x0F, 0xFE, 0x07, 0xFF, 0x83, 0xFF, 0xC3, 0xFF,
  0xE1, 0xFF, 0xB0, 0xFF, 0xDC, 0x6F, 0xEE, 0x77, 0xF7, 0x3B, 0xF9, 0x9D,
  0xFC, 0xCC, 0xFE, 0x76, 0x7F, 0x3F, 0x3F, 0x8F, 0x9F, 0xC7, 0xCF, 0xE3,
  0xC7, 0xF1, 0xE3, 0xC0, 0xE0, 0x3F, 0xC0, 0xFF, 0x03, 0xFE, 0x0F, 0xFC,
  0x3F, 0xF0, 0xFE, 0xE3, 0xFB, 0x8F, 0xE7, 0x3F, 0x9E, 0xFE, 0x3B, 0xF8,
  0xFF, 0xE1, 0xFF, 0x83, 0xFE, 0x0F, 0xF8, 0x1F, 0xE0, 0x7F, 0x80, 0xF0,
  0x03, 0xE0, 0x07, 0xFC, 0x07, 0xFF, 0x07, 0xCF, 0xC7, 0x81, 0xF3, 0xC0,
  0x7B, 0xC0, 0x1D, 0xE0, 0x0F, 0xF0, 0x07, 0xF8, 0x03, 0xFC, 0x01, 0xFE,
  0x00, 0xFF, 0x00, 0x73, 0xC0, 0x79, 0xF0, 0x7C, 0x7F, 0xFC, 0x1F, 0xFC,
  0x07, 0xFC, 0x00, 0x20, 0x00, 0xFF, 0x07, 0xFF, 0x3F, 0xFD, 0xC3, 0xFE,
  0x07, 0xF0, 0x1F, 0x80, 0xFC, 0x0F, 0xE0, 0xFF, 0xFF, 0xBF, 0xF9, 0xFF,
  0x0E, 0x00, 0x70, 0x03, 0x80, 0x1C, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x03,
  0xE0, 0x07, 0xFC, 0x07, 0xFF, 0x07, 0xCF, 0xC7, 0x80, 0xF3, 0xC0, 0x7B,
  0xC0, 0x1F, 0xE0, 0x0F, 0xF0, 0x07, 0xF8, 0x03, 0xFC, 0x01, 0xFE, 0x04,
  0xFF, 0x07, 0x73, 0xC3, 0xF9, 0xF0, 0xFC, 0x7F, 0xFC, 0x1F, 0xFF, 0x07,
  0xFF, 0xC0, 0x20, 0xC0, 0xFF, 0x83, 0xFF, 0xCF, 0xFF, 0xBC, 0x3F, 0xF0,
  0x3F, 0xC0, 0xFF, 0x03, 0xFC, 0x0F, 0xFF, 0xFB, 0xFF, 0x8F, 0xFF, 0xBC,
  0x1E, 0xF0, 0x3B, 0xC0, 0xEF, 0x03, 0xBC, 0x0E, 0xF0, 0x3F, 0xC0, 0xF0,
  0x0F, 0x80, 0xFF, 0xC7, 0xFF, 0xBE, 0x1E, 0xF0, 0x3B, 0xC0, 0xFF, 0x00,
  0x3F, 0x80, 0x7F, 0xE0, 0xFF, 0xE0, 0x3F, 0xC0, 0x0F, 0x00, 0x1F, 0x80,
  0x7F, 0x03, 0xFF, 0x1F, 0x7F, 0xF8, 0xFF, 0xC0, 0x00, 0x00, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x03, 0x80, 0x0E, 0x00, 0x38, 0x00, 0xE0,
  0x03, 0x80, 0x0E, 0x00, 0x38, 0x00, 0xE0, 0x03, 0x80, 0x0E, 0x00, 0x38,
  0x00, 0xE0, 0x03, 0x80, 0x0E, 0x00, 0xE0, 0x3F, 0x80, 0xFE, 0x03, 0xF8,
  0x0F, 0xE0, 0x3F, 0x80, 0xFE, 0x03, 0xF8, 0x0F, 0xE0, 0x3F, 0x80, 0xFE,
  0x03, 0xF8, 0x0F, 0xE0, 0x3F, 0xC0, 0xFF, 0x07, 0x9F, 0xFE, 0x7F, 0xF0,
  0x7F, 0x80, 0x20, 0x00, 0xE0, 0x1F, 0xC0, 0x3B, 0xC0, 0xF3, 0x81, 0xE7,
  0x03, 0x8F, 0x0F, 0x0E, 0x1C, 0x1C, 0x38, 0x3C, 0x70, 0x39, 0xC0, 0x73,
  0x80, 0xE7, 0x00, 0xFC, 0x01, 0xF8, 0x03, 0xF0, 0x03, 0xC0, 0x07, 0x80,
  0x0F, 0x00, 0xF0, 0x38, 0x1D, 0xC1, 0xE0, 0xF7, 0x87, 0xC3, 0xDE, 0x1F,
  0x0F, 0x78, 0x7C, 0x38, 0xE3, 0xB0, 0xE3, 0x8E, 0xC7, 0x8F, 0x3B, 0x9C,
  0x1C, 0xEE, 0x70, 0x73, 0x39, 0xC1, 0xDC, 0x67, 0x07, 0x71, 0xB8, 0x0F,
  0xC7, 0xE0, 0x3E, 0x1F, 0x80, 0xF8, 0x3E, 0x01, 0xE0, 0xF0, 0x07, 0x83,
  0xC0, 0x1E, 0x0F, 0x00, 0xF0, 0x3D, 0xF0, 0x79, 0xE1, 0xE1, 0xE3, 0xC3,
  0xCF, 0x03, 0xFC, 0x07, 0xF8, 0x07, 0xE0, 0x07, 0x80, 0x0F, 0x00, 0x3F,
  0x00, 0x7F, 0x01, 0xFE, 0x07, 0x9E, 0x0F, 0x3C, 0x3C, 0x3C, 0xF8, 0x3D,
  0xE0, 0x78, 0xF0, 0x1F, 0xE0, 0x79, 0xE0, 0xF3, 0xC3, 0xC3, 0xC7, 0x87,
  0x9E, 0x07, 0x3C, 0x0F, 0x70, 0x0F, 0xE0, 0x1F, 0x80, 0x1F, 0x00, 0x3C,
  0x00, 0x78, 0x00, 0xF0, 0x01, 0xE0, 0x03, 0xC0, 0x07, 0x80, 0x0F, 0x00,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x80,
  0x78, 0x07, 0x80, 0x78, 0x07, 0x80, 0x7C, 0x03, 0xC0, 0x3C, 0x03, 0xC0,
  0x1F, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xFF, 0xFF, 0xCE, 0x73, 0x9C, 0xE7,
  0x39, 0xCE, 0x73, 0x9C, 0xE7, 0x39, 0xCF, 0xFF, 0xE0, 0xC1, 0x81, 0x02,
  0x06, 0x04, 0x08, 0x18, 0x30, 0x20, 0x60, 0xC0, 0x81, 0x83, 0x02, 0x06,
  0xFF, 0xFF, 0xC7, 0x1C, 0x71, 0xC7, 0x1C, 0x71, 0xC7, 0x1C, 0x71, 0xC7,
  0x1C, 0x71, 0xC7, 0xFF, 0xFF, 0xC0, 0x0F, 0x00, 0xF0, 0x0F, 0x01, 0xF8,
  0x1B, 0x83, 0x9C, 0x39, 0xC3, 0x0C, 0x70, 0xE7, 0x0E, 0xE0, 0x70, 0xFF,
  0xFF, 0xFF, 0xFC, 0x71, 0x86, 0x3F, 0x87, 0xFC, 0xFF, 0xEE, 0x1E, 0x01,
  0xE0, 0xFE, 0x7F, 0xEF, 0x8E, 0xE1, 0xEE, 0x1E, 0xF3, 0xEF, 0xFE, 0x7E,
  0xE1, 0x00, 0xF0, 0x07, 0x80, 0x3C, 0x01, 0xE0, 0x0F, 0x00, 0x7B, 0xE3,
  0xFF, 0x9F, 0xFE, 0xF8, 0xF7, 0x83, 0xFC, 0x1F, 0xE0, 0xFF, 0x07, 0xF8,
  0x3F, 0xC1, 0xDF, 0x9E, 0xFF, 0xE7, 0xFE, 0x00, 0x40, 0x1F, 0x83, 0xFC,
  0x7F, 0xEF, 0x0E, 0xE0, 0xEE, 0x00, 0xE0, 0x0E, 0x00, 0xE0, 0x0F, 0x0E,
  0x79, 0xE7, 0xFC, 0x3F, 0x80, 0x00, 0x00, 0x70, 0x07, 0x00, 0x70, 0x07,
  0x00, 0x71, 0xE7, 0x3F, 0xF7, 0xFF, 0xF0, 0xFE, 0x0F, 0xE0, 0x7E, 0x07,
  0xE0, 0x7E, 0x0F, 0xF0, 0xF7, 0x9F, 0x7F, 0xF3, 0xF7, 0x00, 0x00, 0x1F,
  0x07, 0xFC, 0x7B, 0xEE, 0x0E, 0xE0, 0xEF, 0xFE, 0xFF, 0xFF, 0xFF, 0xE0,
  0x0E, 0x0E, 0xF1, 0xE7, 0xFC, 0x3F, 0x80, 0x40, 0x00, 0x1E, 0x3E, 0x3C,
  0x3C, 0xFF, 0xFF, 0xFF, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C, 0x3C,
  0x3C, 0x3C, 0x1E, 0x73, 0xF7, 0x7F, 0xFF, 0x0F, 0xF0, 0xFE, 0x07, 0xE0,
  0x7E, 0x07, 0xE0, 0x7F, 0x0F, 0x79, 0xF7, 0xFF, 0x3F, 0x70, 0x07, 0x00,
  0x7F, 0x0F, 0x7F, 0xE3, 0xFC, 0xE0, 0x1C, 0x03, 0x80, 0x70, 0x0E, 0x01,
  0xDF, 0x3F, 0xF7, 0xFF, 0xF1, 0xFC, 0x1F, 0x83, 0xF0, 0x7E, 0x0F, 0xC1,
  0xF8, 0x3F, 0x07, 0xE0, 0xFC, 0x1C, 0xFF, 0xF1, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFC, 0x39, 0xCE, 0x70, 0x1C, 0xE7, 0x39, 0xCE, 0x73, 0x9C, 0xE7, 0x39,
  0xCE, 0x7F, 0xFF, 0xC0, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F,
  0x0E, 0xF1, 0xEF, 0x3C, 0xF7, 0x8F, 0xF0, 0xFF, 0x0F, 0xF0, 0xFF, 0x8F,
  0x3C, 0xF3, 0xCF, 0x1E, 0xF1, 0xEF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFC, 0xF7, 0xCF, 0x9F, 0xFF, 0xFB, 0xFF, 0xFF, 0xF8, 0x78, 0xFF,
  0x0E, 0x1F, 0xE1, 0xC3, 0xFC, 0x38, 0x7F, 0x87, 0x0F, 0xF0, 0xE1, 0xFE,
  0x1C, 0x3F, 0xC3, 0x87, 0xF8, 0x70, 0xFF, 0x0E, 0x1E, 0xEF, 0x9F, 0xFB,
  0xFF, 0xF8, 0xFE, 0x0F, 0xC1, 0xF8, 0x3F, 0x07, 0xE0, 0xFC, 0x1F, 0x83,
  0xF0, 0x7E, 0x0E, 0x1F, 0x81, 0xFF, 0x1F, 0xFD, 0xE1, 0xEF, 0x07, 0x70,
  0x3F, 0x81, 0xFC, 0x0F, 0xE0, 0x7F, 0x83, 0x9E, 0x3C, 0xFF, 0xC3, 0xFC,
  0x01, 0x00, 0xF7, 0xC7, 0xFF, 0x3F, 0xFD, 0xF1, 0xEF, 0x07, 0xF8, 0x3F,
  0xC1, 0xFE, 0x0F, 0xF0, 0x7F, 0x83, 0xBE, 0x3D, 0xFF, 0xCF, 0x7C, 0x78,
  0x83, 0xC0, 0x1E, 0x00, 0xF0, 0x07, 0x80, 0x00, 0x1E, 0x77, 0xF7, 0x7F,
  0xFF, 0x0F, 0xE0, 0xFE, 0x07, 0xE0, 0x7E, 0x07, 0xE0, 0xFF, 0x0F, 0xF9,
  0xF7, 0xFF, 0x3F, 0x70, 0x47, 0x00, 0x70, 0x07, 0x00, 0x70, 0x07, 0xEF,
  0xFF, 0xFF, 0x8E, 0x1C, 0x38, 0x70, 0xE1, 0xC3, 0x87, 0x0E, 0x00, 0x3F,
  0x8F, 0xFB, 0xEF, 0xF8, 0x7F, 0x01, 0xFE, 0x1F, 0xF0, 0xFF, 0x01, 0xFC,
  0x1F, 0xC3, 0xFF, 0xF7, 0xFC, 0x08, 0x00, 0x38, 0x70, 0xE7, 0xFF, 0xFF,
  0xCE, 0x1C, 0x38, 0x70, 0xE1, 0xC3, 0x87, 0x0F, 0x8F, 0x04, 0xF0, 0x7F,
  0x07, 0xF0, 0x7F, 0x07, 0xF0, 0x7F, 0x07, 0xF0, 0x7F, 0x07, 0xF0, 0x7F,
  0x0F, 0x79, 0xF7, 0xFF, 0x3F, 0x70, 0x80, 0xF0, 0x7B, 0x83, 0x9E, 0x1C,
  0x71, 0xE3, 0x8E, 0x1E, 0x70, 0x73, 0x83, 0xB8, 0x1D, 0xC0, 0x7E, 0x03,
  0xE0, 0x1F, 0x00, 0x78, 0x00, 0xF0, 0xE1, 0xDC, 0x78, 0x77, 0x1F, 0x3D,
  0xC7, 0xCE, 0x79, 0xF3, 0x8E, 0xEC, 0xE3, 0xBB, 0x78, 0xEC, 0xFC, 0x1F,
  0x3F, 0x07, 0xCF, 0xC1, 0xF1, 0xE0, 0x7C, 0x78, 0x0E, 0x1E, 0x00, 0x78,
  0xF3, 0xC7, 0x8F, 0x78, 0x3B, 0x81, 0xFC, 0x07, 0xC0, 0x1E, 0x01, 0xF0,
  0x1F, 0xC0, 0xEF, 0x0F, 0x78, 0xF1, 0xE7, 0x87, 0x80, 0xF0, 0x7B, 0x83,
  0x9E, 0x1C, 0xF1, 0xE3, 0x8E, 0x1E, 0x70, 0x73, 0x83, 0xB8, 0x1D, 0xC0,
  0x7E, 0x03, 0xE0, 0x1F, 0x00, 0x78, 0x03, 0x80, 0x1C, 0x01, 0xE0, 0x3E,
  0x01, 0xE0, 0x00, 0xFF, 0xFF, 0xFF, 0xFC, 0x1E, 0x0F, 0x83, 0xC1, 0xE0,
  0xF0, 0x78, 0x3C, 0x0F, 0xFF, 0xFF, 0xFF, 0xC0, 0x06, 0x3C, 0xF9, 0xC3,
  0x87, 0x0E, 0x1C, 0x38, 0x73, 0xC7, 0x0F, 0x07, 0x0E, 0x1C, 0x38, 0x70,
  0xE1, 0xC3, 0xE7, 0xC7, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0xC3,
  0xCF, 0x0C, 0x38, 0xE3, 0x8E, 0x38, 0xE3, 0xC7, 0x3C, 0xE3, 0x8E, 0x38,
  0xE3, 0x8E, 0xF3, 0xCE, 0x00, 0x10, 0x0F, 0x85, 0xBD, 0xE1, 0xF0, 0x08,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80, 0xFC,
  0x07, 0xE0, 0x3F, 0x01, 0xF8, 0x0F, 0xC0, 0x7E, 0x03, 0xF0, 0x1F, 0x80,
  0xFC, 0x07, 0xFF, 0xFF, 0xFF, 0xC0 };

const GFXglyph ubitxGlyphs[] PROGMEM = {
  {     0,  13,  18,  17,    2,  -17 },   // 0x14
  {    30,  13,  18,  17,    2,  -17 },   // 0x15
  {    60,  13,  18,  17,    2,  -17 },   // 0x16
  {    90,  13,  18,  17,    2,  -17 },   // 0x17
  {   120,  13,  18,  17,    2,  -17 },   // 0x18
  {   150,  13,  18,  17,    2,  -17 },   // 0x19
  {   180,  13,  18,  17,    2,  -17 },   // 0x1A
  {   210,  13,  18,  17,    2,  -17 },   // 0x1B
  {   240,  13,  18,  17,    2,  -17 },   // 0x1C
  {   270,  13,  18,  17,    2,  -17 },   // 0x1D
  {   300,  13,  18,  17,    2,  -17 },   // 0x1E
  {   330,  13,  18,  17,    2,  -17 },   // 0x1F
  {   360,   0,   0,   7,    0,    1 },   // 0x20 ' '
  {   360,   3,  17,   8,    3,  -16 },   // 0x21 '!'
  {   367,   9,   7,  11,    1,  -17 },   // 0x22 '"'
  {   375,  13,  18,  13,    0,  -16 },   // 0x23 '#'
  {   405,  12,  21,  13,    1,  -17 },   // 0x24 '$'
  {   437,  20,  17,  21,    1,  -16 },   // 0x25 '%'
  {   480,  16,  18,  17,    1,  -16 },   // 0x26 '&'
  {   516,   4,   7,   6,    1,  -17 },   // 0x27 '''
  {   520,   6,  23,   8,    1,  -17 },   // 0x28 '('
  {   538,   6,  23,   8,    1,  -17 },   // 0x29 ')'
  {   556,   8,   8,   9,    1,  -17 },   // 0x2A '*'
  {   564,  12,  11,  14,    1,  -10 },   // 0x2B '+'
  {   581,   3,   8,   7,    2,   -3 },   // 0x2C ','
  {   584,   6,   3,   8,    1,   -7 },   // 0x2D '-'
  {   587,   3,   4,   7,    2,   -3 },   // 0x2E '.'
  {   589,   7,  17,   7,    0,  -16 },   // 0x2F '/'
  {   604,  11,  18,  13,    1,  -16 },   // 0x30 '0'
  {   629,   7,  17,  13,    2,  -16 },   // 0x31 '1'
  {   644,  11,  17,  13,    1,  -16 },   // 0x32 '2'
  {   668,  11,  18,  13,    1,  -16 },   // 0x33 '3'
  {   693,  12,  17,  13,    1,  -16 },   // 0x34 '4'
  {   719,  11,  18,  13,    1,  -16 },   // 0x35 '5'
  {   744,  11,  18,  13,    1,  -16 },   // 0x36 '6'
  {   769,  12,  17,  13,    1,  -16 },   // 0x37 '7'
  {   795,  12,  18,  13,    1,  -16 },   // 0x38 '8'
  {   822,  11,  18,  13,    1,  -16 },   // 0x39 '9'
  {   847,   3,  12,   8,    3,  -11 },   // 0x3A ':'
  {   852,   3,  16,   8,    3,  -11 },   // 0x3B ';'
  {   858,  12,  11,  14,    1,  -10 },   // 0x3C '<'
  {   875,  12,   9,  14,    1,   -9 },   // 0x3D '='
  {   889,  12,  11,  14,    1,  -10 },   // 0x3E '>'
  {   906,  11,  18,  15,    2,  -17 },   // 0x3F '?'
  {   931,  22,  21,  23,    1,  -17 },   // 0x40 '@'
  {   989,  16,  18,  17,    1,  -17 },   // 0x41 'A'
  {  1025,  14,  18,  17,    2,  -17 },   // 0x42 'B'
  {  1057,  15,  19,  17,    1,  -17 },   // 0x43 'C'
  {  1093,  14,  18,  17,    2,  -17 },   // 0x44 'D'
  {  1125,  13,  18,  16,    2,  -17 },   // 0x45 'E'
  {  1155,  12,  18,  15,    2,  -17 },   // 0x46 'F'
  {  1182,  16,  18,  19,    1,  -17 },   // 0x47 'G'
  {  1218,  14,  18,  17,    2,  -17 },   // 0x48 'H'
  {  1250,   3,  18,   7,    2,  -17 },   // 0x49 'I'
  {  1257,  11,  19,  13,    1,  -17 },   // 0x4A 'J'
  {  1284,  15,  18,  17,    2,  -17 },   // 0x4B 'K'
  {  1318,  12,  18,  15,    2,  -17 },   // 0x4C 'L'
  {  1345,  17,  18,  20,    2,  -17 },   // 0x4D 'M'
  {  1384,  14,  18,  17,    2,  -17 },   // 0x4E 'N'
  {  1416,  17,  19,  19,    1,  -17 },   // 0x4F 'O'
  {  1457,  13,  18,  16,    2,  -17 },   // 0x50 'P'
  {  1487,  17,  19,  19,    1,  -17 },   // 0x51 'Q'
  {  1528,  14,  18,  17,    2,  -17 },   // 0x52 'R'
  {  1560,  14,  19,  16,    1,  -17 },   // 0x53 'S'
  {  1594,  14,  18,  15,    0,  -17 },   // 0x54 'T'
  {  1626,  14,  19,  17,    2,  -17 },   // 0x55 'U'
  {  1660,  15,  18,  16,    1,  -17 },   // 0x56 'V'
  {  1694,  22,  18,  23,    0,  -17 },   // 0x57 'W'
  {  1744,  15,  18,  16,    1,  -17 },   // 0x58 'X'
  {  1778,  15,  18,  16,    1,  -17 },   // 0x59 'Y'
  {  1812,  13,  18,  15,    1,  -17 },   // 0x5A 'Z'
  {  1842,   5,  23,   8,    2,  -17 },   // 0x5B '['
  {  1857,   7,  17,   7,    0,  -16 },   // 0x5C '\'
  {  1872,   6,  23,   8,    0,  -17 },   // 0x5D ']'
  {  1890,  12,  11,  14,    1,  -16 },   // 0x5E '^'
  {  1907,  15,   2,  13,   -1,    4 },   // 0x5F '_'
  {  1911,   5,   3,   8,    0,  -17 },   // 0x60 '`'
  {  1913,  12,  14,  13,    1,  -12 },   // 0x61 'a'
  {  1934,  13,  19,  15,    1,  -17 },   // 0x62 'b'
  {  1965,  12,  14,  13,    1,  -12 },   // 0x63 'c'
  {  1986,  12,  19,  15,    1,  -17 },   // 0x64 'd'
  {  2015,  12,  14,  13,    1,  -12 },   // 0x65 'e'
  {  2036,   8,  18,   8,    0,  -17 },   // 0x66 'f'
  {  2054,  12,  18,  15,    1,  -12 },   // 0x67 'g'
  {  2081,  11,  18,  15,    2,  -17 },   // 0x68 'h'
  {  2106,   3,  18,   7,    2,  -17 },   // 0x69 'i'
  {  2113,   5,  23,   7,    0,  -17 },   // 0x6A 'j'
  {  2128,  12,  18,  13,    1,  -17 },   // 0x6B 'k'
  {  2155,   3,  18,   7,    2,  -17 },   // 0x6C 'l'
  {  2162,  19,  13,  21,    1,  -12 },   // 0x6D 'm'
  {  2193,  11,  13,  15,    2,  -12 },   // 0x6E 'n'
  {  2211,  13,  14,  15,    1,  -12 },   // 0x6F 'o'
  {  2234,  13,  18,  15,    1,  -12 },   // 0x70 'p'
  {  2264,  12,  18,  15,    1,  -12 },   // 0x71 'q'
  {  2291,   7,  13,   9,    2,  -12 },   // 0x72 'r'
  {  2303,  11,  14,  13,    1,  -12 },   // 0x73 's'
  {  2323,   7,  17,   8,    0,  -15 },   // 0x74 't'
  {  2338,  12,  14,  15,    1,  -12 },   // 0x75 'u'
  {  2359,  13,  13,  13,    0,  -12 },   // 0x76 'v'
  {  2381,  18,  13,  19,    0,  -12 },   // 0x77 'w'
  {  2411,  13,  13,  13,    0,  -12 },   // 0x78 'x'
  {  2433,  13,  18,  13,    0,  -12 },   // 0x79 'y'
  {  2463,  10,  13,  12,    1,  -12 },   // 0x7A 'z'
  {  2480,   7,  23,   9,    1,  -17 },   // 0x7B '{'
  {  2501,   2,  23,   7,    2,  -17 },   // 0x7C '|'
  {  2507,   6,  23,   9,    2,  -17 },   // 0x7D '}'
  {  2525,  11,   5,  14,    1,   -7 },   // 0x7E '~'
  {  2532,  13,  18,  17,    2,  -17 } }; // 0x7F

const GFXfont ubitx_font PROGMEM = {
  (uint8_t  *)ubitxBitmaps,
  (GFXglyph *)ubitxGlyphs,
  0x14, 0x7F, 33 };

// Approx. 3325 bytes

// Color definitions
#define DISPLAY_BLACK       0x0000  ///<   0,   0,   0
#define DISPLAY_NAVY        0x000F  ///<   0,   0, 123
#define DISPLAY_DARKGREEN   0x03E0  ///<   0, 125,   0
#define DISPLAY_DARKCYAN    0x03EF  ///<   0, 125, 123
#define DISPLAY_MAROON      0x7800  ///< 123,   0,   0
#define DISPLAY_PURPLE      0x780F  ///< 123,   0, 123
#define DISPLAY_OLIVE       0x7BE0  ///< 123, 125,   0
#define DISPLAY_LIGHTGREY   0xC618  ///< 198, 195, 198
#define DISPLAY_DARKGREY    0x7BEF  ///< 123, 125, 123
#define DISPLAY_BLUE        0x001F  ///<   0,   0, 255
#define DISPLAY_GREEN       0x07E0  ///<   0, 255,   0
#define DISPLAY_CYAN        0x07FF  ///<   0, 255, 255
#define DISPLAY_RED         0xF800  ///< 255,   0,   0
#define DISPLAY_MAGENTA     0xF81F  ///< 255,   0, 255
#define DISPLAY_YELLOW      0xFFE0  ///< 255, 255,   0
#define DISPLAY_WHITE       0xFFFF  ///< 255, 255, 255
#define DISPLAY_ORANGE      0xFD20  ///< 255, 165,   0
#define DISPLAY_GREENYELLOW 0xAFE5  ///< 173, 255,  41
#define DISPLAY_PINK        0xFC18  ///< 255, 130, 198

#endif // _NANO_GUI_H_


