# Sliding Window

> Sliding window has a fixed template to use, so please grasp this topic and practice.


## Template
```c++
int left = 0, right = 0, n = nums.size();

// boundary condition
while(right < n) {
    windos.add(nums[right]);
    while(/* window need to shrink*/) {
        window.remove(nums[left]);
        left++;
    }
}
```
