#include "frames.h"
#include "my_graphics.h"
#include "bitmaps.h"

frame::frame( bitmap** ptr, uint8_t len ){
  _objects = ptr;
  _num_of_objects = len;
}

void frame::draw( my_graphics &_disp ){
  for( int col = 0; col < 128; col++ ){
    for( unsigned int page = 7; page < 8; page-- ){
      int my_byte = 0;
      for ( uint8_t obj = 0; obj < _num_of_objects; obj++ ){
        if ( _objects[obj]->not_pageAligned() )
          my_byte |= _objects[obj]->getByte( col, page-1 );
        else
          my_byte |= _objects[obj]->getByte( col, page );
          
        if ( _objects[obj]->not_pageAligned() )
          my_byte |= _objects[obj]->getByte( col, page, true );
      }
      
      _disp.spi_transmit( my_byte );
    }
  }
}
