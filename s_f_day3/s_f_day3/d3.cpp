#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <unordered_set>
using namespace std;
//单链表专题：
//技巧：双指针技巧秒杀七道链表题⽬
//1、合并两个有序链表
//2、合并 k 个有序链表
//3、寻找单链表的倒数第 k 个节点
//4、寻找单链表的中点
//5、判断单链表是否包含环并找出环起点
//6、判断两个单链表是否相交并找出交点
//这些解法都⽤到了双指针技巧，所以说对于单链表相关的题⽬，双指针的运⽤是⾮常⼴泛的，下⾯我们就来
//⼀个⼀个看。
// 
// 
// +虚空头指针的用法：保持操作的同一性，一致性（在题号21中，因为有可能有空指针的存在，所以加个虚空头指针可以避免讨论空指针的情况，十分方便适用）
//虚拟头节点其实比较容易理解, 相当于在头节点前, 加上一个虚拟的节点.这样, 头节点就有了前驱, 根据之前的分析, 就可以简单地将删除节点的逻辑进行统一
//leetcode：题号21：合并两个有序链表(做出来了！，还没看教程）
//
//LIstNOde结点的定义
 struct ListNode {
      int val;
   ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 //这是我自己的方法，没有考虑到空指针的情况，提交错误了好几次,一个技巧：虚空头指针用法
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode*s=list2;
        ListNode*l1=list1;
        ListNode*l2=list2;
        ListNode*temp;
        if(!list1&&!list2)
        {
            return nullptr;
        }
        else if(!list1)
        {
            return list2;
        }
        else if(!list2)
        {
            return list1;
        }
        if(l1->val<l2->val)
        {   s=list1;
            l1=l1->next;
        }
        else
        {s=list2;
        l2=l2->next;
        }
        temp=s;
        while(l2&&l1)
        {  
            if(l1->val>l2->val)
            {   

                temp->next=l2;
                l2=l2->next;
                temp=temp->next;
                
            }
            else
            {
                temp->next=l1;
                l1=l1->next;
                temp=temp->next;
            }
        }
        if(l2)
        {
            temp->next=l2;
        }
        if(l1)
        {
            temp->next=l1;
        }
        return s;
    }
};
//这是教程
ListNode* mergeTwoLists_(ListNode* l1, ListNode* l2) {
    // 虚拟头结点：注意，学会运用
    ListNode* dummy = new ListNode(-1), * p = dummy;
    ListNode* p1 = l1, * p2 = l2;

    while (p1 != NULL && p2 != NULL) {
        // ⽐较 p1 和 p2 两个指针
        // 将值较⼩的的节点接到 p 指针
        if (p1->val > p2->val) {
            p->next = p2;
            p2 = p2->next;
        }
        else {
            p->next = p1;
            p1 = p1->next;
        }
        // p 指针不断前进
        p = p->next;
    }

    if (p1 != NULL) {
        p->next = p1;
    }
    if (p2 != NULL) {
        p->next = p2;
    }

    return dummy->next;
}
//此题还有另一种方法：递归
//两个链表头部值较小的一个节点与剩下元素的 merge 操作结果合并。
//我们直接将以上递归过程建模，同时需要考虑边界情况。
//如果 l1 或者 l2 一开始就是空链表 ，那么没有任何操作需要合并，所以我们只需要返回非空链表。否则，我们要判断 l1 和 l2 哪一个链表的头节点的值更小，然后递归地决定下一个添加到结果里的节点。如果两个链表有一个为空，递归结束。
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        else if (l2 == nullptr) {
            return l1;
        }
        else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};//注意理解




//题号：23：合并k个有序链表
// 
// 
//
// （虚拟头指针+最小堆+双指针的思想）
//此题用到了优先级队列的知识，因为要知道k个链表每次的最小值，所以要将他们都放入优先队列中（最小堆），使其每次得出的都是最小的值
//
//要点：使用priority_quneue时，默认的排序《运算符为less
//template <class T, class Container = vector<T>,
//    class Compare = less<typename Container::value_type> > class priority_queue;
//less的定义是
//template<class T>
//struct less :public binary_function<T, T, bool> {
//    bool operator()(const T& x, const T& y) const { return x < y; }
//}
//less的重载函数调用运算符的参数是const T& ，其实这很正常，但是因为x是const，所以假如我们在T这个类的成员函数里实现重载 < 运算符的时候，就要把它定义成 const 成员函数，不然程序error，因为常量对象无法调用非const成员函数——因为this指针默认是指向非常量对象的常量指针 T* const this （也就是非const 成员函数的this参数类型）, 而一个底层const不能初始化一个普通的对象， const成员函数的this参数类型是 const T* const this。
//在这里，我还学到了当成员函数不改变数据成员的时候，一定要切记定义成const成员函数，虽然之前就学过，但好像一直没当回事。在定义函数参数的时候，好多时候都是写成const T& ，所以假如不是const成员函数，就没法被调用。
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};
class Solution {
public:
    struct S {
        int val;
        ListNode* n;
        S(int v, ListNode* s) :val(v), n(s) {}

