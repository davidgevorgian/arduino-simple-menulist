#ifndef __X_MENU__
#define __X_MENU__

#include <Arduino.h>

//for 16bit
#define pgm_read_ptr(address) (char *)__LPM_word((uint16_t)(address))
#define pgm_read_byte(address) __LPM((uint16_t)(address))
/*
for 32bit 
#define pgm_get_ptr(address) (char *)__ELPM_word((uint32_t)(address))
#define pgm_read_byte(address) __ELPM((uint32_t)(address_long))
*/

typedef struct{
  uint8_t count;  //number items in menu list
  PGM_P items;    //items pointer
  PGM_P list;     //items text list pointer
}XM_Menu_Head;

typedef struct{
  uint8_t type; //item type (any)
  PGM_P child;  //child pointer (menu list or variable or function or ...)
}XM_Menu_Item;

//list = list items ex: "Line1\0Item1\0Item2\0"
//make_items list name, count items, list items text, type, (ptr to child, type, ptr to child, type, ...)
#define XM_Make_items(name, count, list, ...) \
  const XM_Menu_Item __xm_##name[] PROGMEM = {__VA_ARGS__};\
  const char __xm_ls_##name[] PROGMEM = {list};\
  const XM_Menu_Head name[] PROGMEM ={count,(PGM_P)__xm_##name,__xm_ls_##name}

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

void XM_Getitem(XM_Menu_Item *item, PGM_P root, uint8_t nitem)
{
  root = pgm_read_ptr(root+offsetof(XM_Menu_Head,items))+sizeof(XM_Menu_Item)*nitem;
  memcpy_P(item,root,sizeof(XM_Menu_Item));
}
//
void XM_Gethead(XM_Menu_Head *head, PGM_P root)
{
  memcpy_P(head,root,sizeof(XM_Menu_Head));
}

void XM_Readlistitem(char *buffer, PGM_P list, uint8_t item)
{
  uint8_t dat;
  do{
    dat=pgm_read_byte(list++);
    if (item==0) *buffer++=dat;
    if (dat==0) item--;
  }while(item!=255);
}

uint8_t XM_Getlevelsize(PGM_P root)
{
  return pgm_read_byte(root+offsetof(XM_Menu_Head,count));
}

#endif
