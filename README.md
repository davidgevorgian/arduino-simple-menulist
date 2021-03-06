## Arduino multilevel menu list in FLASH (PROGMEM)
*Simple, minimum flash memory and NO RAM*

Helper Xmenu Ver 1.0

---

![Structer](https://cloud.githubusercontent.com/assets/16103132/11769521/bfc4fe84-a1f1-11e5-9b12-f6391700aa73.png)



### Structure in FLASH Memory
*Menu list*

**Header:**
- [Byte] Number Items in Menu list
- [PGM_P] Pointer to Items text
- [PGM_P] Pointer to Items list

**Items text:**
- [Chars] Item 0 text
- [Byte] Terminator
- [Chars] Item 1 text
- [Byte] Terminator
- ...
- [Chars] Item N text
- [Byte] Terminator

**Items list:**
- [Byte] Item 0 type (any user type)
- [PGM_P] Pointer to (child "*Menu List*") or (Variable) or ...
- [Byte] Item 1 type (any user type)
- [PGM_P] Pointer to (child "*Menu List*") or (Variable) or ...
- ...
- [Byte] Item N type (any user type)
- [PGM_P] Pointer to (child "*Menu List*") or (Variable) or ...

---
#### Menu list maker:

*XM_Make_items(name, number items, items text, item 0, item 1, ..., item N);*

- **name** - this 'Menu list' name
- **number items** - number items in this list
- **items text** - zero terminated 'Items text'. *ex.: "Text1\0Text2\0Line3\0"*
- **item[0..N]** - 'Items list'. *ex.: {Item, (PGM_P)Mlist2} - pointer to a child sub menu list Mlist2 or {Int, (PGM_P)&parameter1} - pointer to integer parameter1 or {Func, (PGM_P)&function2} - pointer to function2 or any user define*

#### Internal TYPES:

**XM_Menu_Head** - 'Menu list' header.
- [.count] - count items in 'Menu list'
- [.list] - PGM_P pointer to 'Items text'

**XM_Menu_Item** - 'Menu list' item structure
- [.type] - user define, any type [0..255]
- [.child] - PGM_P pointer to (sub level 'Menu list', variable, function, ...)

#### Functions:

**XM_Getitem(&item, list, uint8_t nitem)** - Read item from 'Menu list'.
- **nitem** - item number 0..255
- **list** - 'Menu list' name (PGM_P)

return:
- **item** - see XM_Menu_Item structure
```
XM_Getitem(&curitem,(PGM_P)mainmenu,1) // read second item from "mainmenu" and return to "curitem"
```

**XM_Gethead(&head, list)** - Read 'Menu list' header
- **list** - 'Menu list' name (PGM_P)

return:
- **head** - see XM_Menu_Head structure
```
XM_Gethead(&menuhead,(PGM_P)mainmenu) // read header from "mainmenu" and return to "menuhead"
```
**XM_Readlistitem(buffer, list, numitem)** - Read text from 'Items text'
- **list** - (PGM_P) Pointer to 'Items text'. *see: XM_Getlistptr*
- **numitem** - Item text number [0..254]

return:
- **buffer** - Item text. Zero terminated string

**PGM_P XM_Getchildptr(PGM_P menu, uint8_t nitem)** - Return pointer to child
- **menu** - 'Menu list' name (PGM_P)
- **nitem** - item number 0..255

return:
- **PGM_P** - pointer to child

**PGM_P XM_Getlistptr(PGM_P menu)** - Return pointer to 'Items text'
- **menu** - - 'Menu list' name (PGM_P)

return:
- **PGM_P** - pointer to 'Items text'

**uint8_t XM_Getitemscount(PGM_P menu)** - Return count items in 'Menu list'
- **menu** - - 'Menu list' name (PGM_P)

return:
- **uint8_t** - count items
