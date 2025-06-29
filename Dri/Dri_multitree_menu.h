#ifndef __MULTITREE__MENU__H_
#define __MULTITREE__MENU__H_

#include <stdint.h>

// [ ] 后续优化为动态扩展数组大小，就可以设置小一些，当前子菜单固定最多8个
#define INIT_CAPACITY 2

// 定义菜单操作函数类型
typedef void (*MenuAction)(void);

// 定义菜单结构体
typedef struct MenuItem
{
    // 全局索引编号
    // FIXME 每个16进制位不能取0，否则get_parent_id会判断出错
    uint16_t g_menu_id;
    // 菜单名称，每个汉字是3个字符长度，8个汉字24字节，至少24
    char menu_name[32];
    MenuAction action;
} MenuItem;

// 定义数据类型
typedef MenuItem DATA_TYPE;

// 定义多叉树节点结构
typedef struct TreeNode
{
    DATA_TYPE data;
    struct TreeNode **children;
    int child_count;
    int active_child;
    int capacity;
    struct TreeNode *parent;
} TreeNode;

TreeNode *create_node(DATA_TYPE data);
// 通过子节点的g_menu_id 查找父节点
TreeNode *find_parent(TreeNode *root, TreeNode *node);

TreeNode *find_node_by_id(TreeNode *root, uint16_t id);

// 通过父指针
TreeNode *get_parent(TreeNode *node);

void add_child(TreeNode *parent, TreeNode *child);
// 添加子节点

// 释放多叉树内存
void free_tree(TreeNode *root);

// 前序遍历多叉树
void preorder_traversal(TreeNode *root);

#endif // !__MULTITREE__MENU__H_
