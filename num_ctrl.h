#pragma once
#include <Arduino.h>

class num_ctrl{
protected:
  uint8_t _range;
  bitmap** _dig;  // Less significant digit first
  
public:
  num_ctrl( uint8_t range,  bitmap** num_ptr );
  void hide ();
  void show ();
  void invert ();
  void setInversed( boolean inv );
  void setVal( uint8_t val );
};

num_ctrl::num_ctrl( uint8_t range,  bitmap** num_ptr ) { _range = range; _dig = num_ptr; }

void num_ctrl::hide (){ 
                      _dig[0]->setVisible( false );
  if ( _range > 9  )  _dig[1]->setVisible( false );
  if ( _range > 99 )  _dig[2]->setVisible( false );
}

void num_ctrl::show (){
                      _dig[0]->setVisible( true );
  if ( _range > 9  )  _dig[1]->setVisible( true );
  if ( _range > 99 )  _dig[2]->setVisible( true );
}

void num_ctrl::setVisible ( boolean vis ){
                      _dig[0]->setVisible( vis );
  if ( _range > 9  )  _dig[1]->setVisible( vis );
  if ( _range > 99 )  _dig[2]->setVisible( vis );
}

void num_ctrl::invert (){
                      _dig[0]->invert();
  if ( _range > 9  )  _dig[1]->invert();
  if ( _range > 99 )  _dig[2]->invert();
}

void num_ctrl::setInversed ( boolean inv ){
                      _dig[0]->setInversed(inv);
  if ( _range > 9  )  _dig[1]->setInversed(inv);
  if ( _range > 99 )  _dig[2]->setInversed(inv);
}

void num_ctrl::setVal ( uint8_t val ){ 
                      _dig[0]->Select(   val         % 10 );
  if ( _range > 9  )  _dig[1]->Select( ( val / 10 )  % 10 );
  if ( _range > 99 )  _dig[2]->Select( ( val / 100 ) % 10 );
}
