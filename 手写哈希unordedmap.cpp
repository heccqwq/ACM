#include<bits/stdc++.h>
#define int long long
using namespace std;
struct SafeHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x ^ (x >> 31);
    }

    static uint64_t seed() {
        static const uint64_t s =
            std::chrono::steady_clock::now().time_since_epoch().count();
        return s;
    }

    // 整数类型：用 is_integral<T>::value
    template <class T>
    typename std::enable_if<std::is_integral<T>::value, size_t>::type
    operator()(T x) const {
        return splitmix64(static_cast<uint64_t>(x) + seed());
    }

    // string
    size_t operator()(const std::string& s) const {
        return splitmix64(std::hash<std::string>{}(s) + seed());
    }

    // pair<int,int>
    size_t operator()(const std::pair<int,int>& p) const {
        uint64_t h = splitmix64(static_cast<uint64_t>(p.first) + seed());
        h ^= splitmix64(static_cast<uint64_t>(p.second) + 0x9e3779b9ULL
                        + (h << 6) + (h >> 2));
        return h;
    }
};
unordered_map<int,int,SafeHash> mp;
signed main(){
	ios::sync_with_stdio(0);
	return 0; 
}
