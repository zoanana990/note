# 513. Find Bottom Left Tree Value



## BFS, origin
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
    int findBottomLeftValue(TreeNode* root) {
        int left;
        queue<TreeNode *> q;
        q.push(root);

        while(!q.empty()) {
            int n = q.size();
            for(int i = 0; i < n; i++) {
                TreeNode *node = q.front();
                q.pop();

                if(i == 0)
                    left = node->val;

                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }
        }

        return left;
    }
};
```

This direction is from top to bottom, and from left to right.

How to improve it? 
We can traverse from top to bottom and **from right to left**!
```c++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        int left;
        queue<TreeNode *> q;
        q.push(root);

        while(!q.empty()) {
            TreeNode *node = q.front();
            q.pop();

            left = node->val;
            if(node->right)
                q.push(node->right);

            if(node->left)
                q.push(node->left);
        }

        return left;
    }
};
```

Furthermore, we can reduce a variable
```c++
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        queue<TreeNode *> q;
        q.push(root);
        TreeNode *node;

        while(!q.empty()) {
            node = q.front();
            q.pop();

            if(node->right)
                q.push(node->right);

            if(node->left)
                q.push(node->left);
        }

        return node->val;
    }
};
```

## DFS
```c++
class Solution {
public:
    int left = 0;
    int max_depth = -1;
    void dfs(TreeNode *root, int depth) {
        if(root == nullptr)
            return;
        
        if(!root->left && !root->right && depth > max_depth) {
            max_depth = depth;
            left = root->val;
        }

        dfs(root->left, depth + 1);
        dfs(root->right, depth + 1);

    }
    int findBottomLeftValue(TreeNode* root) {
        dfs(root, 0);
        return left;
    }
};
```