        bool operator < (const S& s2)const
        {
            return val > s2.val;
        }
    };
    priority_queue<S> p;
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* head = new ListNode(0);
        ListNode* temp = head;
        if (lists.size() == 0)
        {
            return NULL;
        }
        for (auto& x : lists)
        {
            if (x)
            {
                p.push({ x->val,x });
            }
        }
        while (!p.empty())
        {
            auto x = p.top();
            p.pop();
            temp->next = x.n;
            temp = temp->next;
            if (x.n->next)
                p.push({ x.n->next->val,x.n->next });
        }
        return head->next;

    }

};
//时间复杂度：考虑优先队列中的元素不超过 k 个，那么插入和删除的时间代价为 O(\log k)，这里最多有 kn 个点，对于每个点都被插入删除各一次，故总的时间代价即渐进时间复杂度为O(kn×logk)。
//空间复杂度：这里用了优先队列，优先队列中的元素不超过 k 个，故渐进空间复杂度为O(k)。
//
//第二种方法：合并两个有序链表-》合并k个有序链表，创建一个初始变量，一直与lists[i]进行两个有序链表的合并
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, * tail = &head, * aPtr = a, * bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            }
            else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ans = nullptr;
        for (size_t i = 0; i < lists.size(); ++i) {
            ans = mergeTwoLists(ans, lists[i]);
        }
        return ans;
    }
};
//时间复杂度：假设每个链表的最长长度是 n。时间复杂度为O（k^2*n)
//    空间复杂度：没有用到与 k 和n 规模相关的辅助空间，故渐进空间复杂度为 O(1)
//
//方法3：分治合并的方法(类似于归并排序的思路：将k个链表看成k个有序的子集）
//
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, * tail = &head, * aPtr = a, * bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr; aPtr = aPtr->next;
            }
            else {
                tail->next = bPtr; bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = (aPtr ? aPtr : bPtr);
        return head.next;
    }

    ListNode* merge(vector <ListNode*>& lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return nullptr;
        int mid = (l + r) >> 1;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};
//渐进时间复杂度为 O(kn×logk)。
//时间复杂度会用到O（logk）

//链表的倒数第k个结点：如何用一次便利就可以知道此结点就是我们要找的倒k个结点。（此时不知道链表的长度，两遍遍历解决的也行，但是只用一遍遍历就能解决的话更具技巧性）
//假设正常倒数k个结点就是正数n-k+1个结点，正常情况下需要一次遍历得到链表长度n，在下次遍历才能得出结果
//但有更加具技巧性的方法：也是运用双指针
//注意是走的步数，而不是第几个结点，因为最后要走到NULL才算结束，所以要算的是走了几步，
//当第一个指针从第一个结点开始走的时候，走了k步，到了k+1个结点位置，此时第二个结点也同时从第一个结点开始出发，直到第一个结点到达NULL，故第一个结点走了n步，第二个结点走了n-k步，到达n-k+1个结点上,刚好是要的倒k个结点
//因为需要对此结点进行操作，通常都是找到其前一个结点，又因为操作的一致性，第一个结点没有前置结点，所以要构造一个虚拟空结点，满足所有结点的算法逻辑一致性
//
//题号：19：删除单链表的倒k个结点
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* l1, * l2;
        ListNode* dummy = new ListNode(0, head);//构造虚拟头结点
        dummy->next = head;
        l2 = dummy;//这样l2实际到的位置是第n-k个结点，刚好是我们要的第n-k+1个结点的前置
        l1 = head;
        for (int i = 0; i < n; i++)
        {
            l1 = l1->next;//计数看的是走几步，而不是第几个点，因为最后是要到NULL的
        }
        while (l1)
        {
            l1 = l1->next;
            l2 = l2->next;
        }
        l2->next = l2->next->next;//删除此结点（假删除，没有销毁空间）
        head = dummy->next;//不要返回head，有可能删除的是head，而返回head可能会相当于没有删除（上一条注释）
        delete dummy;
        return head;
    }
};
//还有一种方法：就是用栈，按照栈的先进后出的原则，等全部放入栈后，取出的第k个元素就是我们要的倒数第k个元素，并且目前的栈顶结点就是我们要的倒k个结点的前置结点
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        stack<ListNode*> s;
        ListNode* dummy = new ListNode(0);//注意还是虚拟结点的问题，栈顶的结点要是前一个结点
        dummy->next = head;
        ListNode* l1 = dummy;
        while (l1)
        {
            s.push(l1);
            l1 = l1->next;
        }
        for (int i = 0; i < n; i++)
        {
            s.pop();
        }
        s.top()->next = s.top()->next->next;
        return dummy->next;

    }
};
//还有最正常的方法：一遍遍历得出n，在一遍遍历得出n-k+1个结点

