#include <iostream>
#include <vector>
#include <map>
using namespace std;
//题号：303：区域与检索：数组不可变
//给定一个整数数组  nums，处理以下类型的多个查询 :
//
//计算索引 left 和 right （包含 left 和 right）之间的 nums 元素的 和 ，其中 left <= right
//实现 NumArray 类：
//
//NumArray(int[] nums) 使用数组 nums 初始化对象
//int sumRange(int i, int j) 返回数组 nums 中索引 left 和 right 之间的元素的 总和 ，包含 left 和 right 两点（也就是 nums[left] + nums[left + 1] + ... + nums[right] )
//
//
//示例 1：
//
//输入：
//["NumArray", "sumRange", "sumRange", "sumRange"]
//[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
//输出：
//[null, 1, -1, -3]
//
//解释：
//NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
//numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3)
//numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1)) 
//numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))
//
//
//提示：
//
//1 <= nums.length <= 10^4
//- 10^5 <= nums[i] <= 10^5
//0 <= i <= j < nums.length
//	最多调用 10^4 次 sumRange 方法
//
// 
//如果按照常规的解法，就是每次用sumRange函数都是将left到right循环，遍历一遍，在时间复杂度为O(N)，在需要大量调用时，耗时很大
class NumArray {
private:
    vector<int> pre;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        pre.resize(n);
        for (int i = 0; i < nums.size(); i++)
        {
           pre[i] = nums[i];
        }
    }

    int sumRange(int left, int right) {
        int sum = 0;
        for(int i =left;i<=right;i++)
        {
            sum += pre[i];
            
         }
    }

};
//这个代码可以，但是耗时会比较大，最优解其实是计算前缀和，只执行一次循环在构造函数中，而将sumRange时间复杂度降到O（1）
class NumArray {
private:
    vector<int> pre;
public:
    NumArray(vector<int>& nums) {
        int n = nums.size();
        pre.resize(n + 1);
        for (int i = 0; i < nums.size(); i++)
        {
            pre[i + 1] = pre[i] + nums[i];
        }
    }

    int sumRange(int left, int right) {
        return pre[right + 1] - pre[left];
    }

};
//sumRange 函数需要计算并返回一个索引区间之内的元素和,这样，可以达到效果，但是效率很差，因为 sumRange 方法会被频繁调用，而它的时间复杂度是 O(N)，其中 N 代表 nums 数组的长度。

//这道题的最优解法是使用前缀和技巧，将 sumRange 函数的时间复杂度降为 O(1)，
//看这个 preSum 数组，如果我想求索引区间 [1, 4] 内的所有元素之和，就可以通过 preSum[5] - preSum[1] 得出。
//
//这样，sumRange 函数仅仅需要做一次减法运算，避免了每次进行 for 循环调用，最坏时间复杂度为常数 O(1)。
//
//这个技巧在生活中运用也挺广泛的，比方说，你们班上有若干同学，每个同学有一个期末考试的成绩（满分 100 分），那么请你实现一个 API，输入任意一个分数段，返回有多少同学的成绩在这个分数段内。
//
//那么，你可以先通过计数排序的方式计算每个分数具体有多少个同学，然后利用前缀和技巧来实现分数段查询的 API：
// 
// 
//总结：在处理到类似的序列和时，要先考虑到一些规律，尽可能的优化算法，此处的从left到right相加，可以转换成求前n个数的和的数组其中两个下标值的相减

//题号：304：二维区域和检索：矩阵不可变
//二维数组的前缀和
//遵循公式：S(O,D)=S(O,C)+S(O,B)−S(O,A)+D 来计算前缀数组
//S(A,D)=S(O,D)−S(O,E)−S(O,F)+S(O,G) ，通过前缀数组来求出指定区域的和
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        presum.resize(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                presum[i + 1][j + 1] = presum[i + 1][j] + presum[i][j + 1] + matrix[i][j] - presum[i][j];
            }
        }

    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        return presum[row2 + 1][col2 + 1] - presum[row1][col2 + 1] - presum[row2 + 1][col1] + presum[row1][col1];
    }
