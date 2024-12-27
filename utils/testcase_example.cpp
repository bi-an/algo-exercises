#include <fstream>
#include <iostream>
#include <json/json.h>  // 使用 JSON 库
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashMap;
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            if (hashMap.find(complement) != hashMap.end()) {
                return {hashMap[complement], i};
            }
            hashMap[nums[i]] = i;
        }
        return {};  // 如果没有找到解决方案
    }
};

int main() {
    // 读取文件中的测试用例
    ifstream file("test_cases.json");
    stringstream buffer;
    buffer << file.rdbuf();
    string jsonString = buffer.str();

    // 解析 JSON 数据
    Json::Reader reader;
    Json::Value testCases;
    reader.parse(jsonString, testCases);

    Solution sol;

    // 遍历并运行每个测试用例
    for (const auto& testCase : testCases) {
        vector<int> nums;
        for (auto& x : testCase["nums"])
            nums.push_back(x.asInt());
        int target = testCase["target"].asInt();
        vector<int> expected;
        for (auto& x : testCase["expected"])
            expected.push_back(x.asInt());

        // 调用 solution 函数
        vector<int> result = sol.twoSum(nums, target);

        // 比较结果并输出
        if (result == expected) {
            cout << "Test passed!" << endl;
        } else {
            cout << "Test failed!" << endl;
        }
    }

    return 0;
}
