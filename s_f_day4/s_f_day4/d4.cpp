#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;
//双指针解决七道数组题
//在处理数组和链表相关问题时，双指针技巧是经常⽤到的，双指针技巧主要分为两类：左右指针和快慢指针。
//所谓左右指针，就是两个指针相向⽽⾏或者相背⽽⾏；⽽所谓快慢指针，就是两个指针同向⽽⾏，⼀快⼀慢。
//对于单链表来说，⼤部分技巧都属于快慢指针，前⽂ 单链表的六⼤解题套路 都涵盖了，⽐如链表环判断，倒数第 K 个链表节点等问题，它们都是通过⼀个 fast 快指针和⼀个 slow 慢指针配合完成任务。
//在数组中并没有真正意义上的指针，但我们可以把索引当做数组中的指针，这样也可以在数组中施展双指针技巧，本⽂主要讲数组相关的双指针算法。

//快慢指针
//删除有序数组或者有序链表中的重复元素
// 
// 
//题号：26：删除有序数组中的有序项
// 
//我自己感觉的双指针技巧：a指针指向现在的待定项,b指针指向接下的值，如果相等，则b指针后移，如果不相等，说明此时的待定项重复数完了，将a指针后移，并将b此时指的值继续赋给a，循环直到b超出范围。
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int right = 1;
        int left = 0;
        if (nums.size() < 2)
            return 1;
        int num = 1;
        while (right < nums.size())
        {
            if (nums[left] == nums[right])
            {
                right++;
            }
            else if (nums[left] != nums[right])
            {
                left++;
                nums[left] = nums[right];
                num++;
                right++;
            }
        }
        return num;
    }
};
//时间复杂度为O(n)
// 
//教程:题目要求原地修改，不能够建立一个新的数组来存放不重复的数组，只能在原地修改完后指定此时数组的长度来给出一个数组。如果是每遇到一个重复的数就删除他，每个值都得要往前移动，一趟下来时间复杂度为O(N^2)，不理想
//如果需要高效的解决问题就需要快慢指针：我们让慢指针 slow ⾛在后⾯，快指针 fast ⾛在前⾯探路，找到⼀个不重复的元素就赋值给 slow 并让slow 前进⼀步。这样，就保证了 nums[0..slow] 都是⽆重复的元素，当 fast 指针遍历完整个数组 nums 后，nums[0..slow] 就是整个数组去重之后的结果。
//这就是我自己的想出来的办法！！！！！！
int removeDuplicates(vector<int> nums) {
    if (nums.size() == 0) {
        return 0;
    }
    int slow = 0, fast = 0;
    while (fast < nums.size()) {
        if (nums[fast] != nums[slow]) {
            slow++;
            // 维护 nums[0..slow] ⽆重复
            nums[slow] = nums[fast];
        }
        fast++;
    }
    // 数组⻓度为索引 + 1
    return slow + 1;
}
//将运用到数组上的思想类比到链表的有序链表去掉重复上，也只是将下标换成指针而已
//题号83：删除排序链表中的重复元素
//我的办法：与数组的类似
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* slow, * fast;
        if (!head)
            return head;
        slow = head;
        fast = head;
        while (fast->next)//这一步可以不用过多的考虑到fast最后一个要更新的情况，因为将最后一个元素按照之前的方法处理完后，跳出循环后将slow->next置为NULL就可以解决，也就是教程的方法
        {
            if (slow->val == fast->val)
            {
                fast = fast->next;
            }
            else
            {
                slow->next = fast;
                slow = slow->next;
                fast = fast->next;
            }
        }
        if (fast->val == slow->val)
        {
            slow->next = NULL;
        }
        else {
            slow->next = fast;
        }
        return head;

    }
};
//
//教程：跟我像的差不多一样
ListNode* deleteDuplicates(ListNode* head) {
    if (head == NULL) return NULL;
    ListNode* slow = head, *fast = head;
    while (fast != NULL) {
        if (fast->val != slow->val) {
            // nums[slow] = nums[fast];
            slow->next = fast;
            // slow++;
            slow = slow->next;
        }
            // fast++
            fast = fast->next;
    }
    // 断开与后⾯重复元素的连接
    slow->next = NULL;
    return head;
}
//lettcode官方的解答会更加巧妙一点，只用了一个指针的情况就结束了，用到其实也是双指针的技巧，就是将一个指针和其-》next作为两个指针
//理解！
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) {
            return head;
        }

        ListNode* cur = head;
        while (cur->next) {
            if (cur->val == cur->next->val) {
                cur->next = cur->next->next;
            }
            else {
                cur = cur->next;
            }
        }

        return head;
    }
};
//具体地，我们从指针 \textit{cur}cur 指向链表的头节点，随后开始对链表进行遍历。如果当前 \textit{cur}cur 与 \textit{cur.next}cur.next 对应的元素相同，那么我们就将 \textit{cur.next}cur.next 从链表中移除；否则说明链表中已经不存在其它与 \textit{cur}cur 对应的元素相同的节点，因此可以将 \textit{cur}cur 指向 \textit{cur.next}cur.next。当遍历完整个链表之后，我们返回链表的头节点即可。
//细节：当我们遍历到链表的最后一个节点时，\textit{ cur.next }cur.next 为空节点，如果不加以判断，访问 \textit{ cur.next }cur.next 对应的元素会产生运行错误。因此我们只需要遍历到链表的最后一个节点，而不需要遍历完整个链表。
//
//除了让你在有序数组/链表中去重，题⽬还可能让你对数组中的某些元素进⾏「原地删除」。
//题号27：移除元素
//我自己的想法是用双指针，slow指针指的是当前要存储新的元素的位置，而fast指针则负责进行在前面的探测，如果是要删除的值，则忽略，如果不是，则将其放在slow指针的位置，在slow指针和fast指针后移
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0)
        {
            return 0;
        }
        int fast = 0;
        int slow = 0;
        int num = 0;//num可以删去了，因为slow在记录存放位置同时也兼顾计数的作用
        while (fast < nums.size() && slow < nums.size())
        {
            if (nums[fast] == val)
            {
                fast++;

            }
            else
            {
                nums[slow] = nums[fast];
                num++;
                slow++;
                fast++;
            }
        }
        return num;
    }
};
//
//教程：题⽬要求我们把 nums 中所有值为 val 的元素原地删除，依然需要使⽤快慢指针技巧：如果 fast 遇到值为 val 的元素，则直接跳过，否则就赋值给 slow 指针，并让 slow 前进⼀步。
int removeElement(vector<int> nums, int val) {
    int fast = 0, slow = 0;
    while (fast < nums.size()) {
        if (nums[fast] != val) {
            nums[slow] = nums[fast];
            slow++;
        }
        fast++;
    }
    return slow;
}
//lettcode的题解进行优化：注意到题目的不考虑删除特定元素后的数组中元素的顺序，如果要删除的元素刚好在开头，那么就需要将所有元素都往前移一位，但是如果此时将最后一个元素复制到前面来，就避免了要移位的情况，故在val的元素较少的时候，可以进行这种方法更加快捷。
// 同样是使用双指针，不过分别在数组的首尾，向中间移动遍历该序列
//如果左指针 \textit{left}left 指向的元素等于 \textit{val}val，此时将右指针 \textit{right}right 指向的元素复制到左指针 \textit{left}left 的位置，然后右指针 \textit{right}right 左移一位。如果赋值过来的元素恰好也等于 \textit{val}val，可以继续把右指针 \textit{right}right 指向的元素的值赋值过来（左指针 \textit{left}left 指向的等于 \textit{val}val 的元素的位置继续被覆盖），直到左指针指向的元素的值不等于 \textit{val}val 为止。
//当左指针 \textit{ left }left 和右指针 \textit{ right }right 重合的时候，左右指针遍历完数组中所有的元素。
//这样的方法两个指针在最坏的情况下合起来只遍历了数组一次。与方法一不同的是，方法二避免了需要保留的元素的重复赋值操作。
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size();
        while (left < right) {
            if (nums[left] == val) {
                nums[left] = nums[right - 1];
                right--;
            }
            else {
                left++;
            }
        }
        return left;
    }
};
//这样的方法两个指针在最坏的情况下合起来只遍历了数组一次。与方法一不同的是，方法二避免了需要保留的元素的重复赋值操作。
//
//还有一种方法也很巧妙，将要删除的元素放在后面，而将其他元素放在最前面
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int j = nums.size() - 1;
        for (int i = 0; i <= j; i++) {
            if (nums[i] == val) {
                swap(nums[i--], nums[j--]);//精髓在这里的i--上，i会重复检查此时交换后的值，i--，在经过i++，又会回到原来的位置上，所以不用担心交换到的是要删除的值
            }
        }
        return j + 1;
    }
};
//
//题号：283：移动零
//相当于是前一道题的删除特定元素换成0，而将后面全部补为0即可。要记住这种思想，将一种有点另类的题型，换成自己学过的.
//我是收到了之前一种解法的影响，首先想的是将前面的元素与后面的元素交换，但是发现要保持非0元素的相对位置
//所以还是用的是双指针的方法，一个表示的是要存储的位置，另一个地方表示的是现在检测到的值
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int fast = 0, slow = 0;
        for (auto x : nums)
        {
            if (x != 0)
            {
                nums[slow] = x;
                slow++;
            }
        }
        for (int i = slow; i < nums.size(); i++)
        {
            nums[i] = 0;
        }
    }
};
//数组中另⼀⼤类快慢指针的题⽬就是「滑动窗⼝算法」。那个有专门的专题探讨，这里就做一个简单的了解，具体的题⽬本⽂就不重复了，这⾥只强调滑动窗⼝算法的快慢指针特性：left 指针在后，right 指针在前，两个指针中间的部分就是「窗⼝」，算法通过扩⼤和缩⼩「窗⼝」来解决某些问题。
//

