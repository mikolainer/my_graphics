#include "bitmaps.h"

bitmap::bitmap( const uint8_t*  ptr, uint8_t sizeX, uint8_t sizeY, uint8_t num=1 ){
  _ptr = ptr;
  
  _Ymask = 8 - (sizeY % 8);
  _sizeY = sizeY + (_Ymask * (_Ymask < 8));
  _sizeX = sizeX;
  
  _posX = 0;
  _posY = 64 - _sizeY  + _Ymask;

  _num_of_bmps_inside = num;
  
  _visible = true;
  _selected = 0;
}

void bitmap::invert()                  { _inversed = !_inversed; }
void bitmap::Select( uint8_t n )       { _selected = n;          }
void bitmap::setVisible( boolean vis ) { _visible = vis;         }
void bitmap::setInversed( boolean inv ){ _inversed = inv; }

void bitmap::setPosition( uint8_t posX, uint8_t posY ){
  _posX = posX;
  _posY = 64 - _sizeY - posY + ( _Ymask * (_Ymask < 8) );
}

boolean bitmap::getVisible()      { return ( _visible ); }
boolean bitmap::not_pageAligned() { return ( true && (_posY%8) ); }

uint8_t bitmap::getByte( uint8_t x, uint8_t y, boolean secondHalf = false ){
  uint8_t out = 0;

  if ( _visible &&
        x >= _posX && x < _posX + _sizeX &&
        y >= (_posY/8) && y < (_posY/8) + (_sizeY/8)
     )
  {
    unsigned int ptrPos = ( ( x - _posX ) * (_sizeY/8) ) + ( y - (_posY/8) );
    out = pgm_read_byte( _ptr + ptrPos + ( _selected * _sizeX* _sizeY / 8 ) ) ^ _inversed * 0xFF ;
    
    if ( _Ymask<8 && y == (_posY/8) + (_sizeY/8) -1 ) out &= 0xFF << _Ymask;
    
    if ( secondHalf ) out >>=        ( _posY % 8 )   & (0xFF * ((_posY % 8)&& 1) );
                else  out <<= ( 8 -  ( _posY % 8 ))  & (0xFF * ((_posY % 8)&& 1) );
  }
  return out ;
}