//快慢指针的运用
//题号：876：链表的中间结点
//1.最正常的方法：先遍历一遍知道其链表的长度，其次再次遍历找到其n/2+1个结点即为要找的中间结点
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        int cnt = 0;
        ListNode* l = head;
        for (; l; cnt++)
        {
            l = l->next;
        }
        ListNode* l2 = head;
        for (int i = 1; i < (cnt / 2 + 1); i++)
        {
            l2 = l2->next;
        }
        return l2;

    }
};//时间复杂度为O（n）
//其耗时和空间占用都是极少的，但是比较没有技巧
//2.快慢指针，虽然这题用第一种方法会更快，但是为了其适用性和方法的掌握(只用一次遍历就可以完成），要知道在这个技巧，快慢指针，快指针走两步，慢指针走一步，等到快指针到NULL时，慢指针就到了中间
//
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode* quick, * slow;
        quick = slow = head;
        while (quick && quick->next)
        {
            quick = quick->next->next;
            slow = slow->next;
        }
        return slow;
    }
};
//需要注意的是，如果链表⻓度为偶数，也就是说中点有两个的时候，我们这个解法返回的节点是靠后的那个节点。
// 
//快慢指针的用法可以推广到判断一个链表是否形成一个环，如果fast指针最后指向NULL，则表示没有环，如果最后快慢指针相遇，则表示有环
class Solution {
public:
    bool middleNode(ListNode* head) {
        ListNode* quick, * slow;
        quick = slow = head;
        while (quick && quick->next)
        {
            quick = quick->next->next;
            slow = slow->next;
            if (slow == quick)
                return true;
        }
        return false;
    }
};
//题号:141：环形链表
//用快慢指针的方法
class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* fast, * slow;
        fast = slow = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast)
                break;
        }
        if (fast == NULL || fast->next == NULL)
            return false;
        else
            return true;
  
    }
};
//第二种用哈希表的方法：就是在每一次经过一个结点的时候，看哈希表中是否有与其相同的点，如果有，则说明出现了环，空间复杂度为O（n）为结点数
class Solution {
public:
    bool hasCycle(ListNode* head) {
        unordered_set<ListNode*> seen;
        while (head != nullptr) {
            if (seen.count(head)) {
                return true;
            }
            seen.insert(head);
            head = head->next;
        }
        return false;
    }
};
//进阶版：如果有环，如何判断环的起点的位置，不是一整个链表都构成环的，而是一部分是环，要计算出环的起点
//因为当快指针和慢指针第一次相遇的时候，一定是差了k步，而这k步就是环的圈的长度。假设此时相遇点距环的起点为m，则从head出发，走k-m步一定能到环的起点，有因为此时从相遇点到环的起点的距离也是k-m，故当从起点出发的慢指针和从相遇点出发的快指针相遇时，一定就是环的起点了
//
class Solution {
public:
    bool middleNode(ListNode* head) {
        ListNode* quick, * slow;
        quick = slow = head;
        while (quick && quick->next)
        {
            quick = quick->next->next;
            slow = slow->next;
            if (slow == quick)
                break;
        }
        if (quick == NULL || quick->next == NULL)
            return NULL;
        slow = head;
        while (slow != quick)//以相同的速度再次相遇时就是他们在环的起点相遇的时候
        {
            quick = quick->next;
            slow = slow->next;
        }
        return slow;
        
    }
};
//题号：142：环形链表二
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        ListNode* fast, * slow;
        fast = slow = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (slow == fast)
                break;
        }
        if (fast == NULL || fast->next == NULL)
        {
            return NULL;
        }
        slow = head;
        while (slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
//还是哈希表的思路，只是这一次是一旦遇到了之前的值，就返回这个结点，这个结点就是环的第一个结点，虽然简单粗暴，但是其空间复杂度为O（n）
class Solution {
public:
    ListNode* detectCycle(ListNode* head) {
        unordered_set<ListNode*> visited;
        while (head != nullptr) {
            if (visited.count(head)) {
                return head;
            }
            visited.insert(head);
            head = head->next;
        }
        return nullptr;
    }
};
//
//
//题号：160：相交链表
//1.哈希表：先将其中一个链表全部放入哈希表中，然后在从另一个链表慢慢一个一个与哈希表比较，如果一旦有一个相遇，则代表有相交并且相交的第一个起点就是这个结点
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        unordered_set<ListNode*> us;
        ListNode* l = headA;
        while (l)
        {
            us.insert(l);
            l = l->next;
        }
        l = headB;
        while (l)
        {
            if (us.count(l))
                return l;
            l = l->next;
        }
        return NULL;
    }
};
//时间复杂度：O(m + n)，其中 m 和 n是分别是链表 \textit{ headA }headA 和 \textit{ headB }headB 的长度。需要遍历两个链表各一次。
//空间复杂度：O(m)，其中 m是链表 \textit{ headA }headA 的长度。需要使用哈希集合存储链表 \textit{ headA }headA 中的全部节点。
// 
//双指针的技巧：就算将两个指针同时指向两个不同的链表，但是其长度不能保证相同，两个指针不能同时到达相交点：？如何解决
// 这种方法比较麻烦，实现不理想：我们可以将两个链表连起来，这样的话如果有交点就会形成环，从而可以变成环的交点的问题。
// （思路很重要）
// 
// 自己的方法：就是如果链表相交，那么从末端到最短的链表这一段路程进行比较，就可以两个指针同步往下走，直到相等。要先遍历两个链表，找出最短的那个链表，将两个的链表长度的差作为长的链表提前走的部分。这时就可以两个指针同时走，并且保证后续链表的长度相等了
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        ListNode* a = headA;
        ListNode* b = headB;
        int na = 0, nb = 0;
        while (a)
        {
            na++;
            a = a->next;
        }
        while (b)
        {
            nb++;
            b = b->next;
        }
        int n;
        a = headA;
        b = headB;
        if (na >= nb)
        {
            n = na - nb;
            for (int i = 0; i < n; i++)
            {
                a = a->next;
            }
            while (a != b)
            {
                a = a->next;
                b = b->next;
            }
            if (!a || !b)
            {
                return NULL;
            }
            else {
                return a;
            }
        }
        else
        {
            n = nb - na;
            for (int i = 0; i < n; i++)
            {
                b = b->next;
            }
            while (a != b)
            {
                a = a->next;
                b = b->next;
            }
            if (!a || !b)
            {
                return NULL;
            }
            else {
                return a;
            }
        }

    }
};
//教程的方法
//更好的方法是：也是连接两个链表（不是实际意义的连接，而是指针a遍历完A，就转到B，指针b遍历完b就转到A）这样两个指针就可以在同时检测到相交结点了，是我上面那个方法的简化，直接两个链表不同顺序连接，相当与抵消了他们之间的差值，可以保证同步
//下面提供双指针方法的正确性证明。考虑两种情况，第一种情况是两个链表相交，第二种情况是两个链表不相交。
//
//情况一：两个链表相交
//
//链表 \textit{ headA }headA 和 \textit{ headB }headB 的长度分别是 m 和 n。假设链表 \textit{ headA }headA 的不相交部分有 a 个节点，链表 \textit{ headB }headB 的不相交部分有 b 个节点，两个链表相交的部分有 c 个节点，则有 a + c = m，b + c = n。
//
//如果 a = b，则两个指针会同时到达两个链表相交的节点，此时返回相交的节点；
//
//如果 a 不等于 b，则指针 \textit{ pA }pA 会遍历完链表 \textit{ headA }headA，指针 \textit{ pB }pB 会遍历完链表 \textit{ headB }headB，两个指针不会同时到达链表的尾节点，然后指针 \textit{ pA }pA 移到链表 \textit{ headB }headB 的头节点，指针 \textit{ pB }pB 移到链表 \textit{ headA }headA 的头节点，然后两个指针继续移动，在指针 \textit{ pA }pA 移动了 a + c + b 次、指针 \textit{ pB }pB 移动了 b + c + a 次之后，两个指针会同时到达两个链表相交的节点，该节点也是两个指针第一次同时指向的节点，此时返回相交的节点。
//
//情况二：两个链表不相交
//
//链表 \textit{ headA }headA 和 \textit{ headB }headB 的长度分别是 m和 n。考虑当 m = n 和 m 不等于 n
//
//​
//m= n 时，两个指针分别会如何移动：
//
//如果 m = n，则两个指针会同时到达两个链表的尾节点，然后同时变成空值 \text{ null }null，此时返回 \text{ null }null；
//
//如果 m 不等于 n，则由于两个链表没有公共节点，两个指针也不会同时到达两个链表的尾节点，因此两个指针都会遍历完两个链表，在指针 \textit{ pA }pA 移动了 m + n 次、指针 \textit{ pB }pB 移动了 n + m 次之后，两个指针会同时变成空值 \text{ null }null，此时返回 \text{ null }null。
class Solution {
public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        if (headA == nullptr || headB == nullptr) {
            return nullptr;
        }
        ListNode* pA = headA, * pB = headB;
        while (pA != pB) {
            pA = pA == nullptr ? headB : pA->next;
            pB = pB == nullptr ? headA : pB->next;
        }
        return pA;
    }
};