#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    static void showArrays(vector<int> nums) {
        for (int &n: nums) {
            cout << n << " ";
        }
        cout << endl;
    }

    //! 直接插入排序
    void insertSort(vector<int> nums) {
        for (int i = 1; i < nums.size(); i++) {
            int temp = nums[i];
            if (temp < nums[i - 1]) {
                int j = i;
                while (temp < nums[j - 1] && j >= 1) {
                    nums[j] = nums[j - 1];
                    j--;
                }
                nums[j] = temp;
            }
            showArrays(nums);
        }
    }

    //折半插入排序
    void insertSort2(vector<int> nums) {
        for (int i = 1; i < nums.size(); i++) {
            int temp = nums[i];
            int low=0,high=i-1;
            while(low<=high){
                int mid=(low+high)/2;
                if(nums[mid]>temp){
                    high=mid-1;
                }else{
                    low=mid+1;
                }
            }
            int j=i;
            for(;j>low;j--){
                nums[j]=nums[j-1];
            }
            nums[j]=temp;
            showArrays(nums);
        }
    }

    //! 希尔排序
    void shellSort(vector<int> nums) {
        int n = nums.size();
        for (int gap = n / 2; gap >= 1; gap = gap / 2) {
            for (int i = gap; i < n; i++) {
                int temp = nums[i];
                int j = i;
                for (; j >= gap && nums[j - gap] > temp; j = j - gap) {
                    nums[j] = nums[j - gap];
                }
                nums[j] = temp;
            }
            showArrays(nums);
        }
    }


    void bubbleSort(vector<int> nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            bool flag = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (nums[j] > nums[j + 1]) {
                    swap(nums[j], nums[j + 1]);
                    flag = true;
                }
            }
            if (!flag) {
                break;
            }
            showArrays(nums);
        }
    }

    void quickSort(vector<int> &nums, int left, int right) {
        // 当left==right即对一个元素没必要进行排序，无需处理
        if (left < right) {
            int pivot = partition(nums, left, right);
            quickSort(nums, left, pivot - 1);
            quickSort(nums, pivot + 1, right);
        }
        showArrays(nums);
    }

    int partition(vector<int> &nums, int left, int right) {
        int pivot = nums[left];
        // 注意此处循环条件为left<right，而不是left<=right
        while (left < right) {
            while (left < right && nums[right] >= pivot) {
                right--;
            }
            nums[left] = nums[right];
            while (left < right && nums[left] <= pivot) {
                left++;
            }
            nums[right] = nums[left];
        }
        nums[left] = pivot;
        return left;
    }


    void quickSort2(vector<int> &nums, int low, int high) {
        if (low >= high) {
            return;
        }
        int left = low;
        int right = high;
        int pivot = nums[low];

        while (left < right) {
            while (left < right && nums[right] >= pivot) {
                right--;
            }
            nums[left] = nums[right];
            while (left < right && nums[left] <= pivot) {
                left++;
            }
            nums[right] = nums[left];
        }
        nums[left] = pivot;

        quickSort2(nums, low, left - 1);
        quickSort2(nums, left + 1, high);

        showArrays(nums);
    }

    void selectionSort(vector<int> nums) {
        int minIndex = 0;
        for (int i = 0; i < nums.size(); i++) {
            minIndex = i;
            for (int j = i + 1; j < nums.size(); j++) {
                if (nums[j] < nums[minIndex]) {
                    minIndex = j;
                }
            }
            swap(nums[i], nums[minIndex]);
        }
        showArrays(nums);
    }

    void heapSort(vector<int> nums) {
        int n = nums.size();
        buildHeap(nums);
        for (int i = n - 1; i >= 0; i--) {
            swap(nums[0], nums[i]);
            heapify(nums, i-1, 0);
        }
        showArrays(nums);
    }

    // 从第index个结点开始，不断往下重复调整堆，使其成为大根堆
    void heapify(vector<int> &nums, int n, int currIndex) {
        if (currIndex > n) {
            return;
        }
        // 左孩子
        int leftChildIndex = (2 * currIndex) + 1;
        // 右孩子
        int rightChildIndex = (2 * currIndex) + 2;
        int maxIndex = currIndex;

        if (leftChildIndex <= n && nums[leftChildIndex] > nums[maxIndex]) {
            maxIndex = leftChildIndex;
        }
        if (rightChildIndex <= n && nums[rightChildIndex] > nums[maxIndex]) {
            maxIndex = rightChildIndex;
        }

        if (maxIndex != currIndex) {
            swap(nums[maxIndex], nums[currIndex]);
            heapify(nums, n, maxIndex);
        }
    }

    void buildHeap(vector<int> &nums) {
        int lastNodeIndex = nums.size() - 1;
        int lastParentIndex = (lastNodeIndex - 1) / 2;

        for (int i = lastParentIndex; i >= 0; i--) {
            heapify(nums, nums.size()-1, i);
        }
    }

    void mergeSort(vector<int> &nums, int low, int high) {
        // 当low==high时，即数组只有一个元素，为有序的，开始归并的“并”的部分
        if (low < high) {
            int mid = low + (high - low) / 2;
            mergeSort(nums, low, mid);
            mergeSort(nums, mid + 1, high);
            merge(nums, low, mid, high);
        }
        showArrays(nums);
    }

    void merge(vector<int> &nums, int low, int mid, int high) {
        vector<int> copyNums(nums);     // 辅助数组，因此空间复杂度 O(N)

        // 数组[low:mid]和[mid+1,high]之间的元素都是有序的
        int i = low, j = mid + 1;
        //! 注意此处结果数组的索引不能初始化为0
        int resIndex = i;
        while (i <= mid && j <= high) {
            if (copyNums[i] <= copyNums[j]) {
                nums[resIndex++] = copyNums[i++];
            } else {
                nums[resIndex++] = copyNums[j++];
            }
        }
        // 一边数组已经遍历插入完成，另外一边数组无需比较之间附到顺序数组后方即可
        while (i <= mid) nums[resIndex++] = copyNums[i++];
        while (j <= high) nums[resIndex++] = copyNums[j++];
    }

    void countSort(vector<int> nums) {
        int maxNum = *(max_element(nums.begin(), nums.end()));
        vector<int> countNums(maxNum + 1, 0);
        for (int &n: nums) {
            countNums[n]++;
        }

//        // 从前往后累加元素出现的次数,该次数即为元素最终应该出现的位置
//        for (int i = 1; i < countNums.size(); i++) {
//            countNums[i] += countNums[i - 1];
//        }
//        vector<int> temp(nums); //辅助数组，空间复杂度 O(N)
//
//        for (int i = temp.size() - 1; i >= 0; i--) {
//            // temp[n-1]=17     countNums[17]=4     nums[4-1]=17(注意此处要减1)
//            nums[countNums[temp[i]] - 1] = temp[i];
//            // 使多次出现的元素的出现次数减1
//            countNums[temp[i]]--;
//        }
        for (int i = 0, j = 0; i < countNums.size(); i++) {
            while (countNums[i] > 0) {
                nums[j++] = i;
                countNums[i]--;
            }
        }

        showArrays(nums);
    }

    void bucketSort(vector<int> nums) {
        int n = nums.size();
        // 使用下面两条语句分别获取vector数组中的最大值和最小值
        int maxNum = *(max_element(nums.begin(), nums.end()));
        int minNum = *(min_element(nums.begin(), nums.end()));

        // 计算桶的数量，加1是为了后续方便存放数据
        int bucketNum = (maxNum - minNum) / n + 1;
        // 即要使用的桶，上一句获得了桶的数量，但每个桶里具体存放多少数据还不清楚，后续使用push_back动态扩容
        vector<vector<int>> bucket(bucketNum);

        for (int i = 0; i < n; i++) {
            // 算出当前的元素应该放在那个桶，index为桶的索引
            int index = (nums[i] - minNum) / n;
            bucket[index].push_back(nums[i]);
        }

        // 打印数组，用于Debug,可注释掉
        for (int i = 0; i < bucket.size(); i++) {
            if(bucket[i].empty()){
                continue;
            }
            for (int j = 0; j < bucket[i].size(); j++) {
                cout << bucket[i][j] << " ";
            }
            cout << endl;
        }

        int resIndex = 0;	// 结果数组的索引
        for (int i = 0; i < bucketNum; i++) {
            // 使用快速排序对每个桶内的数据进行排序，此函数需要单独实现，当然也可以之间调用sort库函数
            quickSort(bucket[i], 0, bucket[i].size() - 1);
            // 桶内元素已经有序，直接取出来放到结果数组就行
            for (int j = 0; j < bucket[i].size(); j++) {
                nums[resIndex++] = bucket[i][j];
            }
        }
        showArrays(nums);
    }


    void radixSort(vector<int> nums) {
        int n = nums.size();

        // 求所有数据的最大位数
        int maxNum = *(max_element(nums.begin(), nums.end()));
        int numBit = 0;
        while (maxNum > 0) {
            maxNum /= 10;
            ++numBit;
        }
        // cout << "最大元素的位数：" << numBit << endl;

        // radix作为除数用于在每次循环中得到位数
        int radix = 1;
        // 第一次循环计算个位，以此十位、百位等
        for (int k = 1; k <= numBit; k++) {
            vector<vector<int>> bucket(10);
            for (int j = 0; j < n; j++) {
                // 得到该数的当前判断的位数
                int index = (nums[j] / radix) % 10;
                bucket[index].push_back(nums[j]);
            }

            //debug
            for (int i = 0; i < bucket.size(); i++) {
                if (bucket[i].empty()) {
                    continue;
                }
                for (int j = 0; j < bucket[i].size(); j++) {
                    cout << bucket[i][j] << " ";
                }
                cout << endl;
            }

            // 先分散放到各个桶里，然后再收集起来
            int resIndex=0;
            for (int i = 0; i < bucket.size(); i++) {
                if (bucket[i].empty()) {
                    continue;
                }
                for (int j = 0; j < bucket[i].size(); j++) {
                    nums[resIndex++] = bucket[i][j];
                }
            }
            cout << "第" << k << "轮排序结果为：";
            showArrays(nums);
            // 乘以10用于计算下次位数
            radix *= 10;
        }
        cout << "最终排序结果为：";
        showArrays(nums);
    }
};


