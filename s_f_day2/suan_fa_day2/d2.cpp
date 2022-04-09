#include <iostream>
#include <vector>
using namespace std;
//前缀和主要适⽤的场景是原始数组不会被修改的情况下，频繁查询某个区间的累加和。
//差分数组：差分数组的主要适⽤场景是频繁对原始数组的某个区间的元素进⾏增减。
//差分数组：就是构造一个数组，数组的每个数都是前一个数-去当前这个数的结果，第一位数就是他原来的数（因为没有更前面的数来相减）
//a[0] = num[0];
//for (int i = 1; i < length; i++)
//{
//	a[i] = num[i] - num[i - 1];
//}
//来构造差分数组、
//而如果进行对一个子区间的整体都相加或相减value，只要把区间（i。。。。j）中的差分数组a[i]+=value，再将a[j+1]-=value，
//因为对这一整个子区间相加减的话，他们内部的差分数组类似于a1+m-(a2+m),结果还是原来的值，所以改变的只有子区间相临的元素，前面的元素-当前子区间的首元素，a[首】会加等于value，而尾元素后的那个元素会-=value
//在进行操作后，如果要得到原数组，只要将构造差分数组的过程逆过来就行
//nums[0] = a[0];//因为差分数组的首元素就是本来的值
//for (int i = 1; i < length; i++)
//{
//	nums[i] = nums[i -1] + a[i];
//}
//还能在优化，不用新创建一个数组
//for (int i = 1; i < n; i++)
//{
//	a[i] += a[i - 1];//a是原本的差分数组，这样就等于是nums[i]=num[i-1]+a[i]，因为a[0]和nums【0】是一样的，所以一样
//}
//整体过程合并成一个类
// 差分数组⼯具类
/*class Difference {
	// 差分数组
	private int[] diff;

	//输⼊⼀个初始数组，区间操作将在这个数组上进⾏ 
	public Difference(int[] nums) {
		assert nums.length > 0;
		diff = new int[nums.length];
		// 根据初始数组构造差分数组
		diff[0] = nums[0];
		for (int i = 1; i < nums.length; i++) {
			diff[i] = nums[i] - nums[i - 1];
		}
	}
	//给闭区间 [i,j] 增加 val（可以是负数）
	public void increment(int i, int j, int val) {
		diff[i] += val;
		if (j + 1 < diff.length) {//如果j+1大于length，那么说明是从i到结尾，所以不用-=的朝操作，因为都在子区间内，相减都不影响本来的值
			diff[j + 1] -= val;
		}
	}
	//返回结果数组 
	public int[] result() {
		int[] res = new int[diff.length];
		// 根据差分数组构造结果数组
		res[0] = diff[0];
		for (int i = 1; i < diff.length; i++) {
			res[i] = res[i - 1] + diff[i];
		}
		//优化
		for(int i=1;i<didd.length;i++)
		{
		diff[i]+=diff[i-1];
		}
		return res;
	}
}*/
//leetcode题号：370，区间加法，直接运用的是差分数组的原理，但有些都是要抽象出来才可以解决的
int * inerace(int* diff, int left, int right, int value,int n)
{
	diff[left] += value;
	if (right + 1 < n)
	{
		diff[right + 1] -= value;
	}
	return diff;
}
int main() {
	int n, k;
	cin >> n;
	cin >> k;
	int* nums = new int[n];
	int* diff = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> nums[i];
	}
	diff[0] = nums[0];
	for (int i= 1; i < n; i++)
	{
		diff[i] = nums[i] - nums[i - 1];
	}
	int l, r, v;
	for (int j = 0; j < k; j++)
	{
		cin >> l >> r >> v;
		inerace(diff, l, r, v, n);
	}
	//将差分数组复原
	auto final = new int[n];
	final[0] = diff[0];
	/*for (int i = 1; i < n; i++)
	{
		final[i] = final[i - 1] + diff[i];
	}*/
	//优化的
	for (int i = 1; i < n; i++)
	{
		diff[i] += diff[i - 1];
	}
	for (int i = 0; i < n; i++)
	{
		cout << diff[i] << " ";
	}
	return 0;
}
//题号：1109航班预定统计
//此题的一开始的数组全为0，相当于差分数组，一开始全为0就是相差为0，本身就是差分数组。
class Solution {
public:
	vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
		vector<int> a;
		a.resize(n);
		for (auto x : bookings)
		{
			a[x[0] - 1] += x[2];
			if (x[1] < n)
			{
				a[x[1]] -= x[2];
			}
		}
		for (int i = 1; i < n; i++)
		{
			a[i] += a[i - 1];
		}
		return a;
	}
};
//时间复杂度：O(n + m)，其中 n 为要求的数组长度，m为预定记录的数量。我们需要对于每一条预定记录处理一次差分数组，并最后对差分数组求前缀和。
//空间复杂度：O(1)。我们只需要常数的空间保存若干变量，注意返回值不计入空间复杂度。
//有空进行了解
/*本题只涉及「区间修改 + 单点查询」，属于「区间求和」问题中的入门难度。
对于各类「区间求和」问题，该用什么方式进行求解，之前在这里提到过。
此处可以再总结一下（加粗字体为最佳方案）：
数组不变，区间查询：前缀和、树状数组、线段树；
数组单点修改，区间查询：树状数组、线段树；
数组区间修改，单点查询：差分、线段树；
数组区间修改，区间查询：线段树。
*/

//题号：1094拼车
//没想到，可以将公里数看成是数组的下标，在那一个区间内总体加上上车的人数，并且每个公里数到最后都是不能大于座位的，并且在下车结尾那个公里数里不能算有人，算已经下车了
class Solution {
public:
	bool carPooling(vector<vector<int>>& trips, int capacity) {
		vector<int> diff(1001);
		for (auto x : trips)
		{
			diff[x[1]] += x[0];
			if (x[2] < 1001) diff[x[2]] -= x[0];//注意末尾的那个下标的公里数是已经下车的人！！！

		}
		for (int i = 0; i < 1001; i++)
		{
			if (i)
				diff[i] += diff[i - 1];
			if (diff[i] > capacity)
				return false;
		}
		return true;
	}
};
//相信你已经能够联想到差分数组技巧了：trips[i] 代表着一组区间操作，旅客的上车和下车就相当于数组的区间加减；只要结果数组中的元素都小于 capacity，就说明可以不超载运输所有旅客。
//
//但问题是，差分数组的长度（车站的个数）应该是多少呢？题目没有直接给，但给出了数据取值范围：
//
//0 <= trips[i][1] < trips[i][2] <= 1000
//	车站编号从 0 开始，最多到 1000，也就是最多有 1001 个车站，那么我们的差分数组长度可以直接设置为 1001，这样索引刚好能够涵盖所有车站的编号：






