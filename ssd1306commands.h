 #pragma once
 /***  MINIMAL INIT  ****
 *  SET_CHARGE_PUMP     *
 *  CHARGE_PUMP_ENABLE  *
 *  DISP_SLEEP(0)          *
 ***********************/
    
    ////  fundamental cmds  ////
    ////////////////////////////
#define SET_CONTRAST        0x81
  // [0 - 255] contrast val

#define DISP_RAM_CONT(x)    ( 0xA5 - (x && 1) )
#define DISP_BLACK_IS(x)    ( 0xA6 + (x && 1) )
#define DISP_SLEEP(x)       ( 0xAF - (x && 1) )

    ////  scroll cmds  ////
    ///////////////////////
#define SET_HSCROLL_DIR(x)  ( 0x26 + (x && 1) )  // x=1 -> left
                                                 // x=0 -> right
  // [0x00]
  // [0-7] start page address
  /* [0-7] time interval (frames) between each scroll step
   *  0 -> 5 frames
   *  1 -> 64 frames
   *  2 -> 128 frames
   *  3 -> 256 frames
   *  4 -> 3 frames
   *  5 -> 4 frames
   *  6 -> 25 frames
   *  7 -> 2 frames
   */
  // [0-7] end page address
  // [0x00]
  // [0xFF]

#define SET_VHSCROLL_DIR(x) ( 0x29 + (x && 1) ) // x=1 -> left
                                                // x=0 -> right
  // [0x00]
  // [0-7] start page address
  /* [0-7] time interval (frames) between each scroll step
   *  0 -> 5 frames
   *  1 -> 64 frames
   *  2 -> 128 frames
   *  3 -> 256 frames
   *  4 -> 3 frames
   *  5 -> 4 frames
   *  6 -> 25 frames
   *  7 -> 2 frames
   */
  // [0-7] end page address
  // [0-63] vertical scrolling offset
  //No continuous vertical scrolling is available.
#define SET_SCROLL(x)       ( 0x2E + (x && 1) ) // x=1 -> activate
                                                // x=0 -> deactivate
  // After sending 2Eh command to deactivate the scrolling 
  // action, the ram data needs to be rewritten. 
#define SET_V_SCROLLAREA    0xA3
  // [0-63] num of rows in top fixed area
  // [0-128] num of rows in scroll area
  /*  Notes:
   *  1. [ fixed area ] + [ scroll area ] <=  MUX ratio
   *  2. Vertical scrolling offset (in SET_VHSCROLL_DIR(x))
   *      must be smaller then scroll area
   *  3. Display Start Line (in SET_STARTLINE(n))
   *      must be smaller then scroll area
   *      
       For 64d MUX display 
       [ fixed area ] = 0; [scroll area] = 64   <- whole area scrolls 
       [ fixed area ] = 0; [scroll area] < 64   <- top area scrolls 
       [ fixed area ] + [scroll area] < 64      <- central area scrolls 
       [ fixed area ] + [scroll area] = 64      <- bottom area scrolls
   */

    ////  addressing cmds  ////
    ///////////////////////////
#define SET_MEMADDR_MODE    0x20
#define HORI_MEMMODE  0x00
#define VERT_MEMMODE  0x01
#define PAGE_MEMMODE  0x02
  /*  [0-2] Memory Addressing Mode
   *    0 <- Horizontal Addressing Mode
   *    1 <- Vertical Addressing Mode
   *    2 <- Page Addressing Mode
   */

//  PAGE addressing mode
#define START_COL_H(x)  ( (x >> 4) & 0xF )
#define START_COL_L(x)  ( 0x10 + (x & 0xF) )
#define START_PAGE(x)   ( 0xB0 + (x & 7) )

//  HORISONTAL or VERTICAL addressing mode
#define SET_COL_ADRS        0x21
  //  [ 0-127 ] start address (RESET = 0)
  //  [ 0-127 ] end address   (RESET = 127)

#define SET_PAGE_ADRS       0x22
  //  [ 0-7 ] start address (RESET = 0)
  //  [ 0-7 ] end address   (RESET = 7)


    ////  hardconfig cmds  ////
    ///////////////////////////
#define DISP_STARTLINE(x)        ( 0x40 + ( x & 0x3F ) )
#define DISP_REMAP(x)    (0xA0 + (x && 1) )
#define SET_MUX_RATIO       0xA8
  // [ 15 - 63 ] <- MUX ratio minus 1
#define COMSCAN_DIR_INVERSE(x)  ( 0xC0 + ((x && 1) * 8))
#define SET_DISP_OFFSET     0xD3
  // [ 0 - 63 ] vertical shift
#define SET_COMPINS_HARDCFG 0xDA 
  /* [ 0b00PR0010 ]
   * P - COM pin cfg
   *      = 0 -> sequential COM pin cfg
   *      = 1 -> alternative COM pin cfg;
   * R - left/right remap enable
   *      = 1 -> enable
   *      = 0 -> disable
   */


    ////  Timing & Driving  ////
    ////////////////////////////
#define SET_DISP_CLK        0xD5
  /* [0xAB]
   *  A - Divide ratio        (RESET = 0h) 
   *  B - Oscillator Frequency  (RESET = 8h) 
   */
#define SET_PRE_CHARGE      0xD9
  /* [0xAB]
   *  A - Phase 1 period in range 1 : 15 (RESET = 2h) 
   *  B - Phase 2 period in range 1 : 15 (RESET = 2h) 
   */
#define SET_DESEL_LVL       0xDB
  /*VOLTAGE COMH deselect level
   *  0x00 <- ~ 0.65 x VCC
   *  0x20 <- ~ 0.77 x VCC (RESET) 
   *  0x30 <- ~ ~ 0.83 x VCC
   */
#define DISP_NO_OP          0xE3


    ////  Advance GFX  ////
    ///////////////////////
#define SET_DISP_MODE       0x23
  /* [0xAB]
   *  A - display mode
   *  A=0 <- fast Blinking Mode[RESET]
   *  A=1 <- Fade Out Mode
   *  A=2 <- Blinking mode
   *  
   *  B - Time interval for each fade step
   *  in range from 0 to 15
   *  num frames = 8 * (B+1)
   */
#define SET_ZOOM_MODE       0xD6
  /*  1 or 0
   *  0 <- Disable Zoom [RESET]
   *  1 <- Enable Zoom
      Note:
      COM pin cfg (in SET_COMPINS_HARDCFG)
          must be alternative
   */

    ////  Charge Pump  ////
    ///////////////////////
#define SET_CHARGE_PUMP     0x8D
#define CHARGE_PUMP_ENABLE  0x14
#define CHARGE_PUMP_DISABLE 0x10
  //  0x14 or 0x10
  //  0x14 <- Enable charge pump
  //  0x10 <- Disable charge pump (RESET)
