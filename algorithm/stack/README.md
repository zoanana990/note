# stack

## Monotonic stack

### Template
> Note: This is really skill!
```c++
// test case: [2,1,2,4,3]
vector<int> nextGreaterElement(vector<int>& nums) {
    vector<int> ans(nums.size());
    stack<int> s;

    for(int i = nums.size() - 1; i >= 0; i--) {
        while(!s.empty() && s.top() <= nums[i]) {
            s.pop();
        }

        ans[i] = s.empty() ? -1 : s.top();
        s.push(nums[i]);
    }

    return ans;
}
```

> Due to the property of stack, we need to use for-loop iterate from the last element!

### Example
[Leetcode 150 Evaluate Reverse Polish Notation](https://leetcode.com/problems/evaluate-reverse-polish-notation/description/)

Brute Force:
```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if(tokens.empty())
            return 0;
        // get the value first
        string token = tokens.back();
        tokens.pop_back();

        // check it is the operator or the value
        if(token == "+" || token == "-" || token == "*" || token == "/") {
            int right = evalRPN(tokens);
            int left = evalRPN(tokens);

            if(token == "+")
                return left + right;
            else if(token == "-")
                return left - right;
            else if(token == "*")
                return left * right;
            else if(token == "/")
                return left / right;
        }

        return stoi(token);
    }
};
```

Stack solution:
```c++
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        unordered_map<string, function<int (int, int) > > map = {
            { "+" , [] (int a, int b) { return a + b; } },
            { "-" , [] (int a, int b) { return a - b; } },
            { "*" , [] (int a, int b) { return a * b; } },
            { "/" , [] (int a, int b) { return a / b; } }
        };
        std::stack<int> stack;
        for (string& s : tokens) {
            if (!map.count(s)) {
                stack.push(stoi(s));
            } else {
                int op1 = stack.top();
                stack.pop();
                int op2 = stack.top();
                stack.pop();
                stack.push(map[s](op2, op1));
            }
        }
        return stack.top();
    }
};
```

## Stack Property
> Note: Utilize the property of stack, first in last out!!!
### [232. Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/description/)
```c++
class MyQueue {
    stack<int> in, out;
public:
    MyQueue() {}
    
    void push(int x) {
        while(!out.empty()) {
            in.push(out.top());
            out.pop();
        }
        in.push(x);
    }
    
    int pop() {
        while(!in.empty()) {
            out.push(in.top());
            in.pop();
        }
        int ret = out.top();
        out.pop();
        return ret;
    }
    
    int peek() {
        while(!in.empty()) {
            out.push(in.top());
            in.pop();
        }
        return out.top();
    }
    
    bool empty() {
        return out.empty() && in.empty();
    }
};
```

### [155. Min Stack](https://leetcode.com/problems/min-stack/description/)
> Note: Utilize the property of stack, first in last out!!!
```c++
class MinStack {
    stack<int> s, min_stack;
public:
    MinStack() {}
    
    void push(int val) {
        s.push(val);
        if(min_stack.empty() || min_stack.top() >= val)
            min_stack.push(val);
    }
    
    void pop() {
        if(s.top() == min_stack.top())
            min_stack.pop();
        s.pop();
    }
    
    int top() {
        return s.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
};
```

### [Leetcode 32. Longest Valid Parentheses](https://leetcode.com/problems/longest-valid-parentheses/description/)

Brute Force then **FAIL**
```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<char> ps;
        int count = 0;
        for(auto ss : s) {
            if(ss == '(')
                ps.push(ss);
            else {
                if(ps.empty())
                    continue;
                if(ps.top() == '(') {
                    ps.pop();
                    count += 2;
                }
            }
        }
        return count;
    }
};
```

This solution do not consider the `Longest` situation, it will failed in this case:
```
()(()
```

The longest length expect 2, and get 4

Thus we need to fixed this problem by change the stack template

```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> ps;
        int count = 0, n = s.size();
        ps.push(-1);
        for(int i = 0; i < n; i++) {
            int top = ps.top();
            if(i > 0 && top > -1 && s[i] == ')' && s[top] == '(') {
                ps.pop();
                count = max(count, i - ps.top());
            } else {
                ps.push(i);
            }
        }

        return count;
    }
};
```

However, the condition in the branch condition is very complex, and we need to simplify that
```c++
class Solution {
public:
    int longestValidParentheses(std::string s) {
        std::stack<int> st;
        st.push(-1); // Push -1 onto the stack as a base index

        int maxLen = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                // Push index of '(' onto the stack
                st.push(i); 
            } else {
                // Pop '(' index since we encountered ')'
                st.pop(); 

                // the stack empty is designed for the first character is ')'
                if (st.empty()) {
                    // Push current index onto the stack to mark a new starting point
                    st.push(i); 
                } else {
                    // Update maxLen
                    maxLen = std::max(maxLen, i - st.top()); 
                }
            }
        }

        return maxLen;
    }
};
```

And here, we can use different solution for this problem, that is, dynamic programming
```c++
class Solution {
public:
    int longestValidParentheses(string s) {
        int n = s.size();
        int res = 0;
        vector<int> dp(n, 0);
        for (int i = 0; i < n; i++) {
            if (i > 0 && s[i] == ')') {
                if (s[i-1] == '(') {
                    int val = i - 2 >= 0 ? dp[i-2] : 0;
                    dp[i] = 2 + val;
                } else {
                    int ind = i - dp[i-1] - 1;
                    if (ind >= 0 && s[ind] == '(') {
                        int val = ind > 0 ? dp[ind - 1] : 0;
                        dp[i] = 2 + dp[i-1] + val;
                    }
                }
                res = max(res, dp[i]);
            }
        }
        return res;
    }
};
```