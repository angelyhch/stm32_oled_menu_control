#include "Dri_multitree_menu.h"

#include "FreeRTOS.h"

#include "dbg.h"
#include "FreeRTOSConfig.h"
#include <stdlib.h>

#define my_ASSERT(x)                                                           \
    if ((x) == 0)                                                              \
    {                                                                          \
        debug("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    }

uint16_t
get_parent_id(MenuItem *item)
{
    uint16_t current_id = item->g_menu_id;

    int i = 0;
    uint16_t mask;
    for (i = 0; i < 4; i++)
    {
        mask = 0xf << i * 4;
        // debug("mask: 0x%x\n", mask);
        // debug("current_id & mask: 0x%x\n", current_id & (mask));
        // FIXME 下面必须用过括号调整优先级，否则会出现永远都不能break的情况
        if ((current_id & (mask)) != 0)
            break;
    }

    // debug("i: %d\n", i);
    // debug("current_id: 0x%x\n", current_id);
    return current_id & (~(0xf << i * 4));
}

// 创建新节点
TreeNode *create_node(DATA_TYPE data)
{
    TreeNode *node = (TreeNode *)pvPortMalloc(sizeof(TreeNode));
    if (node == NULL)
    {
        debug("Memory allocation failed\n");
        return NULL;
    }

    node->data = data;
    node->child_count = 0;
    node->active_child = 0;
    node->capacity = INIT_CAPACITY; // 初始容量
    // debug("node->capacity: %d\n", node->capacity);
    node->children = (TreeNode **)pvPortMalloc(node->capacity * sizeof(TreeNode *));
    if (node->children == NULL)
    {
        debug("Memory allocation failed\n");
        vPortFree(node);
        return NULL;
    }
    node->parent = NULL;
    return node;
}

TreeNode *find_node_by_id(TreeNode *root, uint16_t id)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (root->data.g_menu_id == id)
    {
        return root;
    }

    for (int i = 0; i < root->child_count; i++)
    {
        if (root->children[i]->data.g_menu_id == id)
        {
            return root->children[i];
        }
        TreeNode *node = find_node_by_id(root->children[i], id);
        if (node != NULL)
        {
            return node;
        }
    }

    return NULL;
}
TreeNode *find_parent(TreeNode *root, TreeNode *node)
// 通过子节点的g_menu_id 查找父节点
{
    if (root == NULL || node == NULL)
    {
        return NULL;
    }
    if (root == node)
    {
        return root;
    }

    uint16_t parent_id = get_parent_id(&node->data);
    return find_node_by_id(root, parent_id);
}

TreeNode *get_parent(TreeNode *node)
// 通过父指针
{
    if (node == NULL)
    {
        return NULL;
    }
    return node->parent;
}

// 自定义实现 pvPortRealloc 函数
void *pvPortRealloc(void *pv, size_t old_size, size_t xWantedSize)
{
    void *pvNew;

    // 如果传入的指针为 NULL，直接调用 pvPortMalloc
    if (pv == NULL)
    {
        return pvPortMalloc(xWantedSize);
    }

    // 如果请求的大小为 0，释放原内存并返回 NULL
    if (xWantedSize == 0)
    {
        vPortFree(pv);
        return NULL;
    }

    // 分配新的内存块
    pvNew = pvPortMalloc(xWantedSize);
    if (pvNew != NULL)
    {
        // 获取原内存块的大小（实际应用中需要自己维护原内存块大小信息）
        // 这里简单假设原内存块大小为 old_size，实际可能需要更复杂的处理
        // 这里为示例，假设能通过某种方式获取原内存块大小
        // 以下代码仅为示例，实际可能需要使用内存管理结构来记录原大小
        // size_t old_size = xWantedSize; // 示例，实际需要替换
        // 复制原内存块的数据到新内存块
        memcpy(pvNew, pv, old_size < xWantedSize ? old_size : xWantedSize);
        // 释放原内存块
        vPortFree(pv);
    }

    return pvNew;
}
// 添加子节点
void add_child(TreeNode *parent, TreeNode *child)
{
    if (parent == NULL || child == NULL)
    {
        return;
    }

    // debug("parent->child_count: %d\n", parent->child_count);
    if (parent->child_count >= parent->capacity)
    {
        // 扩容
        size_t old_size = parent->capacity;
        size_t new_size = old_size + 2;
        // FIXME 这个不要忘记了，切记
        parent->capacity = new_size;
        size_t old_size_byte = parent->capacity * sizeof(TreeNode *);
        size_t new_size_byte = new_size * sizeof(TreeNode *);
        // debug("old_size: %d, old_size_byte: %d, new_size: %d, new_size_byte: %d\n", old_size, old_size_byte, new_size, new_size_byte);
        TreeNode **new_children = (TreeNode **)pvPortRealloc(parent->children, old_size_byte, new_size_byte);
        if (new_children == NULL)
        {
            debug("Memory reallocation failed\n");
            return;
        }
        parent->children = new_children;
    }

    parent->children[parent->child_count++] = child;
    child->parent = parent;

    // 查看增加后的内容
    // for (int i = 0; i < parent->child_count; i++)
    // {
    //     debug("0x%x->0x%x\n", parent->children[i]->data.g_menu_id, parent->children[i]->parent->data.g_menu_id);
    // }
}

// 释放多叉树内存
void free_tree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < root->child_count; i++)
    {
        free_tree(root->children[i]);
    }

    vPortFree(root->children);
    vPortFree(root);
}

// 前序遍历多叉树
void preorder_traversal(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    debug("0x%x->", root->data.g_menu_id);
    for (int i = 0; i < root->child_count; i++)
    {
        preorder_traversal(root->children[i]);
    }
}

