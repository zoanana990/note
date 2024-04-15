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

## Basic Calculator I, II
### [Basic Calculator II](https://leetcode.com/problems/basic-calculator-ii/)

Idea:
1. How to get the number
2. The precedence of number
   
archithmetic operator -> stack, we need to store previous number
1. we may need to get the last one
2. we may need to push the number

summary: Last in first out -> stack

Implementation: get a number
```c++
if (isdigit(c)) {
    num = num * 10 + (c - '0');
}
```

Implementation: get the precedence
We need to walk to the operator then use the last operator

Solution:
```c++
class Solution {
public:
    int calculate(string s) {
        int i = 0;
        return calculateHelper(s, i);
    }
    
private:
    int calculateHelper(const string& s, int& i) {
        stack<int> nums;
        char op = '+';
        int num = 0;
        
        while (i < s.size()) {
            char c = s[i++];
            if (isdigit(c)) {
                num = num * 10 + (c - '0');
            }
            if ((!isdigit(c) && c != ' ') || i == s.size()) {
                if (op == '+') {
                    nums.push(num);
                } else if (op == '-') {
                    nums.push(-num);
                } else if (op == '*') {
                    int prev = nums.top();
                    nums.pop();
                    nums.push(prev * num);
                } else if (op == '/') {
                    int prev = nums.top();
                    nums.pop();
                    nums.push(prev / num);
                }
                op = c;
                num = 0;
            }
        }
        
        int result = 0;
        while (!nums.empty()) {
            result += nums.top();
            nums.pop();
        }
        return result;
    }
};
```

Tracing the code:
```txt
s = "3+2*2"

initial value: op = '+', num = 0

i == 0: c = 3, i++ -> i = 1, num = 3, op = '+' (default)
i == 1: c = +, i++ -> i = 2, num = 3,
        op == '+' -> push num to stack, stack: 3,
        num = 0, op = '+'
i == 2: c = 2, i++ -> i = 3, num = 2, op = '+'
i == 3: c = *, i++ -> i = 4, num = 2,
        op == '+' -> push num to stack, stack: 3, 2
        num = 0, op = '*'
i == 4: c = 2, i++ -> i = 5,
        i == s.size(), op == '*', prev = stack.top() = 2,
        stack.pop() -> stack: 3
        stack.push(num * prev) = stack.push(2 * 2) = stack.push(4)
        op = 2, num = 0;
        stack: 3, 4

int result = 0;
while(!nums.empty())
    result += stack.top() -> result += 4 -> result = 4
    stack.pop -> stack: 3

    result += stack.top() -> result += 3 -> result = 7
    stack.pop -> stack:

return result;
```

### [Basic Calculator I](https://leetcode.com/problems/basic-calculator/)
Recursive Method, modify from the above:
```c++
class Solution {
public:
    int partial_calculate(string s, int& index) {
        int num = 0, n = s.size(), result = 0;
        stack<int> string_stack;
        char op = '+';

        while(index < n) {
            char c = s[index];
            index++;

            if(isdigit(c)) {
                num = num * 10 + (c - '0');
            }

            if(c == '(') {
                num = partial_calculate(s, index);
            }
                
            
            if((!isdigit(c) && c != ' ') || index == n) {
                if(op == '+')
                    string_stack.push(num);
                else if(op == '-')
                    string_stack.push(-num);
                
                if(c == ')')
                    break;
                op = c;
                num = 0;
            }
        }

        while(!string_stack.empty()) {
            result += string_stack.top();
            string_stack.pop();
        }

        return result;
    }
    int calculate(string s) {
        int index = 0;
        return partial_calculate(s, index);
    }
};
```

Iteration: here is brute force
**TODO**

### [394. Decode String](https://leetcode.com/problems/decode-string/description/)

Recursive Method
```c++
class Solution {
public:
    string decode(string s, int& index) {
        string pattern, result;
        int times = 0, n = s.size();

        while(index < n) {
            char c = s[index++];
            if(isdigit(c)) {
                times = times * 10 + (c - '0');
            } else if(c == '[') {
                pattern = decode(s, index);
                for(int i = 0; i < times; i++)
                    result.append(pattern);
                times = 0;
            } else if(c == ']') {
                break;
            } else if(isalpha(c)) {
                result.push_back(c);
            }
        }

        return result;
    }
    string decodeString(string s) {
        int index = 0;
        return decode(s, index);
    }
};
```

Stack Method
```c++
class Solution {
public:
    string decodeString(string s) {
        stack<int> countStack;
        stack<string> stringStack;
        string currentString;
        int k = 0;
        for (auto ch : s) {
            if (isdigit(ch)) {
                k = k * 10 + ch - '0';
            } else if (ch == '[') {
                // push the number k to countStack
                countStack.push(k);
                // push the currentString to stringStack
                stringStack.push(currentString);
                // reset currentString and k
                currentString = "";
                k = 0;
            } else if (ch == ']') {
                string decodedString = stringStack.top();
                stringStack.pop();
                // decode currentK[currentString] by appending currentString k times
                for (int currentK = countStack.top(); currentK > 0; currentK--) {
                    decodedString = decodedString + currentString;
                }
                countStack.pop();
                currentString = decodedString;
            } else {
                currentString = currentString + ch;
            }
        }
        return currentString;
    }
};
```

### [735. Asteroid Collision](https://leetcode.com/problems/asteroid-collision/description/)

deque solution:
```c++
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
        deque<int> store;

        for(auto asteroid: asteroids) {
            if(store.empty() && asteroid < 0) {
                ans.push_back(asteroid);
            } else if(asteroid > 0) {
                store.push_back(asteroid);
            } else if(asteroid < 0) {
                while(!store.empty()) {
                    int back = store.back();
                    if(back < abs(asteroid)) {
                        store.pop_back();
                        if(store.empty())
                            ans.push_back(asteroid);
                    }
                    else if(back == abs(asteroid)) {
                        store.pop_back();
                        break;
                    } else
                        break;
                }
            }
        }

        while(!store.empty()) {
            ans.push_back(store.front());
            store.pop_front();
        }

        return ans;
    }
};
```

From huahua
```c++
// Author: Huahua
// Runtime: 22 ms
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> s;
        for (int i = 0 ; i < asteroids.size(); ++i) {
            const int size = asteroids[i];
            if (size > 0) { // To right, OK
                s.push_back(size);
            } else {
                // To left
                if (s.empty() || s.back() < 0) // OK when all are negtives
                    s.push_back(size);
                else if (abs(s.back()) <= abs(size)) {
                    // Top of the stack is going right.
                    // Its size is less than the current one.
                    
                    // The current one still alive!
                    if (abs(s.back()) < abs(size)) --i;
                    
                    s.pop_back(); // Destory the top one moving right
                }                    
            }
        }
        
        // s must look like [-s1, -s2, ... , si, sj, ...]
        return s;
    }
};

```


But, i need to use stack!!!, the following solution is not mine,
This is garbage
```c++
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        stack<int> st;

        for (int asteroid : asteroids) {
            bool destroyed = false;
            while (!st.empty() && asteroid < 0 && st.top() > 0) {
                if (st.top() < -asteroid) {
                    st.pop();
                    continue;
                } else if (st.top() == -asteroid) {
                    st.pop();
                }
                destroyed = true;
                break;
            }
            if (!destroyed) {
                st.push(asteroid);
            }
        }

        vector<int> result(st.size());
        for (int i = st.size() - 1; i >= 0; --i) {
            result[i] = st.top();
            st.pop();
        }

        return result;
    }
};
```