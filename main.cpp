/*
Sohrab Roohi
*/

#include <bits/stdc++.h>

using namespace std;

const double pi=acos(-1.0);
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<PII> VII;
typedef vector<VI> VVI;
typedef map<int,int> MPII;
typedef set<int> SETI;
typedef multiset<int> MSETI;
typedef long int int32;
typedef unsigned long int uint32;
typedef long long int int64;
typedef unsigned long long int  uint64;


class Photo {
public:
    char orientation;
    int size;
    string index;
    set<string> tags;

    Photo(char o, int s, int in) {
        orientation = o;
        size = s;
        index = to_string(in);
        for (int i = 0; i < s; i++) {
            string ss;
            cin >> ss;
            tags.insert(ss);
        }
    }

    Photo(char o, set<string> t, string in) {
        orientation = o;
        size = t.size();
        index = in;
        tags = t;
    }
};

vector<Photo> p;
vector<Photo> h;
vector<Photo> v;

Photo combine(Photo a, Photo b) {
    set<string> u;
    set_union(a.tags.begin(), a.tags.end(), b.tags.begin(), b.tags.end(), inserter(u,u.begin()));
    string combined = a.index;
    combined += " ";
    combined += b.index;
    return Photo('H', u, combined);
}

bool comp(const Photo &a, const Photo &b) {
    return a.size > b.size;
}

int64 score(Photo a, Photo b) {
    vector<string> u, adiff, bdiff;
    set_intersection(a.tags.begin(), a.tags.end(), b.tags.begin(), b.tags.end(), inserter(u,u.begin()));
    set_difference(a.tags.begin(), a.tags.end(), u.begin(), u.end(), inserter(adiff,adiff.begin()));
    set_difference(b.tags.begin(), b.tags.end(), u.begin(), u.end(), inserter(bdiff,bdiff.begin()));
    return min(adiff.size(), min(u.size(), bdiff.size()));
}

int combiner() {
    sort(v.begin(), v.end(), comp);
    for(int i = 1; i < v.size(); i += 2) {
        h.push_back(combine(v[i],v[i-1]));
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int64 N;
    cin >> N;
    for(int i = 0; i < N; i++) {
        char o;
        int s;
        vector<string> t;
        cin >> o >> s;
        p.push_back(Photo(o,s,i));
    }
    for(Photo i : p) {
        if(i.orientation == 'H') {
            h.push_back(i);
        }
        else {
            v.push_back(i);
        }
    }

    combiner();


    Photo cur = h[0];
    int64 curIndex = 0;
    vector<string> ans;
    ans.push_back(cur.index);
    vector<bool> visited(h.size(), false);
    visited[0] = true;
    int found = 1;
    int64 final_score = 0;
    while(found != h.size()) {
        int64 maxScore = -1;
        int64 maxIndex = -1;
        for(int i = 0; i < h.size(); i++) {
            if(i == curIndex) {
                continue;
            }
            if (!visited[i]) {
                int64 compScore = score(cur, h[i]);
                if(compScore > maxScore) {
                    maxScore = compScore;
                    maxIndex = i;
                }
            }
        }
        final_score += maxScore;
        cur = h[maxIndex];
        curIndex = maxIndex;
        ans.push_back(cur.index);
        visited[maxIndex] = true;
        found++;
    }
    // comment later
    //cout<< final_score << endl;

    cout << ans.size() << endl;
    for(string ss : ans) {
        cout << ss << endl;
    }


    return 0;
}