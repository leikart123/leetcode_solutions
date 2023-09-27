/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#define FIELD_SIZE 12
#define DEFAULT_NUM_NODE 1024

void serialize_node(struct TreeNode *node, int **data, int *pos, int *size)
{
    int i = *pos * 3;
    if (*pos >= (*size / FIELD_SIZE) - 1)
    {
        *size *= 2;
        data[0] = (int *)realloc((void *)data[0], *size);
    }
    data[0][i] = node->val;

    if (node->left)
    {
        *pos += 1;
        data[0][i + 1] = *pos;
        serialize_node(node->left, data, pos, size);
    }
    if (node->right)
    {
        *pos += 1;
        data[0][i + 2] = *pos;
        serialize_node(node->right, data, pos, size);
    }
}

char* serialize(struct TreeNode* root) {
    int *result = NULL;
    int pos = 0;
    size_t size = FIELD_SIZE * DEFAULT_NUM_NODE;

    if (root)
    {
        result = (int *)malloc(size);
        memset(result, 0, size);
        serialize_node(root, &result, &pos, &size);
    }
    return (char *)result;
}

void deserialize_node(struct TreeNode *node, int *source_data, int *current)
{
    node->val = *current;
    if (current[1])
    {
        node->left = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        memset(node->left, 0, sizeof(struct TreeNode));
        deserialize_node(node->left, source_data, source_data + current[1] * 3);
    }
    if (current[2])
    {
        node->right = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        memset(node->right, 0, sizeof(struct TreeNode));
        deserialize_node(node->right, source_data, source_data + current[2] * 3);
    }
}

/** Decodes your encoded data to tree. */
struct TreeNode* deserialize(char* data) {
    struct TreeNode *root = NULL;

    if (data)
    {
        root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
        memset(root, 0, sizeof(struct TreeNode));
        deserialize_node(root, (int *)data, (int *)data);
    }
    return root;
}

// Your functions will be called as such:
// char* data = serialize(root);
// deserialize(data);