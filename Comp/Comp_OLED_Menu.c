#include "Comp_OLED_Menu.h"

#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"
#include "Int_LED.h"

#include "Int_KEY.h"

static TreeNode *g_root = NULL;
static TreeNode *g_cur_node = NULL;
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

__weak void action_0x1000(void)
{
    debug("action_0x1000\n");
}

__weak void action_0x2000(void)
{
    debug("action_0x2000\n");
}

__weak void action_0x3000(void)
{
    debug("action_0x3000\n");
}

__weak void action_0x4000(void)
{
    debug("action_0x4000\n");
}

__weak void action_0x5000(void)
{
    debug("action_0x5000\n");
}

__weak void action_0x6000(void)
{
    debug("action_0x6000\n");
}

__weak void action_0x7000(void)
{
    debug("action_0x7000\n");
}

__weak void action_0x7100(void)
{
    debug("action_0x7100\n");
}

__weak void action_0x1110(void)
{
    debug("action_1110\n");
}

__weak void action_0x1120(void)
{
    debug("action_1120\n");
}

__weak void action_0x1130(void)
{
    debug("action_0x1130\n");
}
__weak void action_0x1140(void)
{
    debug("action_0x1140\n");
}

__weak void action_0x1150(void)
{
    debug("action_0x1150\n");
}

__weak void action_0x1210(void)
{
    debug("action_0x1210\n");
}

__weak void action_0x1220(void)
{
    debug("action_0x1220\n");
}

__weak void action_0x1230(void)
{
    debug("action_0x1230\n");
}

__weak void action_0x1240(void)
{
    debug("action_0x1240\n");
}

__weak void action_0x1250(void)
{
    debug("action_0x1250\n");
}

__weak void action_0x1310(void)
{
    debug("action_0x1310\n");
}

__weak void action_0x1320(void)
{
    debug("action_0x1320\n");
}

__weak void action_0x1330(void)
{
    debug("action_0x1330\n");
}

__weak void action_0x1340(void)
{
    debug("action_0x1340\n");
}

__weak void action_0x1350(void)
{
    debug("action_0x1350\n");
}

__weak void action_0x2410(void)
{
    debug("action_0x2410\n");
}

__weak void action_0x2420(void)
{
    debug("action_0x2420\n");
}

__weak void action_0x2430(void)
{
    debug("action_0x2430\n");
}

__weak void action_0x2440(void)
{
    debug("action_0x2440\n");
}
__weak void action_0x2400(void)
{
    debug("action_0x2400\n");
}

__weak void action_0x2500(void)
{
    debug("action_0x2500\n");
}

__weak void action_0x2510(void)
{
    debug("action_0x2510\n");
}

__weak void action_0x2520(void)
{
    debug("action_0x2520\n");
}

__weak void action_0x2530(void)
{
    debug("action_0x2530\n");
}

