# 91. Decode way

## Recursion

```txt

```

recursion + memorization
```c++
class Solution {
    // memorization
    unordered_map<string, int> dic;
public:
    int numDecodings(string s) {
        if(s.length() == 0)
            return 0;

        dic[""] = 1;
        return dfs(s);
    }

    int dfs(const string &s){
        if(dic.count(s))
            return dic[s];
        
        if(s[0] == '0')
            return 0;
        
        if(s.length() == 1)
            return 1;
        
        int w = dfs(s.substr(1));
        const int prefix = stoi(s.substr(0,2));

        if(prefix <= 26)
            w += dfs(s.substr(2));
        
        dic[s] = w;
        return dic[s]; 
    }
};
```

## dp
