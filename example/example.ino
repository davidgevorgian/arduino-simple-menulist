#include "xmenu.h"

int parameter1 = 723;

#define XM_Type_Item 0
#define XM_Type_Int 1

XM_Make_items(it1,2,"Line2.1\0Line2.2\0",
  XM_Type_Item,0,
  XM_Type_Int,(PGM_P)&parameter1
  );
XM_Make_items(root,3,"Line1\0Line2\0Line3\0",
  XM_Type_Item,0,
  XM_Type_Item,(PGM_P)it1,
  XM_Type_Item,0
  );

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
