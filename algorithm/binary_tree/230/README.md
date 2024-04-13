# 230

original
```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void dfs(TreeNode *root, vector<int>& elements) {
        if(root == nullptr)
            return;
        
        dfs(root->left, elements);
        elements.push_back(root->val);
        dfs(root->right, elements);
    }
    int kthSmallest(TreeNode* root, int k) {
        vector<int> elements;
        dfs(root, elements);
        return elements[k - 1];
    }
};
```

optimize
```c++
class Solution {
public:
   int kthSmallest(TreeNode* root, int& k) {
        if (!root) {
            return -1;
        }
        
        int x = kthSmallest(root->left, k);
        if (x != -1) {
            return x;
        }
        
        if (--k == 0) {
            return root->val;
        }
        
        return kthSmallest(root->right, k);
    }
};
```