private:
    vector<vector<int>> presum;
};
//构造函数是O（m*n),求和函数是O(1)的复杂度
//还有一种是将二维数组，分成多行的一维数组的前缀和，只要长度多加1，在sumregion函数中要用循环，来求出相对的行的前缀和
class NumMatrix {
public:
    vector<vector<int>> sums;

    NumMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        if (m > 0) {
            int n = matrix[0].size();
            sums.resize(m, vector<int>(n + 1));
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    sums[i][j + 1] = sums[i][j] + matrix[i][j];
                }
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2) {
        int sum = 0;
        for (int i = row1; i <= row2; i++) {
            sum += sums[i][col2 + 1] - sums[i][col1];
        }
        return sum;
    }
};
//进阶：题号506：和为k的子数组
//给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。
//1.方法1：枚举，列举出所有的情况，用双层循环来枚举，外层循环是表示结尾的数组下标，内层的循环是表示结尾到下标为0的所有子数组，（有个小窍门：就是从末尾减到开头，每次加上离末尾最近的值，这样就可以不要再加一层循环，每个子数组就是一直往开头加值，不用重置，每一个子数组就是前一个子数组的值加上此时下标的值）
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int sum = 0;
        int count = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            sum = 0;
            for (int j = i; j >= 0; j--)
            {
                sum += nums[j];
                if (sum == k)
                    count++;
            }
        }
        return count;
    }

};
//这样的时间复杂度为O（n^2),在需要多次调用此函数的情况，十分浪费时间，提交到leetcode上会最后超时
//又或者先构造前缀数组，在通过循环来用前缀数组的两下标进行相减得到和的值。
/*int subarraySum(int[] nums, int k) {
    int n = nums.length;
    // 构造前缀和
    int[] preSum = new int[n + 1];
    preSum[0] = 0;
    for (int i = 0; i < n; i++)
        preSum[i + 1] = preSum[i] + nums[i];

    int res = 0;
    // 穷举所有⼦数组
    在线⽹站 labuladong的刷题三件套
        34 / 672
        for (int i = 1; i <= n; i++)
            for (int j = 0; j < i; j++)
                // ⼦数组 nums[j..i-1] 的元素和
                if (preSum[i] - preSum[j] == k)
                    res++;
    return res;
}
这个解法的时间复杂度 O(N ^ 2) 空间复杂度 O(N)，并不是最优的解法。不过通过这个解法理解了前缀和数
组的⼯作原理之后，可以使⽤⼀些巧妙的办法把时间复杂度进⼀步降低。*/
//还是需要O（n^2)的结果。还能进一步优化
//即前缀数组加上哈希表
// 在j~i中，如果满足大小，即pre[i]-pre[j-1]=k.因此pre【j-1]=pre[i]-k,而此时j是小于i的值，因此只要在不断创建前缀数组的过程中，将此时的前缀和作为关键字，出现的次数作为值，放入哈希表中。每新添加一个值进入哈希表中时，要同时通过关键字查找m[pre[i]-k]如果存在，则表示这个k成立。并且是在前缀数组不断形成的过程中，j《i的查找，避免了重复造成。而且下标为0之前是没有前缀数组的，就当作关键字为前缀0，出现次数为1就行。在查找时方便
//假设我们创建前缀数组的情况中，其实可以同步进行计算子数组为k的值
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int,int> mp;
        mp[0] = 1;
        int count = 0, pre = 0;
        for (auto& x : nums) {
            pre += x;
            if (mp.find(pre - k) != mp.end()) {
                count += mp[pre - k];
            }
            mp[pre]++;
        }
        return count;
    }
};
//应用哈希表的关键就是能够构建一个等式，表示两个值对应着同一个关键字，
