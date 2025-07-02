#include "Comp_OLED_Menu.h"

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "Int_LED.h"

#include "Int_KEY.h"

// Comp_OLED_Menu_Data中定义
extern TreeNode *g_root;
extern TreeNode *g_cur_node;
extern void init_multi_tree(void);

//////////////////菜单操作/////////////////////////////

void show_cur_menu(TreeNode *cur_node)
{
    if (cur_node == NULL)
    {
        return;
    }

    g_cur_node = cur_node;
    // 判断是否子菜单为空

    // [ ] 工作函数在此处调用
    if (cur_node->data.action != NULL)
    {
        cur_node->data.action();
    }

    if (cur_node->child_count == 0)
    {

        OLED_Clear();
        OLED_ShowString(0, 0, (char *)(cur_node->data.menu_name), OLED_8X16);
        OLED_ShowString(0, 16, "running....", OLED_8X16);
        OLED_Update();
    }
    else
    {

        int active_index = cur_node->active_child;
        int i = 0;
        OLED_Clear();

        // 第一行显示内容，是active_index的前一个
        if (active_index == 0)
        {
            OLED_ClearArea(0, 0, 128, 16);
        }
        else
        {
            OLED_ShowString(0, 0, (char *)cur_node->children[-1 + active_index]->data.menu_name, OLED_8X16);
        }

        // 第二行显示内容，是active_index的内容
        for (i = 0; i < cur_node->child_count - active_index && i < 3; i++)
        {
            OLED_ShowString(0, (i + 1) * 16, (char *)cur_node->children[i + active_index]->data.menu_name, OLED_8X16);
        }

        // active_index 内容反转显示表示选择
        OLED_ReverseArea(0, 16, 128, 16);
        OLED_Update();
    }
}

void menu_up()
{
    if (g_cur_node->active_child > 0)
    {
        g_cur_node->active_child--;
    }
    show_cur_menu(g_cur_node);
}

void menu_down()
{
    if (g_cur_node->active_child < g_cur_node->child_count - 1)
    {
        g_cur_node->active_child++;
    }
    show_cur_menu(g_cur_node);
}

void menu_enter()
// 将当前的cur_node 更新为子菜单node
{
    // 正常如果child_count = 0，走不到这个函数里来
    if (g_cur_node->child_count == 0)
    {
        show_cur_menu(g_cur_node);
        return;
    }
    g_cur_node = g_cur_node->children[g_cur_node->active_child];
    show_cur_menu(g_cur_node);
}

void menu_back()
{
    if (g_cur_node == g_root)
    {
        return;
    }
    g_cur_node = get_parent(g_cur_node);
    show_cur_menu(g_cur_node);
}

/////////////////////////////////////////////////////////////

void Comp_OLED_Menu_Init(void)
{

    // 初始化菜单
    init_multi_tree();

    show_cur_menu(g_root);
    // 初始化Job相关
    Comp_OLED_Job_Init();
}

int test_multi_tree()
{
    // test_get_parent_id();
    // test_find_node_by_id();
    debug("test_multi_tree\n");
    preorder_traversal(g_root);
    show_cur_menu(g_root);

    // TreeNode *node = find_node_by_id(g_root, 0x2000);
    // debug("node->active_child = %d\n", node->active_child);
    // menu_down();
    // // debug("node->active_child = %d\n", node->active_child);
    // // menu_down(node);
    // debug("node->active_child = %d\n", node->active_child);
    // menu_enter();
    // menu_enter();
    // menu_back();
    // menu_back();
    // menu_back();
    // menu_enter();
    // menu_down();
    // menu_down();
    // menu_up();

    // TreeNode *node = find_node_by_id(g_root, 0x1100);
    // debug("node->active_child = %d\n", node->active_child);
    // show_cur_menu(node);
    // menu_enter();
    return 0;
}

void menu_key_scan(void)
{
    if (Key_GetState(KEY1, KEY_STATE_SINGLE))
    {
        menu_up();
        Key_ResetState(KEY1, KEY_STATE_SINGLE);
    }
    if (Key_GetState(KEY2, KEY_STATE_SINGLE))
    {
        menu_down();
        Key_ResetState(KEY2, KEY_STATE_SINGLE);
    }
    if (Key_GetState(KEY3, KEY_STATE_SINGLE))
    {
        menu_enter();
        Key_ResetState(KEY3, KEY_STATE_SINGLE);
    }
    if (Key_GetState(KEY4, KEY_STATE_SINGLE))
    {
        menu_back();
        Key_ResetState(KEY4, KEY_STATE_SINGLE);
    }
}