int main() {
    Solution s;
    vector<int> nums = {22, 5, 43, 99, 2, 5, 17};
    vector<int> nums2 = nums;
    vector<int> nums3 = nums;
//    cout << "InsertSort:\n";
//    s.insertSort(nums);
//
//    cout << "ShellSort:\n";
//    s.shellSort(nums);

//    cout << "BubbleSort:\n";
//    s.bubbleSort(nums);

//    cout << "QuickSort:\n";
//    s.quickSort(nums, 0, nums.size() - 1);
//    s.quickSort2(nums2, 0, nums.size() - 1);

//    cout << "selectionSort:\n";
//    s.selectionSort(nums);

    cout << "HeapSort:\n";
    s.heapSort(nums);

//    Solution::showArrays(nums);

    cout << "MergeSort:\n";
    s.mergeSort(nums3, 0, nums.size() - 1);

//    cout << "ShowArray:\n";
//    Solution::showArrays(nums);

//    cout << "countSort:\n";
//    s.countSort(nums);

//    cout << "BucketSort:\n";
//    s.bucketSort(nums);

//    vector<int> numsRadixSort = {112, 34, 678, 1999, 234, 6, 89, 5678};
//    cout << "radixSort:\n";
//    s.radixSort(numsRadixSort);

    return 0;
}