//左右指针的常用算法：二分查找（只是最简单的二分搜索，后面会有专题讲的），反转数组，两数之和，回文串的判断
//二分查找
/*int binarySearch(int[] nums, int target) {
    // ⼀左⼀右两个指针相向⽽⾏
    int left = 0, right = nums.length - 1;
    while (left <= right) {
        int mid = (right + left) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            left = mid + 1;
        else if (nums[mid] > target)
            right = mid - 1;
    }
    return -1;
}*/
//旨在突出双指针的特性
//题号167：两数之和（数组有序）
//因为数组有序，就应该想到可以用到双指针，左右分别指向的是最大和最小，或者是类似于二分查找，通过调节 left 和 right 就可以调整 sum 的⼤⼩：
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;
        int number;
        while (left < right)
        {
            number = numbers[left] + numbers[right];
            if (number == target)
            {
                return{ left + 1,right + 1 };
            }
            else if (number > target)
            {
                right--;//相当于此时的left+right已经》target，所以此时left一直++都一定会越来越大，所以不满足，一次性就排除了很多
            }
            else
            {
                left++;//类似，此时的left+right《target，所以此时的right--会一直越来越小，一定不满足，一次性消掉列，类似于杨氏矩阵a
            }
        }
        return { -1,-1 };
    }
};
//反转数组：
//题号344：反转字符串，要求原地修改，将字符串（字符数组）反转过来
//还是运用了双指针的技巧，左右指针，一个指针指向开头，一个指针指向结尾，两两交换，在left++，right--，直到left》=right为止，全部的字符都颠倒
class Solution {
public:
    void reverseString(vector<char>& s) {
        int left, right;
        left = 0;
        right = s.size() - 1;
        char temp;
        while (left < right)
        {
            temp = s[left];
            s[left] = s[right];
            s[right] = temp;
            left++;
            right--;
        }
        return;
    }
};
//教程和我想的差不多
//
//回文串判断：aba，abba都是回文串，判断是否是回文串很简单，
bool isPalindrome(string s) {
    // ⼀左⼀右两个指针相向⽽⾏
    int left = 0, right = s.length() - 1;
    while (left < right) {
        if (s[left] != s[right]) {
            return false;
        }
        left++;
        right--;
    }
    return true;
}
//进阶版，判断最长的回文串：
//题号5；最长回文子串（不能是其本身，要是子串）
//这题实在没想到
// 
// 
// 
//教程（中心扩展法）：找回⽂串的难点在于，回⽂串的的⻓度可能是奇数也可能是偶数，解决该问题的核⼼是从中⼼向两端扩散的双指针技巧。
//如果回⽂串的⻓度为奇数，则它有⼀个中⼼字符；如果回⽂串的⻓度为偶数，则可以认为它有两个中⼼字
//符。所以我们可以先实现这样⼀个函数：
string palindore(string s, int l, int r)
{
    while (l >= 0 && r < s.size() && s[l] == s[r])
    {
        l--;
        r++;
    }
    return s.substr(l + 1, r - l - 1);
}
//找最长回文串的过程：for 0 <= i < len(s):找到以 s[i] 为中⼼的回⽂串，找到以 s[i] 和 s[i + 1] 为中⼼的回⽂串，更新答案
class Solution {
public:
    string longestPalindrome(string s) {
        string t = "";
        for (int i = 0; i < s.size(); i++)
        {
            string s1 = palindore(s, i, i);
            string s2 = palindore(s, i, i + 1);
            t = t.size() > s1.size() ? t : s1;
            t = t.size() > s2.size() ? t : s2;
        }
        return t;
    }
    string palindore(string s, int l, int r)
    {
        while (l >= 0 && r < s.size() && s[l] == s[r])
        {
            l--;
            r++;
        }

        return s.substr(l + 1, r - l - 1);
    }

};
//时间复杂度为O（2n）=O（n）
//另外的方法：动态规划：
// 对于一个子串来说，如果的是回文串，并且其长度大于2，那么将他的头尾字母去掉后，也同样是一个回文串，如aba-》b，将p（i，j）定义为从i到j的子串，那么p（i，j）=p（i+1，j-1）并上s【i】==s【j】，满足这个条件p【i】【j】才为真，
// 还要考虑动态规划的边界问题，就是长度在1和2的时候，长度为1肯定是回文串，但是如果长度为2就要进行比较，i和i+1是否相等
using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n < 2) {
            return s;
        }

        int maxLen = 1;
        int begin = 0;
        // dp[i][j] 表示 s[i..j] 是否是回文串
        vector<vector<int>> dp(n, vector<int>(n));
        // 初始化：所有长度为 1 的子串都是回文串
        for (int i = 0; i < n; i++) {
            dp[i][i] = true;
        }
        // 递推开始
        // 先枚举子串长度
        for (int L = 2; L <= n; L++) {
            // 枚举左边界，左边界的上限设置可以宽松一些
            for (int i = 0; i < n; i++) {
                // 由 L 和 i 可以确定右边界，即 j - i + 1 = L 得
                int j = L + i - 1;
                // 如果右边界越界，就可以退出当前循环
                if (j >= n) {
                    break;
                }

                if (s[i] != s[j]) {
                    dp[i][j] = false;
                }
                else {
                    if (j - i < 3) {
                        dp[i][j] = true;
                    }
                    else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }

                // 只要 dp[i][L] == true 成立，就表示子串 s[i..L] 是回文，此时记录回文长度和起始位置
                if (dp[i][j] && j - i + 1 > maxLen) {
                    maxLen = j - i + 1;
                    begin = i;
                }
            }
        }
        return s.substr(begin, maxLen);
    }
};
//时间复杂度为O(n^2),其中n是字符串的长度，动态规划的状态总数为O(n^2),对于每个状态，移动的时间为O（1），空间复杂度为O（N^2),需要存储动态规划的时间
// 专门处理回文串的算法：马拉车算法（manacher算法）
class Solution {
public:
    int expand(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            --left;
            ++right;
        }
        return (right - left - 2) / 2;
    }

    string longestPalindrome(string s) {
        int start = 0, end = -1;
        string t = "#";
        for (char c : s) {
            t += c;
            t += '#';
        }
        t += '#';
        s = t;

        vector<int> arm_len;
        int right = -1, j = -1;
        for (int i = 0; i < s.size(); ++i) {
            int cur_arm_len;
            if (right >= i) {
                int i_sym = j * 2 - i;
                int min_arm_len = min(arm_len[i_sym], right - i);
                cur_arm_len = expand(s, i - min_arm_len, i + min_arm_len);
            }
            else {
                cur_arm_len = expand(s, i, i);
            }
            arm_len.push_back(cur_arm_len);
            if (i + cur_arm_len > right) {
                j = i;
                right = i + cur_arm_len;
            }
            if (cur_arm_len * 2 + 1 > end - start) {
                start = i - cur_arm_len;
                end = i + cur_arm_len;
            }
        }

        string ans;
        for (int i = start; i <= end; ++i) {
            if (s[i] != '#') {
                ans += s[i];
            }
        }
        return ans;
    }
};
//具体还是要看题解：
//当在位置 i 开始进行中心拓展时，我们可以先找到 i 关于 j 的对称点 2 * j - i。那么如果点 2 * j - i 的臂长等于 n，我们就可以知道，点 i 的臂长至少为 min(j + length - i, n)。那么我们就可以直接跳过 i 到 i + min(j + length - i, n) 这部分，从 i + min(j + length - i, n) + 1 开始拓展。
//我们只需要在中心扩展法的过程中记录右臂在最右边的回文字符串，将其中心作为 j，在计算过程中就能最大限度地避免重复计算。
//那么现在还有一个问题：如何处理长度为偶数的回文字符串呢？
//我们可以通过一个特别的操作将奇偶数的情况统一起来：我们向字符串的头尾以及每两个字符中间添加一个特殊字符 #，比如字符串 aaba 处理后会变成 #a#a#b#a#。那么原先长度为偶数的回文字符串 aa 会变成长度为奇数的回文字符串 #a#a#，而长度为奇数的回文字符串 aba 会变成长度仍然为奇数的回文字符串 #a#b#a#，我们就不需要再考虑长度为偶数的回文字符串了。
//注意这里的特殊字符不需要是没有出现过的字母，我们可以使用任何一个字符来作为这个特殊字符。这是因为，当我们只考虑长度为奇数的回文字符串时，每次我们比较的两个字符奇偶性一定是相同的，所以原来字符串中的字符不会与插入的特殊字符互相比较，不会因此产生问题
//应该能发现最⻓回⽂⼦串使⽤的左右指针和之前题⽬的左右指针有⼀些不同：之前的左右指针都是从两端向中间相向⽽⾏，⽽回⽂⼦串问题则是让左右指针从中⼼向两端扩展。
//不过这种情况也就回⽂串这类问题会遇到，所以我也把它归为左右指针了。
//到这⾥，数组相关的双指针技巧就全部讲完了，希望⼤家以后遇到类似的算法问题时能够活学活⽤，举⼀反三。



















































