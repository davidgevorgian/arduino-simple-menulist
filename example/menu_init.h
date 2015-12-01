#ifndef __MENU_INIT__
#define __MENU_INIT__

#define XM_Type_Item 0
#define XM_Type_Int 1

XM_Make_items(it1,2,"Line2.1\0Line2.2\0",
  XM_Type_Item,0,
  XM_Type_Int,0
  );
XM_Make_items(root,3,"Line1\0Line2\0Line3\0",
  XM_Type_Item,0,
  XM_Type_Item,(PGM_P)it1,
  XM_Type_Item,0
  );

//>>>>>>>>>>>> UTILS >>>>>>>>>>>>>>>>>>

#endif