/////////////////测试函数/////////////////////////

// 模拟 MenuAction 函数
static void dummy_action(void)
{
    // 空函数，仅用于测试
}
// 测试用例
static void test_get_parent_id()
{
    // 测试用例1: 最低半字节非零
    {
        MenuItem item = {
            .g_menu_id = 0x1234,
            .menu_name = "TestMenu1",
            .action = dummy_action};
        uint16_t parent_id = get_parent_id(&item);
        debug("Test case 1: 0x%04x -> 0x%04x\n", item.g_menu_id, parent_id);
        my_ASSERT(parent_id == 0x1230);
    }

    // 测试用例2: 第二个半字节非零
    {
        MenuItem item = {
            .g_menu_id = 0x1200,
            .menu_name = "TestMenu2",
            .action = dummy_action};
        uint16_t parent_id = get_parent_id(&item);
        debug("Test case 2: 0x%04x -> 0x%04x\n", item.g_menu_id, parent_id);
        my_ASSERT(parent_id == 0x1000);
    }

    // 测试用例3: 第三个半字节非零
    {
        MenuItem item = {
            .g_menu_id = 0x1000,
            .menu_name = "TestMenu3",
            .action = dummy_action};
        uint16_t parent_id = get_parent_id(&item);
        debug("Test case 3: 0x%04x -> 0x%04x\n", item.g_menu_id, parent_id);
        my_ASSERT(parent_id == 0x0000);
    }

    // 测试用例4: 最高半字节非零
    {
        MenuItem item = {
            .g_menu_id = 0x0001,
            .menu_name = "TestMenu4",
            .action = dummy_action};
        uint16_t parent_id = get_parent_id(&item);
        debug("Test case 4: 0x%04x -> 0x%04x\n", item.g_menu_id, parent_id);
        my_ASSERT(parent_id == 0x0000);
    }

    // 测试用例5: 全零情况
    {
        MenuItem item = {
            .g_menu_id = 0x0000,
            .menu_name = "TestMenu5",
            .action = dummy_action};
        uint16_t parent_id = get_parent_id(&item);
        debug("Test case 5: 0x%04x -> 0x%04x\n", item.g_menu_id, parent_id);
        my_ASSERT(parent_id == 0x0000);
    }

    // 测试用例6: 所有半字节都非零
    {
        MenuItem item = {
            .g_menu_id = 0xFFFF,
            .menu_name = "TestMenu6",
            .action = dummy_action};
        uint16_t parent_id = get_parent_id(&item);
        debug("Test case 6: 0x%04x -> 0x%04x\n", item.g_menu_id, parent_id);
        my_ASSERT(parent_id == 0xFFF0);
    }

    debug("All test cases passed!\n");
}

static void test_find_node_by_id_empty_tree(void)
{
    TreeNode *root = NULL;
    TreeNode *result = find_node_by_id(root, 100);
    debug("test_find_node_by_id_empty_tree: %d\n", result == NULL);
    my_ASSERT(result == NULL);
}

static void test_find_node_by_id_root_match(void)
{
    MenuItem item = {
        .g_menu_id = 100,
        .menu_name = "TestRoot",
        .action = dummy_action};
    TreeNode *root = create_node(item);
    TreeNode *result = find_node_by_id(root, 100);
    debug("test_find_node_by_id_root_match: %d\n", result == root);
    my_ASSERT(result == root);
    free_tree(root);
}

static void test_find_node_by_id_child_match(void)
{
    MenuItem root_item = {
        .g_menu_id = 1,
        .menu_name = "TestRoot",
        .action = dummy_action};
    TreeNode *root = create_node(root_item);

    MenuItem child1_item = {
        .g_menu_id = 2,
        .menu_name = "TestChild1",
        .action = dummy_action};
    TreeNode *child1 = create_node(child1_item);

    MenuItem child2_item = {
        .g_menu_id = 3,
        .menu_name = "TestChild2",
        .action = dummy_action};
    TreeNode *child2 = create_node(child2_item);

    add_child(root, child1);
    add_child(root, child2);

    TreeNode *result = find_node_by_id(root, 3);
    debug("test_find_node_by_id_child_match: %d\n", result == child2);
    my_ASSERT(result == child2);

    free_tree(root);
}

// 测试在多层嵌套中找到匹配
static void test_find_node_by_id_nested_match(void)
{
    MenuItem root_item = {
        .g_menu_id = 1,
        .menu_name = "TestRoot",
        .action = dummy_action};
    TreeNode *root = create_node(root_item);

    MenuItem child1_item = {
        .g_menu_id = 2,
        .menu_name = "TestChild1",
        .action = dummy_action};
    TreeNode *child1 = create_node(child1_item);

    MenuItem child2_item = {
        .g_menu_id = 3,
        .menu_name = "TestChild2",
        .action = dummy_action};
    TreeNode *child2 = create_node(child2_item);

    MenuItem grandchild_item = {
        .g_menu_id = 4,
        .menu_name = "TestGrandChild",
        .action = dummy_action};
    TreeNode *grandchild = create_node(grandchild_item);

    add_child(root, child1);
    add_child(root, child2);
    add_child(child1, grandchild);

    TreeNode *result = find_node_by_id(root, 4);
    debug("test_find_node_by_id_nested_match: %d\n", result == grandchild);
    my_ASSERT(result == grandchild);

    free_tree(root);
}

static void test_find_node_by_id()
{
    test_find_node_by_id_empty_tree();
    test_find_node_by_id_root_match();
    test_find_node_by_id_child_match();
    test_find_node_by_id_nested_match();
}
