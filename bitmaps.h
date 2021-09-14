#pragma once
#include <Arduino.h>

class bitmap{
protected:
  const uint8_t*  _ptr;
  uint8_t   _Ymask;
  uint8_t   _sizeX, _sizeY;
  uint8_t   _posX,  _posY;
  uint8_t   _num_of_bmps_inside;
  uint8_t   _selected;
  boolean   _inversed, _visible;
  
public:
  bitmap( const uint8_t*  ptr, uint8_t sizeX, uint8_t sizeY, uint8_t num=1 );
  uint8_t getByte( uint8_t x, uint8_t y, boolean secondHalf = false );
  void setPosition( uint8_t posX, uint8_t posY );
  void setDispDraw();
  void setDispCut();
  void invert();
  void setInversed( boolean inv );
  void setVisible( boolean vis );
  void Select( uint8_t n );
  boolean get_displaymethod();
  boolean getVisible();
  boolean not_pageAligned();
};
