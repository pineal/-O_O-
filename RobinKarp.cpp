class Solution {
private:
    inline char hash(const string &s)
    {
        char all =0;
        for(auto i=0;i<s.size();++i)    all ^=s[i];
        return all;
    }
    
public:
    int strStr(string haystack, string needle) {
        int i, hSize = haystack.size(), nSize = needle.size();
        char target;
        if(hSize<nSize) return -1;
        if(!nSize) return 0;
        target = hash(needle);
        for(i=0; i<=hSize-nSize;++i)
        {
            if(hash(haystack.substr(i,nSize)) == target && haystack.substr(i,nSize)== needle) break;
        }
        return i<=hSize-nSize?i:-1;
    }
};
//https://leetcode.com/problems/implement-strstr/discuss/13106/My-C++-brute-force-Robin-Karp-KMP-codes