#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <list>
using namespace std;
//滑动窗口算法
//链表子串数组题，用双指针别犹豫。双指针家三兄弟，各个都是万人迷。
//快慢指针最神奇，链表操作无压力，归并排序找中点，链表成环搞判定。
//左右指针最常见，左右两端相向行。反转数组要靠他，二分搜索是弟弟
//滑动窗口老猛男，子串问题全靠他。左右指针滑窗口，一前一后齐头进。

//双指针技巧有：快慢指针，左右指针，和滑动窗口---前面已经学习了左右指针和快慢指针，接接下来学习最难的滑动窗口的问题。
//说起滑动窗⼝算法，很多读者都会头疼。这个算法技巧的思路⾮常简单，就是维护⼀个窗⼝，不断滑动，然后更新答案么。LeetCode 上有起码 10 道运⽤滑动窗⼝算法的题⽬，难度都是中等和困难。
// 该算法的⼤致逻辑如下：
/*int left = 0, right = 0;
while (right < s.size()) {
	// 增⼤窗⼝
	window.add(s[right]);
	right++;

	while (window needs shrink) {
		// 缩⼩窗⼝
		window.remove(s[left]);
		left++;
	}
}*/
//算法的时间复杂度为O（n），比起字符串暴力算法要高效得多
//其实困扰⼤家的，不是算法的思路，⽽是各种细节问题。⽐如说如何向窗⼝中添加新元素，如何缩⼩窗⼝，
//在窗⼝滑动的哪个阶段更新结果。即便你明⽩了这些细节，也容易出 bug，找 bug 还不知道怎么找，真的挺让⼈⼼烦的。
//所以今天我就写⼀套滑动窗⼝算法的代码框架，我连再哪⾥做输出 debug 都给你写好了，以后遇到相关的问
//题，你就默写出来如下框架然后改三个地⽅就⾏，还不会出 bug：
/* 滑动窗⼝算法框架 */
void slidingWindow(string s, string t) {
	unordered_map<char, int> need, window;
	for (char c : t) need[c]++;

	int left = 0, right = 0;
	int valid = 0;
	while (right < s.size()) {
		// c 是将移⼊窗⼝的字符
		char c = s[right];
		// 右移（增⼤）窗⼝
		right++;
		// 进⾏窗⼝内数据的⼀系列更新
		//...
			/*** debug 输出的位置 ***/
			printf("window: [%d, %d)\n", left, right);
		/********************/

		// 判断左侧窗⼝是否要收缩
		while (window needs shrink) {
			// d 是将移出窗⼝的字符
			char d = s[left];
			// 左移（缩⼩）窗⼝
			left++;
			// 进⾏窗⼝内数据的⼀系列更新
			//...
		}
	}
}
//进行思路讲解和实践：
//题号76：最小覆盖子串
//我们在字符串 S 中使⽤双指针中的左右指针技巧，初始化 left = right = 0，把索引左闭右开区间
//[left, right) 称为⼀个「窗⼝」。
//PS：理论上你可以设计两端都开或者两端都闭的区间，但设计为左闭右开区间是最⽅便处理的。因为
//这样初始化 left = right = 0 时区间[0, 0) 中没有元素，但只要让 right 向右移动⼀位，区间
//[0, 1) 就包含⼀个元素 0 了。如果你设置为两端都开的区间，那么让 right 向右移动⼀位后开区间
//(0, 1) 仍然没有元素；如果你设置为两端都闭的区间，那么初始区间[0, 0] 就包含了⼀个元素。
//这两种情况都会给边界处理带来不必要的麻烦。
//2、我们先不断地增加 right 指针扩⼤窗⼝[left, right)，直到窗⼝中的字符串符合要求（包含了 T 中
//的所有字符）。
//3、此时，我们停⽌增加 right，转⽽不断增加 left 指针缩⼩窗⼝[left, right)，直到窗⼝中的字符串
//不再符合要求（不包含 T 中的所有字符了）。同时，每次增加 left，我们都要更新⼀轮结果
//4、重复第 2 和第 3 步，直到 right 到达字符串 S 的尽头。
//这个思路其实也不难，第 2 步相当于在寻找⼀个「可⾏解」，然后第 3 步在优化这个「可⾏解」，最终找到
//最优解，也就是最短的覆盖⼦串。左右指针轮流前进，窗⼝⼤⼩增增减减，窗⼝不断向右滑动，这就是「滑
//动窗⼝」这个名字的来历。
//
//现在开始套模板，只需要思考以下四个问题：
//1、当移动 right 扩⼤窗⼝，即加⼊字符时，应该更新哪些数据？
//2、什么条件下，窗⼝应该暂停扩⼤，开始移动 left 缩⼩窗⼝？
//3、当移动 left 缩⼩窗⼝，即移出字符时，应该更新哪些数据？
//4、我们要的结果应该在扩⼤窗⼝时还是缩⼩窗⼝时进⾏更新？
//如果⼀个字符进⼊窗⼝，应该增加 window 计数器；如果⼀个字符将移出窗⼝的时候，应该减少 window 计数器；
//当 valid 满⾜ need 时应该收缩窗⼝；应该在收缩窗⼝的时候更新最终结果。
//
//滑动窗口的思路是从起点开始，随着right++全部收录进来，直到满足了子串条件时，才开始优化，看是否有其中的更小子串满足子串的要求，而且时从起点开始检查的，不会有遗漏。
class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> need, window;
        for (char c : t)need[c]++;
        int left = 0, right = 0;
        int vaild = 0;
        // 记录最⼩覆盖⼦串的起始索引及⻓度
        int start = 0;
        int len = 100000;
        while (right < s.size())
        {
            // c 是将移⼊窗⼝的字符
            char c = s[right];
            //右移窗口
            right++;
            // 进⾏窗⼝内数据的⼀系列更新
            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c])
                    vaild++;
            }
            //判断左侧窗口是否要收缩
            while (vaild == need.size())
            {   //更新最小覆盖子串
                if (right - left < len)
                {
                    start = left;
                    len = right - left;
                }
                //d是将移出窗口的字符
                char d = s[left];
                //左移窗口
                left++;
                //进行窗口内的一系列更新
                if (need.count(d))
                {
                    if (window[d] == need[d])
                    {
                        vaild--;

                    }
                    window[d]--;

                }
            }
        }
        return len == 100000 ? "" : s.substr(start, len);
    }
};
//len的初始值应该设置的很大，我设置了1000，最后一点不满足，直到设置成100000才满足
//自主练习：
//题号567：字符串的排列
//思路还是没正确，没有找到判断缩小窗口的点,以为排序不能有重复，就想从还没进入缩减窗口的阶段就开始判断，想提前剔除，发现错误。
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> need, window;
        for (char c : s1)
        {
            need[c]++;
        }
        int left = 0, right = 0;
        int vaild = 0;
        while (right < s2.size())
        {
            char c = s2[right];
            right++;
            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c])
                {
                    vaild++;
                }
            }
            while (right - left >= s1.size())
            {
                if (vaild == need.size())
                    return true;
                char d = s2[left];
                left++;
                if (need.count(d))
                {
                    if (window[d] == need[d])
                    {
                        vaild--;
                    }
                    window[d]--;
                }
            }
        }
        return false;
    }
};
//下一题题号438：找所有字母异位词，（有了前一题的思路，我想到的）
//这一题和上一题的思路基本上一样，就是找到那个子串长度的窗口时就进入判断，如果此时的vaild等于哈希表中的值，那么因为此时长度相等且vaild相等。所以是没有其他单词在其中的，然后将此时的开头下标保存在vector，在继续缩小窗口
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> need, window;
        vector<int> value;
        for (char c : p)
        {
            need[c]++;
        }
        int left = 0, right = 0;
        int vaild = 0;
        while (right < s.size())
        {
            char c = s[right];
            right++;
            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c])
                {
                    vaild++;
                }
            }
            while (right - left >= p.size())
            {
                if (vaild == need.size())//这里要注意不是匹配子串的size，因为有重复的单词存在的可能性，所以是哈希表中的大小
                {
                    value.push_back(left);
                }
                char d = s[left];
                left++;
                if (need.count(d))
                {
                    if (window[d] == need[d])
                    {
                        vaild--;
                    }
                    window[d]--;
                }
            }

        }
        return value;
    }
};
//lettcode题解：还有用另一种解法：就是固定好了窗口大小就是等于p.size(),只是窗口同时移动而已
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> sCount(26);
        vector<int> pCount(26);
        for (int i = 0; i < pLen; ++i) {//先用前p个字符构造好第一个窗口
            ++sCount[s[i] - 'a'];
            ++pCount[p[i] - 'a'];
        }

        if (sCount == pCount) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {//从此时构造的第一个窗口开始平移，同时一边减一边增，保持窗口大小不变
            --sCount[s[i] - 'a'];
            ++sCount[s[i + pLen] - 'a'];

            if (sCount == pCount) {//时刻检查此时的窗口内的值是否和要求的相等，如果数量相等就是异构子串
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};
//时间复杂度：时间复杂度：O(m+(n−m)×Σ)，其中 n为字符串 s 的长度，m 为字符串 p 的长度，Σ 为所有可能的字符数。我们需要 O(m)来统计字符串 p 中每种字母的数量；需要 O(m)来初始化滑动窗口；需要判断 n-m+1个滑动窗口中每种字母的数量是否与字符串 pp 中每种字母的数量相同，每次判断需要O(Σ) 。因为 s 和 p 仅包含小写字母，所以 Σ=26。
//空间复杂度：O(Σ)。用于存储字符串 p 和滑动窗口中每种字母的数量。
//还有一种前面方法的优化，那就是不用两个数组来记录他们的是否相同，而是只用一个数组，只是s和p数组对他的作用是相反的，一个是++，一个是--，这样只要看他们的差就好了，如果在那个字母的值为0，就表示在这个字母上没有差别，所以只要统计差别的字母种类数diff（差别量）即可，后续的缩减也是按照这个方法来的，一旦差别量等于0，那么就相当于此时窗口内的值于要匹配的子串相等
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        int sLen = s.size(), pLen = p.size();

        if (sLen < pLen) {
            return vector<int>();
        }

        vector<int> ans;
        vector<int> count(26);
        for (int i = 0; i < pLen; ++i) {
            ++count[s[i] - 'a'];
            --count[p[i] - 'a'];
        }

        int differ = 0;
        for (int j = 0; j < 26; ++j) {
            if (count[j] != 0) {
                ++differ;
            }
        }

        if (differ == 0) {
            ans.emplace_back(0);
        }

        for (int i = 0; i < sLen - pLen; ++i) {
            //只有在以下两种情况下才要考虑对differ做出改变，还有其他的情况，count的值有很多可能
            if (count[s[i] - 'a'] == 1) {  // 窗口中字母 s[i] 的数量与字符串 p 中的数量从不同变得相同
                --differ;
            }
            else if (count[s[i] - 'a'] == 0) {  // 窗口中字母 s[i] 的数量与字符串 p 中的数量从相同变得不同
                ++differ;
            }
            --count[s[i] - 'a'];

            if (count[s[i + pLen] - 'a'] == -1) {  // 窗口中字母 s[i+pLen] 的数量与字符串 p 中的数量从不同变得相同
                --differ;
            }
            else if (count[s[i + pLen] - 'a'] == 0) {  // 窗口中字母 s[i+pLen] 的数量与字符串 p 中的数量从相同变得不同
                ++differ;
            }
            ++count[s[i + pLen] - 'a'];

            if (differ == 0) {
                ans.emplace_back(i + 1);
            }
        }

        return ans;
    }
};
//时间复杂度：O(n + m + Σ)，其中 n 为字符串 s 的长度，m 为字符串 p 的长度，其中Σ 为所有可能的字符数。我们需要 O(m) 来统计字符串 p 中每种字母的数量；需要 O(m)来初始化滑动窗口；需要 O(Σ) 来初始化 differ；需要 O(n - m) 来滑动窗口并判断窗口内每种字母的数量是否与字符串 p 中每种字母的数量相同，每次判断需要 O(1) 。因为 s 和 p 仅包含小写字母，所以Σ = 26。
//空间复杂度：O(Σ)。用于存储滑动窗口和字符串 p 中每种字母数量的差。
//
//神中神版本：
//class Solution {
//    public List<Integer> findAnagrams(String s, String p) {
//        int[] cnt = new int[128];
//        for (char c : p.toCharArray()) cnt[c]++;
//        int lo = 0, hi = 0;
//        List<Integer> res = new ArrayList<>();
//        while (hi < s.length()) {
//            if (cnt[s.charAt(hi)] > 0) {
//                cnt[s.charAt(hi++)]--;
//                if (hi - lo == p.length()) res.add(lo);
//            }
//            else {
//                cnt[s.charAt(lo++)]++;
//            }
//        }
//        return res;
//    }
//}
//此版本是用双指针的方式，将记录在cnt中的字母当成一种消耗品，如果遇到不在其中的字母，会让left++,跳过，并且将此时的字母加入到cnt中，然后在让right读到这个新添加到cnt中的字母，刚好删去了。不会重复。如果是遇到了指定的字母，会让right删去他并且往前移。唯一满足的子串条件就是right-left等于子串长度。如果找到了一组，接下来遇到的都是没有出现过的，此时要右移left，重新添加进来那些被right遍历过的在子串中的字母，这样就能再次进行寻找了
//
//下一题3：无重复的字符串
//自己想出来的，虽然有一点问题，在统计子串长度上，更新的地方错误，导致了不对，不应该在缩减窗口内更新，本来就有重复的字符串，又因为如果到最后都没有进入过缩减窗口，那么长度将永远无法更新
//还有一个问题就是在对unordered_map的概念上处理错误，因为一旦出现这个数字，例如need【c】如果不存在会创建一个，因此不能只是依靠need。size()函数来看是否删除，因为对值的改变不会影响到关键字的存在，要通过看值的方法看是否删去
//既然是通过看关键字所对应的值的方法，那么就不需要用flag来表示是否有重复出现的字符了
//教程就是用nbeed【c】的值作为判断依据，其他和我的差不多
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> need;
        if (s.size() < 1)
        {
            return 0;
        }
        int left = 0;
        int right = 0;
        int len = 0;
        int flag = 0;
        while (right < s.size())
        {
            char c = s[right];
            right++;
            if (!need[c])
            {
                need[c]++;
            }
            else
            {
                flag = 1;
                need[c]++;
            }
            while (flag)
            {
                char d = s[left];
                left++;
                if (d == c)
                {
                    flag = 0;
                }
                need[d]--;
            }
            if (len < right - left)
            {
                len = right - left;
            }

        }
        return len;
    }
};
//教程的：
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> window;
    int left = 0, right = 0;
    int res = 0; // 记录结果
    while (right < s.size()) {
        char c = s[right];
        right++;
        // 进⾏窗⼝内数据的⼀系列更新
        window[c]++;
        // 判断左侧窗⼝是否要收缩
        while (window[c] > 1) {
            char d = s[left];
            left++;
            // 进⾏窗⼝内数据的⼀系列更新
            window[d]--;
        }
        // 在这⾥更新答案
        res = max(res, right - left);
    }
    return res;
}
//唯⼀需要注意的是，在哪⾥更新结果 res 呢？我们要的是最⻓⽆重复⼦串，哪⼀个阶段可以保证窗⼝中的字符串是没有重复的呢？
//这⾥和之前不⼀样，要在收缩窗⼝完成后更新 res，因为窗⼝收缩的 while 条件是存在重复元素，换句话说
//收缩完成后⼀定保证窗⼝中没有重复嘛。
//要注意更新res的时机，看那个时候才是我们要的结果就在那时候更新即可，要会变通。
