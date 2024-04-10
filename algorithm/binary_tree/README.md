# Binary Tree

There are four critical operations in binary tree: add, delete, search and modify. Here, we need to practice different way to traverse the tree, including preorder, inorder and post order traversal. Furthermore, we need to learn different search way to recursive or iteratively search the tree, that is, depth first search (DFS) or backtracking and breadth first search (BFS).

To training those skills, we need to take lots of subjects, and we also need to use those method on graph and array.

We will introduce those patterns here so don't afraid of that.


> Note: Direction is the most important thing in binary tree !

## Traversal
### Template
In linked list
```c++
class ListNode {
    int val;
    ListNode next;
};

// iterative traversal
void iteration_tarverse(ListNode head) {
    for(...)
        iteration_tarverse(...)
}

// order traversal
void recursive_traverse(ListNode head) {

    // no matter which traverse it is,
    // check the boundary condition first

    //preorder traverse (do something before traverse)
    recursive_traverse(...)
    //postorder traverse (do something after traverse)
}
```

For example, there is a linked list. Please print the value of each node in preorder and postorder
```txt
1->2->3->4->5->6
```

> Note: the direction of preorder traversal is left to right

If i use preorder traversal, the sample code is like this:
```c++
void recursive_traverse(ListNode head) {
    printf("%d ", head.val);
    recursive_traverse(head.next);
}
```
and the result is
```txt
1 2 3 4 5 6
```
> Note: the direction of preorder traversal is right to left

If I use the postorder traversal, the sample code is like this:
```c++
void recursive_traverse(ListNode head) {
    recursive_traverse(head.next);
    printf("%d ", head.val);
}
```
and the result is
```txt
6 5 4 3 2 1
```

In binary tree, there is three kinds of order traversal, preorder, inorder and postorder

and the basic template we use is like this:
```c++
class TreeNode {
    int val;
    TreeNode left, right;
};

void traverse(TreeNode root) {

    // no matter which traverse it is,
    // check the boundary condition first

    //preorder traverse
    traverse(root->left)
    //inorder traverse
    traverse(root->right)
    //postorder traverse
}
```

And we can use this template to pass following example

### [Inorder Traversal](https://leetcode.com/problems/binary-tree-inorder-traversal/)
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
    void inorder(TreeNode *root, vector<int>& ans) {
        if(root==nullptr)
            return;

        inorder(root->left, ans);
        ans.push_back(root->val);
        inorder(root->right, ans);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        if(root==nullptr)
            return {};
        vector<int> ans;
        inorder(root, ans);
        return ans;
    }
};
```
more subjects, [preorder traversal](https://leetcode.com/problems/binary-tree-preorder-traversal/) and [postorder traversal](https://leetcode.com/problems/binary-tree-postorder-traversal/description/)

The concept of traversal is the fundamental essence of backtracking.

And there is a traversal method, we do not use, which is level order traversal, and that is, BFS(breath first search)

### [Level order traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/description/)

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if(root == nullptr)
            return {};

        vector<vector<int>> ans;
        queue<TreeNode *> q;

        q.push(root);

        while(!q.empty()) {
            int n = q.size();
            vector<int> order;

            for(int i = 0; i < n; i++) {
                TreeNode *node = q.front();
                q.pop();

                order.push_back(node->val);
                if(node->left)
                    q.push(node->left);
                if(node->right)
                    q.push(node->right);
            }

            ans.push_back(order);
        }

        return ans;
    }
};
```
#### Some challange here
Can you use DFS to solve this ?

> Note: this is preorder traversal, notice the direction!
```c++
class Solution {
public:
    void dfs(TreeNode *root, vector<vector<int>>& ans, int depth) {
        if(root == nullptr)
            return;

        if(ans.size() <= depth) 
            ans.push_back({});

        ans[depth].push_back(root->val);
        dfs(root->left, ans, depth + 1);
        dfs(root->right, ans, depth + 1);
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        int depth = 0;
        dfs(root, ans, depth);
        return ans;
    }
};
```

### Summary
![](image.png)

## Search
### Backtracking

## Example

## Reference
- [Leetcode刷題學習筆記–Tree Traversal](https://hackmd.io/@meyr543/r1lbVkb-K)