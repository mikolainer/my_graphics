#pragma once
#include <Arduino.h>

class bitmap;
class my_graphics;

class frame{
private:
  bitmap** _objects;
  uint8_t _num_of_objects;
  friend void spi_transmit( uint8_t cmd );
public:
  frame( bitmap** ptr, uint8_t len );
  void draw( my_graphics &_disp );
};
