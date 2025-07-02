

#include "Dri_multitree_menu.h"
#include <stdlib.h>
#include "dbg.h"
#include "Comp_OLED_Job.h"

TreeNode *g_root = NULL;
TreeNode *g_cur_node = NULL;

void action_0x2000(void)
{
    debug("action_2000...\n");

    create_led_flow_timer();

    stop_all_led_blink_to_off();
    stop_led_flow_timer();
}

void action_0x1110(void)
{
    debug("action_1110\n");
    stop_led_blink_to_off(LED1);
}

void action_0x1120(void)
{
    debug("action_1120\n");
    change_led_blink_timer(LED1, 2000);
}

void action_0x1130(void)
{
    debug("action_0x1130\n");
    change_led_blink_timer(LED1, 1000);
}
void action_0x1140(void)
{
    debug("action_0x1140\n");
    change_led_blink_timer(LED1, 200);
}

void action_0x1150(void)
{
    debug("action_0x1150\n");
    stop_led_blink_to_on(LED1);
}

void action_0x1210(void)
{
    debug("action_0x1210\n");
    stop_led_blink_to_off(LED2);
}

void action_0x1220(void)
{
    debug("action_0x1220\n");
    stop_led_blink_to_off(LED2);
}

void action_0x1230(void)
{
    debug("action_0x1230\n");
    change_led_blink_timer(LED2, 1000);
}
void action_0x1240(void)
{
    debug("action_0x1240\n");
    change_led_blink_timer(LED2, 200);
}

void action_0x1250(void)
{
    debug("action_0x1250\n");
    stop_led_blink_to_on(LED2);
}

void action_0x1310(void)
{
    debug("action_0x1310\n");
    stop_led_blink_to_off(LED3);
}

void action_0x1320(void)
{
    debug("action_0x1320\n");
    stop_led_blink_to_off(LED3);
}

void action_0x1330(void)
{
    debug("action_0x1330\n");
    change_led_blink_timer(LED3, 1000);
}
void action_0x1340(void)
{
    debug("action_0x1340\n");
    change_led_blink_timer(LED3, 200);
}

void action_0x1350(void)
{
    debug("action_0x1350\n");
    stop_led_blink_to_on(LED3);
}

void action_0x2400(void)
{
    debug("action_0x2400\n");
    // 关闭流水灯
}
void action_0x2410(void)
{
    debug("action_0x2410\n");
    stop_all_led_blink_to_off();
}

void action_0x2420(void)
{
    debug("action_0x2420\n");
    start_all_led_timer(2000);
}

void action_0x2430(void)
{
    debug("action_0x2430\n");
    start_all_led_timer(1000);
}

void action_0x2440(void)
{
    debug("action_0x2440\n");
    start_all_led_timer(200);
}

void action_0x2500(void)
{
    debug("action_0x2500\n");
}

void action_0x2510(void)
{
    debug("action_0x2510\n");
    stop_led_flow_timer();
}

void action_0x2520(void)
{
    debug("action_0x2520\n");
    LED_flow_on_front(1000);
}

void action_0x2530(void)
{
    debug("action_0x2530\n");
    LED_flow_on_back(1000);
}

void init_multi_tree(void)
{
    g_root = create_node(
        (DATA_TYPE){
            0x0000,
            "Root",
            NULL,
        });

    g_cur_node = g_root;

    debug("g_root 0x%x\n", g_root->data.g_menu_id);

    DATA_TYPE g_init_menu_data[] = {
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

    for (int i = 0; i < sizeof(g_init_menu_data) / sizeof(g_init_menu_data[0]); i++)
    {
        TreeNode *node = create_node(g_init_menu_data[i]);
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
