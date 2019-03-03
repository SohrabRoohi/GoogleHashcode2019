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

map<string,int> tag_amount;

class Photo {
public:
    int size;
    string index;
    vector<string> tags;

    Photo(int s, int in) {
        size = s;
        index = to_string(in);
        for (int i = 0; i < s; i++) {
            string ss;
            cin >> ss;
            tags.push_back(ss);
            tag_amount[ss]++;
        }
    }

    Photo(vector<string> t, string in) {
        size = t.size();
        index = in;
        tags = t;
    }
};

vector<Photo> h;
vector<Photo> v;

Photo combine(Photo &a, Photo &b) {
    vector<string> u;
    set_union(a.tags.begin(), a.tags.end(), b.tags.begin(), b.tags.end(), inserter(u,u.begin()));
    string combined;
    combined.append(a.index);
    combined.append(" ");
    combined.append(b.index);
    return Photo(u, combined);
}

bool comp(const Photo &a, const Photo &b) {
    return a.size > b.size;
}

int64 score(Photo &a, Photo &b) {
    vector<string> u, adiff, bdiff;
    set_intersection(a.tags.begin(), a.tags.end(), b.tags.begin(), b.tags.end(), inserter(u,u.begin()));
    set_difference(a.tags.begin(), a.tags.end(), u.begin(), u.end(), inserter(adiff,adiff.begin()));
    set_difference(b.tags.begin(), b.tags.end(), u.begin(), u.end(), inserter(bdiff,bdiff.begin()));
    return min(adiff.size(), min(u.size(), bdiff.size()));
}

int combiner() {
    // old
    sort(v.begin(), v.end(), comp);
    for(int i = 1; i < v.size(); i += 2) {
        h.push_back(combine(v[i],v[i-1]));
    }
    /*
    vector<bool> combiner_visited(v.size(), false);
    for(int i = 1; i < v.size(); i ++) {
        if (combiner_visited[i]) continue;
        int best = i + 1;
        for (int j = i + 2; j < v.size(); j++) {
            if (combiner_visited[i]) continue;

            h.push_back(combine(v[i],v[i-1]));
        }
    }*/
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ifstream in("C:\\Users\\Sohrab\\CLionProjects\\GoogleHashCode2019\\Ainput.txt");
    cin.rdbuf(in.rdbuf());
    ofstream out("C:\\Users\\Sohrab\\CLionProjects\\GoogleHashcode2019\\E.txt");
    cout.rdbuf(out.rdbuf());
    int64 N;
    cin >> N;
    for(int i = 0; i < N; i++) {
        int s;
        char o;
        vector<string> t;
        cin >> o >> s;
        if (o == 'H')
            h.push_back(Photo(s,i));
        else
            v.push_back(Photo(s,i));
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
    set<int> left;
    for(int i = 0; i < h.size(); i++) {
        left.insert(i);
    }
    left.erase(0);
    while(found != h.size()) {
        int64 maxScore = -1;
        int64 maxIndex = -1;
        bool f = false;
        for(int i = 0; i < min(100,(int)h.size()); i++) {
            int toTest = rand() % (h.size() - 1);
            if(curIndex == toTest) {
                continue;
            }
            if (!visited[toTest]) {
                f = true;
                int64 compScore = score(cur, h[toTest]);
                if(compScore > maxScore) {
                    maxScore = compScore;
                    maxIndex = toTest;
                }
            }
        }
        if(!f) {
            maxIndex = *(left.begin());
        }
        left.erase(maxIndex);
        final_score += maxScore;
        cur = h[maxIndex];
        curIndex = maxIndex;
        ans.push_back(cur.index);
        visited[maxIndex] = true;
        found++;
    }
    // comment later
    //cout<<"score is: "<<final_score << endl;

    cout << ans.size() << endl;
    for(string ss : ans) {
        cout << ss << endl;
    }


    return 0;
}