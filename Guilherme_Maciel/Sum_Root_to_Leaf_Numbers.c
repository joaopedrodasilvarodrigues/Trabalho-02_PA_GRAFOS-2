/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int dfs(struct TreeNode* root, int n); 
int sumNumbers(struct TreeNode* root) {
    return dfs(root, 0);
}
int dfs(struct TreeNode* root, int n) {
    n = root->val + n * 10 ;
    if (root->right  == NULL && root->left == NULL) {
        return n;
    }
    return dfs(root->right, n)+ dfs(root->left, n);
    }