static void init_multi_tree(void)
{
    g_root = create_node(
        (DATA_TYPE){
            0x0000,
            "Root",
            NULL,
        });

    g_cur_node = g_root;

    debug("g_root 0x%x\n", g_root->data.g_menu_id);

    // 初始化菜单内容都写在这里
    DATA_TYPE init_menu_data_sp[] = {
        (DATA_TYPE){0x1000, "Child1", NULL},
        // (DATA_TYPE){0x2000, "Child2", NULL},
        // (DATA_TYPE){0x3000, "Child3", NULL},
        // (DATA_TYPE){0x4000, "Child4", NULL},
        // (DATA_TYPE){0x1100, "Child1-1", NULL},
        // (DATA_TYPE){0x1200, "Child1-2", NULL},
        // (DATA_TYPE){0x1300, "Child1-3", NULL},
        // (DATA_TYPE){0x2100, "Child2-1", NULL},
        // (DATA_TYPE){0x2200, "Child2-2", NULL},
        // (DATA_TYPE){0x2300, "Child2-3", NULL},
        // (DATA_TYPE){0x3100, "Child3-1", NULL},
        // (DATA_TYPE){0x3200, "Child3-2", NULL},
        // (DATA_TYPE){0x3300, "Child3-3", NULL},
        // (DATA_TYPE){0x4100, "Child4-1", NULL},
        // (DATA_TYPE){0x1110, "Child1-1-1", NULL},
        // (DATA_TYPE){0x1210, "Child1-2-1", NULL},
        // (DATA_TYPE){0x1310, "Child1-3-1", NULL},
        // (DATA_TYPE){0x2110, "Child2-1-1", NULL},
        // (DATA_TYPE){0x2210, "Child2-2-1", NULL},
        // (DATA_TYPE){0x2310, "Child2-3-1", NULL},
        // (DATA_TYPE){0x3110, "Child3-1-1", NULL},
        // (DATA_TYPE){0x3210, "Child3-2-1", NULL},
        // (DATA_TYPE){0x3310, "Child3-3-1", NULL},

        /////////////////////////////////////////
        // (DATA_TYPE){0x1000, "reset", action_0x1000},
        // (DATA_TYPE){0x2000, "mode1", action_0x2000},
        // (DATA_TYPE){0x3000, "mode2", action_0x3000},
        // (DATA_TYPE){0x4000, "mode3", action_0x4000},
        // (DATA_TYPE){0x5000, "LED1_OFF", action_0x5000},
        // (DATA_TYPE){0x6000, "LED2_OFF", action_0x6000},
        // (DATA_TYPE){0x7000, "LED3_OFF", action_0x7000},
        // (DATA_TYPE){0x7100, "7100", action_0x7100},
    };
    (void)init_menu_data_sp;

    DATA_TYPE init_menu_data[] = {
        (DATA_TYPE){0x1000, "独立控制", NULL},
        (DATA_TYPE){0x2000, "同步控制", action_0x2000},

        (DATA_TYPE){0x1100, "LED1", NULL},
        (DATA_TYPE){0x1200, "LED2", NULL},
        (DATA_TYPE){0x1300, "LED3", NULL},
        (DATA_TYPE){0x2400, "同步闪烁", action_0x2400},
        (DATA_TYPE){0x2500, "流水灯闪烁", action_0x2500},

        (DATA_TYPE){0x1110, "LED1-关闭", action_0x1110},
        (DATA_TYPE){0x1120, "LED1-慢闪", action_0x1120},
        (DATA_TYPE){0x1130, "LED1-中闪", action_0x1130},
        (DATA_TYPE){0x1140, "LED1-快闪", action_0x1140},
        (DATA_TYPE){0x1150, "LED1-常亮", action_0x1150},
        (DATA_TYPE){0x1210, "LED2-关闭", action_0x1210},
        (DATA_TYPE){0x1220, "LED2-慢闪", action_0x1220},
        (DATA_TYPE){0x1230, "LED2-中闪", action_0x1230},
        (DATA_TYPE){0x1240, "LED2-快闪", action_0x1240},
        (DATA_TYPE){0x1250, "LED2-常亮", action_0x1250},
        (DATA_TYPE){0x1310, "LED3-关闭", action_0x1310},
        (DATA_TYPE){0x1320, "LED3-慢闪", action_0x1320},
        (DATA_TYPE){0x1330, "LED3-中闪", action_0x1330},
        (DATA_TYPE){0x1340, "LED3-快闪", action_0x1340},
        (DATA_TYPE){0x1350, "LED3-常亮", action_0x1350},

        (DATA_TYPE){0x2410, "同步闪烁-关闭", action_0x2410},
        (DATA_TYPE){0x2420, "同步闪烁-慢闪", action_0x2420},
        (DATA_TYPE){0x2430, "同步闪烁-中闪", action_0x2430},
        (DATA_TYPE){0x2440, "同步闪烁-快闪", action_0x2440},
        (DATA_TYPE){0x2510, "流水灯闪烁-关闭", action_0x2510},
        (DATA_TYPE){0x2520, "流水灯闪烁-顺", action_0x2520},
        (DATA_TYPE){0x2530, "流水灯闪烁-逆", action_0x2530},

    };

    for (int i = 0; i < sizeof(init_menu_data) / sizeof(init_menu_data[0]); i++)
    {
        TreeNode *node = create_node(init_menu_data[i]);
        // debug("node 0x%x->", node->data.g_menu_id);
        TreeNode *parent = find_parent(g_root, node);
        // debug("parent 0x%x\n", parent->data.g_menu_id);

        if (parent != NULL)
        {
            add_child(parent, node);
        }
        else
        {
            add_child(g_root, node);
        }
    }

    preorder_traversal(g_root);
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
