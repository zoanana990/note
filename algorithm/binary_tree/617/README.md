# 617. Merge Two Binary Trees

Brute force:
```c++
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1 == nullptr && root2 == nullptr)
            return nullptr;
        
        TreeNode *node;
        if(root1 && root2){
            node = new TreeNode(root1->val + root2->val);
            node->left = mergeTrees(root1->left, root2->left);
            node->right = mergeTrees(root1->right, root2->right);
        }
        else if(root1) {
            node = new TreeNode(root1->val);
            node->left = mergeTrees(root1->left, nullptr);
            node->right = mergeTrees(root1->right, nullptr);
        } else if(root2) {
            node = new TreeNode(root2->val);
            node->left = mergeTrees(nullptr, root2->left);
            node->right = mergeTrees(nullptr, root2->right);
        }

        return node;
    }
};
```

We can simplify to following:
```c++
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
        if(root1 == nullptr && root2 == nullptr)
            return nullptr;

        if(root2 == nullptr)
            return root1;
        
        if(root1 == nullptr)
            return root2;
        
        TreeNode *node = new TreeNode(root1->val + root2->val);
        node->left = mergeTrees(root1->left, root2->left);
        node->right = mergeTrees(root1->right, root2->right);

        return node;
    }
};
```