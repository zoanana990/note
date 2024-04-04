# 1353. Maximum Number of Events That Can be Attended

tags: Greedy, priority queue

Brute force, use a set and give every 
```c++
class Solution {
public:
    static bool cmp(vector<int>& a,vector<int>& b)
    {
        if(a[1]<b[1])return true;
        else if(a[1]==b[1]) return a[0]<b[0];
        return false;
    }
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(),events.end(),cmp);
        set<int>days;
        int cnt=0;
        int max_end_day = 0;
        int n = events.size();
        for (int i = 0; i < n; ++i) {
            max_end_day = max(max_end_day, events[i][1]);
        }
        for(int i= 1 ;i<=max_end_day;++i)
        {
            days.insert(i);
        }
        for(const auto & event : events)
        {
            int s = event[0];
            int e = event[1];
            auto it = days.lower_bound(s);
            if(it == days.end() || *it >e)
            {
                continue;
            }
            else
            {
                ++cnt;
                days.erase(it);
            }
        }
        return cnt;
    }
};
```

priority queue:
```c++
class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        int n = events.size();
        sort(events.begin(), events.end());

        // 這邊我預設由小排到大
        // 然後我們只會把 [1] 排進去
        priority_queue<int, vector<int>, greater<int>> pq;
        int count = 0;
        
        int max_end_day = 0;
        for (int i = 0; i < n; ++i) {
            max_end_day = max(max_end_day, events[i][1]);
        }
        
        for (int day = 1, i = 0; day <= max_end_day; ++day) {
            // 將當前結束時間小於當前日期的事件從優先佇列中移除
            while (!pq.empty() && pq.top() < day) {
                pq.pop();
            }
            
            // 將當前日期開始的事件加入優先佇列
            while (i < n && events[i][0] == day) {
                pq.push(events[i++][1]);
            }
            
            // 如果優先佇列非空，則參加當前日期結束時間最早的事件
            if (!pq.empty()) {
                pq.pop();
                count++;
            }
        }
        
        return count;
    }
};
```


refer to [note](https://yuihuang.com/cpp-stl-priority-queue/) for priority queue