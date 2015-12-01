#include "xmenu.h"
#include "menu_init.h"



void setup() {
  Serial.begin(9600);
  while (!Serial);

  char buffer[20];

  XM_Menu_Head head;
  XM_Menu_Item item;

  //read item text 2,1
  XM_Getitem(&item, (PGM_P)root,1);
  XM_Gethead(&head,item.child);
  XM_Readlistitem(buffer,head.list,0);
  Serial.println(buffer);
  
}

void loop() {
}
