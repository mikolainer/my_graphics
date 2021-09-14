#include "my_graphics.h"
#include "ssd1306commands.h"

my_graphics::my_graphics(uint8_t dataPin, uint8_t clkPin, uint8_t DCpin, uint8_t CSpin, uint8_t RSTpin){
  _dataPin = dataPin;
  _clkPin = clkPin;
  _DCpin = DCpin;
  _CSpin = CSpin;
  _RSTpin = RSTpin;
}

void my_graphics::spi_transmit( uint8_t cmd ){
  for ( uint8_t mask = 0x80; mask; mask >>= 1 ){
    digitalWrite( _dataPin, cmd & mask );
    digitalWrite( _clkPin, HIGH );
    digitalWrite( _clkPin, LOW );
  }
}

void my_graphics::begin(){
  digitalWrite( _clkPin,  LOW );
  digitalWrite( _dataPin, LOW );
  digitalWrite( _CSpin,   LOW );
  digitalWrite( _RSTpin,  LOW );
  
  pinMode(_clkPin,  OUTPUT );
  pinMode(_dataPin, OUTPUT );
  pinMode(_RSTpin,  OUTPUT );
  pinMode(_DCpin,   OUTPUT );
  pinMode(_CSpin,   OUTPUT );
  
  digitalWrite( _RSTpin, HIGH );
  delay(20);
  
  // spi_transmit( START_COL_L(x) );
  
  this->setCMDtxMode();
  
  spi_transmit( SET_CHARGE_PUMP );
  spi_transmit( CHARGE_PUMP_ENABLE );
  
  spi_transmit( DISP_REMAP(1) );
  spi_transmit( COMSCAN_DIR_INVERSE(1) );
  
  spi_transmit( SET_MEMADDR_MODE );
  spi_transmit( VERT_MEMMODE );
  
  spi_transmit( SET_COL_ADRS );
  spi_transmit( 0 );
  spi_transmit( 127 );
  
  spi_transmit( SET_PAGE_ADRS );
  spi_transmit( 0 );
  spi_transmit( 7 );
  
  spi_transmit( DISP_SLEEP(0) );
  
  this->setDATAtxMode();
}

void my_graphics::setCMDtxMode(){
  digitalWrite( _DCpin, LOW );
}

void my_graphics::setDATAtxMode(){
  digitalWrite( _DCpin, HIGH );
}

void my_graphics::clear(){
  for (int i=0; i<1024; i++) spi_transmit( 0 );
}
