# Solution

This document is a solution of the [leetcode 51. insert interval](https://leetcode.com/problems/insert-interval/submissions/1221120194/)

category: `array`

In this subject, there are several cases we need to discuss:
1. no merge condition
   1. the interval upper bound is less than the lower bound of the inserted interval
   2. the interval lower bound is greater than the upper bound of inserted interval
2. merge condition: cross multiple intervals
   
Therefore, there are only three condition we need to consider

Thus, let's write a pesudo code:
```
function insert_interval
    answer;

    while(the interval upper bound is less than the lower bound of the inserted interval)
        answer push_back the interval

    while(merge condition)
        update the inserted condition

    after the condition is updated, answer push_back the inserted interval

    while( the interval lower bound is greater than the upper bound of inserted interval)
        answer push_back the inserted interval

    return answer;
```

the code in `C++`

```c++
class Solution {
public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector<vector<int>> merged;
        int i = 0, n = intervals.size();

        while (i < n && intervals[i][1] < newInterval[0]) {
            merged.push_back(intervals[i]);
            i++;
        }

        while (i < n && intervals[i][0] <= newInterval[1]) {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        merged.push_back(newInterval);

        while (i < n) {
            merged.push_back(intervals[i]);
            i++;
        }

        return merged;
    }
};
```