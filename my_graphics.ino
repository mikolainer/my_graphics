#include "my_graphics.h"
#include "num_ctrl.h"
#include "images.h"

#define OLED_CLK        14+1
#define OLED_MOSI       14+2
#define OLED_RESET      14+3    // could be connected to VCC
#define OLED_DC         14+4
#define OLED_CS         14+5    // could be connected to GND

my_graphics disp(OLED_MOSI, OLED_CLK, OLED_DC, OLED_CS, OLED_RESET);


//// images declaration
// main menu

bitmap Main_Menu_Batary( &MMbatval[0],  13,  59 );

bitmap Main_Menu_Active( &MMA_bmp [0],  89,  20 );
bitmap Main_Menu_Upped ( &MMU_bmp [0],  89,  20 );
bitmap Main_Menu_Losted( &MML_bmp [0],  89,  20 );

bitmap Num_Active_HIGH ( &digits  [0],   8,  16 );
bitmap Num_Active_LOW  ( &digits  [0],   8,  16 );
bitmap Num_Upped_HIGH  ( &digits  [0],   8,  16 );
bitmap Num_Upped_LOW   ( &digits  [0],   8,  16 );
bitmap Num_Losted_HIGH ( &digits  [0],   8,  16 );
bitmap Num_Losted_LOW  ( &digits  [0],   8,  16 );

// sub menu
bitmap  Sub_Menu_Batary(    &SMbatval[0],  24,   9 );

bitmap  Sub_Menu_Accept(   &cha_fo_re[0],  96,  20 );
bitmap  Sub_Menu_Choise( &dat_nom_dat[0],  96,  16 );

bitmap  White_Nums_Mark  (     &white[0],  24,  24 );
bitmap  Num_Selected_HIGH(    &digits[0],   8,  16 );
bitmap  Num_Selected_LOW (    &digits[0],   8,  16 );
bitmap  Num_Choised_HIGH (    &digits[0],   8,  16 );
bitmap  Num_Choised_LOW  (    &digits[0],   8,  16 );



//// build frames
bitmap* MainMenu_imgs[] = { &Main_Menu_Active,
                            &Main_Menu_Upped,
                            &Main_Menu_Losted,
                            &Main_Menu_Batary,
                            &Num_Active_HIGH, &Num_Active_LOW,
                            &Num_Upped_HIGH,  &Num_Upped_LOW,
                            &Num_Losted_HIGH, &Num_Losted_LOW
                          };
                          
bitmap* SubMenu_imgs[]  = { &Sub_Menu_Batary,
                            &Sub_Menu_Accept,
                            &Sub_Menu_Choise,
                            &Num_Selected_HIGH, &Num_Selected_LOW,
                            &Num_Choised_HIGH,  &Num_Choised_LOW,
                            &White_Nums_Mark
                          };

//// frames declaration
frame MainMenu( MainMenu_imgs, sizeof(MainMenu_imgs) / sizeof(bitmap*) );
frame SubMenu ( SubMenu_imgs,  sizeof(SubMenu_imgs)  / sizeof(bitmap*) );

//// digit controll

bitmap* Num_Active_digs[]   = { &Num_Active_LOW   , &Num_Active_HIGH };
bitmap* Num_Upped_digs[]    = { &Num_Upped_LOW    , &Num_Upped_HIGH    };
bitmap* Num_Losted_digs[]   = { &Num_Losted_LOW   , &Num_Losted_HIGH  };
bitmap* Num_Selected_digs[] = { &Num_Selected_LOW , &Num_Selected_HIGH };
bitmap* Num_Choised_digs[]  = { &Num_Choised_LOW  , &Num_Choised_HIGH   };

num_ctrl Num_Active(   99, Num_Active_digs   );
num_ctrl Num_Upped(    99, Num_Upped_digs    );
num_ctrl Num_Losted(   99, Num_Losted_digs   );
num_ctrl Num_Selected( 99, Num_Selected_digs );
num_ctrl Num_Choised(  99, Num_Choised_digs  );

//// inits

void bmp_positions_init(){
  Main_Menu_Batary.setPosition(     2,   3 );
  Main_Menu_Active.setPosition(    18,   2 );
  Main_Menu_Losted.setPosition(    18,  22 );
  Main_Menu_Upped.setPosition(     18,  42 );

  Num_Active_HIGH.setPosition(    109,   4 );
  Num_Active_LOW.setPosition(     119,   4 );
  Num_Losted_HIGH.setPosition(    109,  24 );
  Num_Losted_LOW.setPosition(     119,  24 );
  Num_Upped_HIGH.setPosition(     109,  44 );
  Num_Upped_LOW.setPosition(      119,  44 );

  Sub_Menu_Batary.setPosition(    101,  26 );
  Sub_Menu_Choise.setPosition(      2,   5 );
  Sub_Menu_Accept.setPosition(      2,  39 );

  Num_Selected_HIGH.setPosition(  104,   5 );
  Num_Selected_LOW.setPosition(   114,   5 );
  Num_Choised_HIGH.setPosition(   104,  41 );
  Num_Choised_LOW.setPosition(    114,  41 );

  White_Nums_Mark.setPosition( 101, 1 );
//  White_Nums_Mark.setPosition( 101, 37 );
}

void bmp_visible_init(){
  Sub_Menu_Accept.setVisible(  false );
  Num_Choised.hide();
  Num_Choised.invert();
  Num_Selected.invert();
}

void setup() {
  disp.begin();
  bmp_positions_init();
  bmp_visible_init();
}


void loop() {
  disp.clear();
  Main_Menu_Active.setInversed( true );
  Num_Selected.setVal(69);
//  SubMenu.draw( disp );
  MainMenu.draw( disp );

  while(1);
}
