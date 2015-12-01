Simple menu list in PROGMEM
=========
*Based on #define helper for create menu list in PROGMEM. See example.*


**Menu list maker:**

*XM_Make_items(name, number items, items text,item0,item2,.....itemx);*

**name** - this list name
**number items** - number items in list
**items text** - the zero terminated list. ex:. "Text1\0Text2\0Line3\0"
**item[x]** - user any type 0..255, ptr to child (PGM_P). ex.: (PGM_P)&parameter1 - pointer to var parameter1, (PGM_P)list3 - pointer to a child menu list by the name (list3)
==
Internal TYPES:

XM_Menu_Head - list header.
read [.count] - count items in list
read [.list] - PGM_P pointer to list in PROGMEM

XM_Menu_Item - item structure
read [.type] - user define type [0..255]
read [.child] - PGM_P pointer to child (next level list items, variable, function, ...)

Functions:

XM_Getitem(&item, list, uint8_t nitem)

Read item [nitem] to [item] from [list].

nitem - 0..255
item - XM_Menu_Item
list - list menu name (PGM_P)
Example: XM_Getitem(&curitem,(PGM_P)mainmenu,1) - read second item to "curitem" from "mainmenu"
-----------------------------------------------------------------------------------
XM_Gethead(&head, list)

Read list header from [list] menu list to [head]
list - list menu name (PGM_P)
head - XM_Menu_Head

Example: XM_Gethead(&menuhead,(PGM_P)mainmenu)
------------------------------------------------------------------------------------
XM_Readlistitem(buffer, list, numitem)

Read [numitem] text to [buffer] from items text [list]
buffer - zero terminated string
list - (PGM_P) of items text. Can read from menu header [.list]
numitem - item number 0..254
