#pragma once
#include <Arduino.h>

#include "ssd1306commands.h"
#include "my_graphics.h"
#include "frames.h"
#include "bitmaps.h"


class my_graphics{
protected:
  uint8_t _dataPin, _clkPin, _DCpin, _CSpin, _RSTpin;
  void spi_transmit( uint8_t cmd );
public:
  my_graphics(uint8_t dataPin, uint8_t clkPin, uint8_t DCpin, uint8_t CSpin, uint8_t RSTpin);
  void begin();
  void setCMDtxMode();
  void setDATAtxMode();
  void clear();
  
  friend void frame::draw( my_graphics &_disp );
};
