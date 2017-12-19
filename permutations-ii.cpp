/* LC 47
 * Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/

#include<iostream>
#include<vector>
using namespace std;

//Same as permutations approach 2 using 'next' permutation
bool helper(vector<int> &A, vector<vector<int>> &res, int n) {
        
        int k = -1;
        for(int i = n-2; i >=0; i--) {
            if(A[i] < A[i+1]) {
                k = i;
                break;
            }
        }
        if(k == -1) {
            //sort(A.begin(),A.end());
            return false;
        }
        int l = -1;
        for(int i = n-1; i >= 0; i--) {
            if(A[i] > A[k]) {
                l = i;
                break;
            }
        }
        swap(A[k],A[l]);
        reverse(A.begin()+k+1,A.end());
        return true;
    }
    
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        if(n==0) return res;
        if(n==1){res.push_back(nums); return res;}
        sort(nums.begin(),nums.end());
        res.push_back(nums);
        while(helper(nums,res,n))
            res.push_back(nums);
        return res;
    }

//approach 2
void helper(vector<int> &nums, vector<vector<int>> &res, vector<int> &ans, vector<bool> &used){
        if(ans.size() == nums.size()) {
            res.push_back(ans);
        } else {
            for(int i = 0; i < nums.size(); i++) {
                if(used[i] || i>0 && nums[i] == nums[i-1] && !used[i-1]) continue;
                ans.push_back(nums[i]);
                used[i] = true;
                helper(nums,res,ans,used);
                ans.pop_back();
                used[i] = false;
            }
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> ans;
        int n = nums.size();
        if(!n) return res;
        if(n == 1) {
            res.push_back(nums);
            return res;
        }
        vector<bool> used(n,false);
        sort(nums.begin(),nums.end());
        helper(nums,res,ans,used);
        return res;
    }
    
    /* Tested.
     * Note: Parallization/multithreading is easy for the 'next permutation' approach. The concept being: If I have 200k permutations to generate and have 2 cores, I find out 100kth permutation by kth permutation algorithm and can parallely process from there since each permutation is only dependent on the previous one.
     * Time complexity: O(n^n) where n is the number of elements.
     * Space complexity: O(1)
     */
