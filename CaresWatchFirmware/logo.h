#ifndef __LOGO_H__
#define __LOGO_H__

const unsigned char logo_bits [] PROGMEM = {
  // 'FABLAB DEFINITIVO, 128x64px
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0xfd, 0xe0, 0x00, 0x3f, 0xe1, 0xff, 0xfe, 0x00, 0x3f, 
  0xff, 0xff, 0xe0, 0x00, 0x01, 0xff, 0xff, 0xfd, 0xc0, 0x00, 0x1f, 0xc0, 0xff, 0xfc, 0x00, 0x0f, 
  0xff, 0xff, 0x80, 0x0c, 0x00, 0x7f, 0xff, 0xfd, 0xc0, 0x00, 0x3f, 0xc0, 0xff, 0xf8, 0x00, 0x07, 
  0xff, 0xfe, 0x00, 0x3f, 0x00, 0x1f, 0xff, 0xfd, 0x80, 0x00, 0x7f, 0x80, 0x7f, 0xf8, 0x00, 0x07, 
  0xff, 0xf8, 0x00, 0x7f, 0xc0, 0x07, 0xff, 0xfd, 0x87, 0xff, 0xff, 0x80, 0x7f, 0xf8, 0x7f, 0xc7, 
  0xff, 0xf0, 0x01, 0xff, 0xe0, 0x03, 0xff, 0xfd, 0x87, 0xff, 0xff, 0x08, 0x3f, 0xf8, 0x7f, 0xc3, 
  0xff, 0xe0, 0x03, 0xff, 0xf8, 0x01, 0xff, 0xfd, 0x87, 0xff, 0xff, 0x0c, 0x3f, 0xf8, 0x7f, 0xc3, 
  0xff, 0xc0, 0x00, 0xff, 0xfe, 0x00, 0xff, 0xfd, 0x87, 0xff, 0xfe, 0x1e, 0x1f, 0xf8, 0x7f, 0xc3, 
  0xff, 0x80, 0x00, 0x00, 0x3f, 0x80, 0x7f, 0xfd, 0x87, 0xff, 0xfe, 0x1e, 0x1f, 0xf8, 0x7f, 0xc3, 
  0xff, 0x00, 0x00, 0x00, 0x0f, 0xc0, 0x3f, 0xfd, 0x87, 0xff, 0xfc, 0x3e, 0x0f, 0xf8, 0x7f, 0x87, 
  0xfe, 0x02, 0x00, 0x00, 0x07, 0xf0, 0x1f, 0xfd, 0x80, 0x0f, 0xf8, 0x3f, 0x0f, 0xf8, 0x7e, 0x07, 
  0xfc, 0x0f, 0x80, 0x00, 0x03, 0xfc, 0x0f, 0xfd, 0x80, 0x07, 0xf8, 0x7f, 0x87, 0xf8, 0x40, 0x0f, 
  0xfc, 0x1f, 0xe0, 0x00, 0x03, 0xfe, 0x0f, 0xfd, 0x80, 0x0f, 0xf0, 0x7f, 0x87, 0xf8, 0x40, 0x0f, 
  0xfe, 0x7f, 0xe0, 0x00, 0x03, 0xff, 0x9f, 0xfd, 0x80, 0x0f, 0xf0, 0xff, 0xc3, 0xf8, 0x60, 0x07, 
  0xff, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xfb, 0xfd, 0x87, 0xff, 0xe0, 0x00, 0x03, 0xf8, 0x7f, 0x07, 
  0xf1, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xe3, 0xfd, 0x87, 0xff, 0xe0, 0x00, 0x01, 0xf8, 0x7f, 0x87, 
  0xf1, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xe1, 0xfd, 0x87, 0xff, 0xc0, 0x00, 0x01, 0xf8, 0x7f, 0xc3, 
  0xe1, 0xff, 0xf0, 0x00, 0x07, 0xff, 0xe1, 0xfd, 0x87, 0xff, 0xc0, 0x00, 0x00, 0xf8, 0x7f, 0xc3, 
  0xe1, 0xff, 0xf8, 0x00, 0x0f, 0xff, 0xe1, 0xfd, 0x87, 0xff, 0x87, 0xff, 0xf0, 0xf8, 0x7f, 0xc3, 
  0xe1, 0xff, 0xfa, 0x00, 0x3f, 0xff, 0xe0, 0xfd, 0x87, 0xff, 0x87, 0xff, 0xf8, 0x78, 0x7f, 0xc3, 
  0xc1, 0xff, 0xfa, 0xc1, 0xff, 0xff, 0xe0, 0xfd, 0x87, 0xff, 0x0f, 0xff, 0xf8, 0x78, 0x7f, 0x87, 
  0xc1, 0xff, 0xfa, 0xff, 0xff, 0xff, 0xe0, 0xfd, 0x87, 0xff, 0x0f, 0xff, 0xfc, 0x38, 0x00, 0x07, 
  0xc1, 0xff, 0xfa, 0xff, 0xff, 0xff, 0xe0, 0xfd, 0x87, 0xfe, 0x1f, 0xff, 0xfc, 0x3c, 0x00, 0x0f, 
  0xc1, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xe0, 0xfd, 0x87, 0xfe, 0x1f, 0x00, 0x7e, 0x3c, 0x00, 0x0f, 
  0xc1, 0xfe, 0x7e, 0xff, 0xff, 0xcf, 0x80, 0x7d, 0xcf, 0xff, 0x3f, 0x00, 0x3e, 0x3f, 0x00, 0x3f, 
  0xc1, 0xf8, 0x1e, 0xff, 0xfe, 0x02, 0x00, 0x7d, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xff, 
  0xc1, 0xf0, 0x07, 0xff, 0xfc, 0x00, 0x00, 0x7d, 0xff, 0xff, 0xfe, 0x1e, 0x1f, 0xff, 0xff, 0xff, 
  0xc1, 0xe0, 0x03, 0xff, 0xf8, 0x00, 0x00, 0x7d, 0xff, 0xff, 0xfc, 0x3f, 0x0f, 0xff, 0xff, 0xff, 
  0xc1, 0xe0, 0x01, 0xff, 0xf0, 0x00, 0x00, 0x7d, 0xff, 0xff, 0xf8, 0x7f, 0x8f, 0xff, 0xff, 0xff, 
  0xc1, 0xe0, 0x01, 0xff, 0xe0, 0x00, 0x00, 0x7d, 0xff, 0xff, 0xf8, 0x7f, 0x87, 0xff, 0xff, 0xff, 
  0xc1, 0xe0, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x7d, 0xff, 0xff, 0xf8, 0x7f, 0x87, 0xff, 0xff, 0xff, 
  0xc1, 0xe0, 0x00, 0xff, 0xc0, 0x00, 0x00, 0xfd, 0xff, 0xff, 0xf8, 0x7f, 0x8f, 0xff, 0xff, 0xff, 
  0xc1, 0xe0, 0x00, 0x7f, 0xc0, 0x00, 0x60, 0xfd, 0xff, 0xff, 0xfc, 0x7f, 0x0f, 0xff, 0xff, 0xff, 
  0xc1, 0xe0, 0x00, 0x7f, 0x80, 0x00, 0xe0, 0xfd, 0xff, 0xff, 0xfc, 0x3e, 0x1f, 0xff, 0xff, 0xff, 
  0xe1, 0xe0, 0x00, 0x3f, 0x80, 0x01, 0xe0, 0xfd, 0xff, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xff, 0xff, 
  0xe1, 0xf0, 0x00, 0x3f, 0x80, 0x01, 0xe1, 0xfd, 0xcf, 0xff, 0x3f, 0x00, 0x3f, 0x7f, 0x80, 0x7f, 
  0xe1, 0xf0, 0x00, 0x3f, 0x80, 0x03, 0xe1, 0xfd, 0x87, 0xfe, 0x1f, 0x00, 0x7e, 0x3e, 0x00, 0x1f, 
  0xe1, 0xf8, 0x00, 0x3f, 0x80, 0x03, 0xe1, 0xfd, 0x87, 0xfe, 0x1f, 0xff, 0xfc, 0x3c, 0x00, 0x0f, 
  0xf1, 0xfc, 0x00, 0x3f, 0x80, 0x07, 0xe3, 0xfd, 0x87, 0xff, 0x0f, 0xff, 0xfc, 0x38, 0x00, 0x07, 
  0xf1, 0xfc, 0x00, 0x7f, 0x80, 0x0f, 0xe3, 0xfd, 0x87, 0xff, 0x0f, 0xff, 0xf8, 0x78, 0x7f, 0x87, 
  0xf8, 0xfc, 0x00, 0x7f, 0xc0, 0x1f, 0xc7, 0xfd, 0x87, 0xff, 0x87, 0xff, 0xf8, 0x78, 0x7f, 0xc3, 
  0xf8, 0x3c, 0x00, 0xff, 0xe0, 0x3f, 0x07, 0xfd, 0x87, 0xff, 0x87, 0xff, 0xf0, 0xf8, 0x7f, 0xc3, 
  0xfc, 0x0c, 0x01, 0xff, 0xf9, 0xfe, 0x0f, 0xfd, 0x87, 0xff, 0xc0, 0x00, 0x00, 0xf8, 0x7f, 0xc3, 
  0xfe, 0x04, 0x01, 0xff, 0xff, 0xf8, 0x1f, 0xfd, 0x87, 0xff, 0xc0, 0x00, 0x01, 0xf8, 0x7f, 0xc3, 
  0xff, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x1f, 0xfd, 0x87, 0xff, 0xe0, 0x00, 0x01, 0xf8, 0x7f, 0xc3, 
  0xff, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x3f, 0xfd, 0x87, 0xff, 0xe0, 0x00, 0x03, 0xf8, 0x7f, 0x07, 
  0xff, 0x80, 0x01, 0xff, 0xff, 0x00, 0x7f, 0xfd, 0x87, 0xff, 0xf0, 0xff, 0xc3, 0xf8, 0x60, 0x07, 
  0xff, 0xc0, 0x01, 0xff, 0xfc, 0x00, 0xff, 0xfd, 0x87, 0xff, 0xf0, 0x7f, 0x87, 0xf8, 0x40, 0x0f, 
  0xff, 0xe0, 0x01, 0xff, 0xf0, 0x01, 0xff, 0xfd, 0x87, 0xff, 0xf8, 0x7f, 0x87, 0xf8, 0x40, 0x0f, 
  0xff, 0xf0, 0x00, 0xff, 0xe0, 0x03, 0xff, 0xfd, 0x87, 0xff, 0xf8, 0x7f, 0x0f, 0xf8, 0x60, 0x07, 
  0xff, 0xf0, 0x00, 0x7f, 0x80, 0x0f, 0xff, 0xfd, 0x87, 0xff, 0xfc, 0x3f, 0x0f, 0xf8, 0x7f, 0x87, 
  0xff, 0xf3, 0x00, 0x1e, 0x00, 0x3f, 0xff, 0xfd, 0x87, 0xff, 0xfc, 0x1e, 0x1f, 0xf8, 0x7f, 0xc3, 
  0xff, 0xf3, 0x00, 0x0c, 0x00, 0x7f, 0xff, 0xfd, 0x87, 0xff, 0xfe, 0x1e, 0x1f, 0xf8, 0x7f, 0xc3, 
  0xff, 0xf3, 0x10, 0x0c, 0x03, 0xff, 0xff, 0xfd, 0x87, 0xff, 0xfe, 0x0c, 0x3f, 0xf8, 0x7f, 0xc3, 
  0xff, 0xf3, 0x1f, 0x0c, 0x3f, 0xff, 0xff, 0xfd, 0x87, 0xff, 0xff, 0x0c, 0x3f, 0xf8, 0x7f, 0xc3, 
  0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x87, 0xff, 0xff, 0x00, 0x7f, 0xf8, 0x7f, 0xc7, 
  0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x87, 0xff, 0xff, 0x80, 0x7f, 0xf8, 0x7f, 0x87, 
  0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x80, 0x00, 0x3f, 0x80, 0xff, 0xf8, 0x00, 0x07, 
  0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xc0, 0x00, 0x1f, 0xc0, 0xff, 0xfc, 0x00, 0x0f, 
  0xff, 0xff, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xe0, 0x00, 0x3f, 0xe1, 0xff, 0xfe, 0x00, 0x1f, 
  0xff, 0xff, 0x9f, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

#endif
