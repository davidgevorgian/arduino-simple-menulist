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

//========================= Menu Structer =========================
#define listterminator 1 /* terminator for string list */

typedef struct {
  uint8_t count;  //number of items in menu list
  PGM_P items;    //pointer to items list
  PGM_P list;     //pointer to items text list
}XM_Menu_Head;

typedef struct {
  uint8_t type; //item type (any) define by user
  PGM_P child;  //pointer to child (menu list or variable or function or ...)
}XM_Menu_Item;

//list = list items example: "Line1\0Item1\0Item2\0"
//make_items list name, count items, list items text, (type, ptr to child, type, ptr to child, ...)
#define XM_Make_items(name, count, list, ...) \
  const XM_Menu_Item __xm_##name[] PROGMEM = {__VA_ARGS__};\
  const char __xm_ls_##name[] PROGMEM = {list};\
  const XM_Menu_Head name[] PROGMEM ={count,(PGM_P)__xm_##name,__xm_ls_##name}
//======================= END Menu Structer =======================

//========================= Menu Utils =========================
void XM_Getitem(XM_Menu_Item *item, PGM_P menu, uint8_t nitem)
{
  menu = pgm_read_ptr(menu + offsetof(XM_Menu_Head, items)) + sizeof(XM_Menu_Item) * nitem;
  memcpy_P(item, menu, sizeof(XM_Menu_Item));
}

void XM_Gethead(XM_Menu_Head *head, PGM_P menu)
{
  memcpy_P(head, menu, sizeof(XM_Menu_Head));
}

PGM_P XM_Getchildptr(PGM_P menu, uint8_t nitem)
{
  menu = pgm_read_ptr(menu + offsetof(XM_Menu_Head, items)) + sizeof(XM_Menu_Item) * nitem;
  return pgm_read_ptr(menu + offsetof(XM_Menu_Item, child));
}

PGM_P XM_Getlistptr(PGM_P menu)
{
  return pgm_read_ptr(menu+offsetof(XM_Menu_Head, list));
}

uint8_t XM_Getitemscount(PGM_P menu)
{
  return pgm_read_byte(menu+offsetof(XM_Menu_Head, count));
}

void XM_Readlistitem(char *buffer, PGM_P list, uint8_t item)
{
  uint8_t dat;
  do {
    dat = pgm_read_byte(list++);
    if (item == 0) *buffer++ = dat;
    if ((dat==0)||(dat == listterminator)) item--;
  } while (item != 255);
  *(buffer-1)=0;
}

#endif
