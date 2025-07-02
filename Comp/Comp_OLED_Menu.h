#ifndef __OLED_MENU__H_
#define __OLED_MENU__H_

#include "Dri_multitree_menu.h"
#include "Int_OLED.h"
#include "Comp_OLED_Job.h"
// 菜单操作函数

void Comp_OLED_Menu_Init(void);

void menu_key_scan(void);

int test_multi_tree(void);

#endif // !__OLED_MENU__H_
