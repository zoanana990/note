# Construct binary tree from two order array
Subjects:
- [Leetcode 105 construct-binary-tree-from-preorder-and-inorder-traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/)
- [Leetcode 106 construct-binary-tree-from-inorder-and-postorder-traversal](https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/)
- [Leetcode 889 construct-binary-tree-from-preorder-and-postorder-traversal](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/description/)

## General Ideas
```text
                     3
                    / \
                   9   20
                      /  \
                     15   7

order

                M   L       R
                m,  l, (m,  l,  r)
preorder:     [ 3,  9, 20, 15,  7]     -> if binary search tree, top - down

                L   M       R
                l,  m, (l,  m,  r)
inorder:      [ 9,  3, 15, 20,  7]     -> if binary search tree, ordered

                L       R       M
                l, (l,  r,  m), m
postorder:    [ 9, 15,  7, 20,  3]     -> if binary search tree, bottom - up
```

### Leetcode 105, Construct Binary Tree from Preorder and Inorder Traversal
```text
Inorder  Hashtable
   9         0
   3         1
  15         2
  20         3
   7         4
```

Solution:
```c
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++)
            map[inorder[i]] = i;

        return _buildTree(0, inorder.size() - 1, 0, inorder.size() - 1, preorder, map);
    }
    
    TreeNode* _buildTree(int preStart, int preEnd, int inStart, int inEnd, vector<int>& preorder, unordered_map<int, int>& map) {
        if (preStart > preEnd || inStart > inEnd) return nullptr;
        
        TreeNode* curr = new TreeNode(preorder[preStart]);
        int inIndex = map[curr->val];
        
        curr->left = _buildTree(preStart + 1, preEnd, inStart, inIndex - 1, preorder, map);
        curr->right = _buildTree(preStart + inIndex - inStart + 1, preEnd, inIndex + 1, inEnd, preorder, map);
        
        return curr;
    }
};
```

### Leetcode 106, Construct Binary Tree from Inorder and Postorder Traversal
```text
Inorder  Hashtable
   9         0
   3         1
  15         2
  20         3
   7         4
```

Solution:
```c
class Solution {
public:
    TreeNode* _buildTree(int inStart, int inEnd, int postStart, int postEnd, vector<int>& postorder, unordered_map<int, int>& map) {
        if(inStart > inEnd || postStart > postEnd) return NULL;
        TreeNode* curr = new TreeNode(postorder[postEnd]);
        int split = map[postorder[postEnd]];
        int left = split - inStart;
        int right = inEnd - split;
        curr->left = _buildTree(inStart, inStart + left-1, postStart, postStart + left-1, postorder, map);
        curr->right = _buildTree(inEnd-right+1, inEnd, postEnd-right, postEnd-1, postorder, map);
        return curr;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        unordered_map<int, int> map;
        for(int i = 0 ; i < n; i++)
            map[inorder[i]] = i;
        return _buildTree(0, n-1, 0, n-1, postorder, map);
    }
};
```

### Leetcode 889, Construct Binary Tree from Preorder and Postorder Traversal
```text
Preorder  Hashtable   Postorder
   3          0           9
   9          1          15
  20          2           7
  15          3          20
   7          4           3
```

Solution:
```c
class Solution {
public:
    TreeNode* _buildTree(int preStart, int preEnd, int postStart, int postEnd, vector<int>& preorder, unordered_map<int, int>& map) {
        if (preStart > preEnd || postStart > postEnd) return nullptr;
        
        TreeNode* curr = new TreeNode(preorder[preStart]);
        if (preStart == preEnd) return curr;

        int nextRootVal = preorder[preStart + 1];
        int nextRootIdxPost = map[nextRootVal];
        
        int leftSubtreeSize = nextRootIdxPost - postStart + 1;
        
        curr->left = _buildTree(preStart + 1, preStart + leftSubtreeSize, postStart, nextRootIdxPost, preorder, map);
        curr->right = _buildTree(preStart + leftSubtreeSize + 1, preEnd, nextRootIdxPost + 1, postEnd - 1, preorder, map);
        
        return curr;
    }

    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        int n = postorder.size();
        unordered_map<int, int> map;
        for (int i = 0; i < n; i++)
            map[postorder[i]] = i;

        return _buildTree(0, n - 1, 0, n - 1, preorder, map);
    }
};
```