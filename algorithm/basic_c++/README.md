# Basic C++ skill

## sort and custom sorting function
```c++
#include <iostream>
#include <vector>
#include <algorithm>

bool compare(const std::vector<int>& a, const std::vector<int>& b) {
    return a[1] < b[1];
}

int main() {
    std::vector<std::vector<int>> vec = {{1, 2}, {13, 15}, {1, 5}};
    std::sort(vec.begin(), vec.end(), compare);

    for (const auto& v : vec) {
        std::cout << "{" << v[0] << ", " << v[1] << "} ";
    }
    std::cout << std::endl;

    return 0;
}
```


## print the vector
```c++
for(auto i: intervals)
    cout << "{" << i[0] << ", " <<  i[1] << "}, ";
cout << endl;
```