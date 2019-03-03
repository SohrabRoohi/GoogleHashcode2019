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
    int size;
    string index;
    unordered_set<string> tags;

    Photo(int s, int in) {
        size = s;
        index = to_string(in);
        for (int i = 0; i < s; i++) {
            string ss;
            cin >> ss;
            tags.insert(ss);
        }
    }

    Photo(unordered_set<string> t, string in) {
        size = t.size();
        index = in;
        tags = t;
    }
};

vector<Photo> h;
vector<Photo> v;

unordered_set<string> un(Photo &a, Photo &b) {
    unordered_set<string> u;
    for(string s : a.tags) {
        u.insert(s);
    }

    for(string s : b.tags) {
        u.insert(s);
    }
    return u;
}

int64 intersectionSize(Photo &a, Photo &b) {
    int64 size = 0;
    if(a.tags.size() <= b.tags.size()) {
        for(string s : a.tags) {
            if(b.tags.count(s)) {
                size++;
            }
        }
    }
    else {
        for(string s : b.tags) {
            if(a.tags.count(s)) {
                size++;
            }
        }
    }
    return size;
}

Photo combine(Photo &a, Photo &b) {
    unordered_set<string> u = un(a,b);
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
    int64 u = intersectionSize(a, b);
    return min(a.tags.size() - u, min(u, b.tags.size() - u));
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

    for(char c = 'A'; c <= 'E'; c++) {
        string input = "C:\\Users\\Sohrab\\CLionProjects\\GoogleHashCode2019\\";
        input += c;
        input += "input.txt";
        ifstream in(input);
        cin.rdbuf(in.rdbuf());
        string output = "C:\\Users\\Sohrab\\CLionProjects\\GoogleHashcode2019\\";
        output += c;
        output += ".txt";
        ofstream out(output);
        cout.rdbuf(out.rdbuf());
        int64 N;
        cin >> N;
        for (int i = 0; i < N; i++) {
            int s;
            char o;
            vector<string> t;
            cin >> o >> s;
            if (o == 'H')
                h.push_back(Photo(s, i));
            else
                v.push_back(Photo(s, i));
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
        set<pair<int,int>> left;
        for(int i = 1; i < h.size(); i++) {
            left.insert(make_pair(-h[i].size, i));
        }
        while (found != h.size()) {
            int64 maxScore = -1;
            int64 maxIndex = -1;
            auto ss = left.begin();
            auto answer = ss;
            for (int i = 0; i < min(5000,(int)left.size()); i++) {
                int index = ss->second;
                if (curIndex == index) {
                    continue;
                }
                if (!visited[index]) {
                    int64 sc = score(cur, h[index]);
                    if (sc > maxScore) {
                        answer = ss;
                        maxScore = sc;
                        maxIndex = index;
                    }
                }
                ss++;
            }
            left.erase(*answer);
            final_score += maxScore;
            cur = h[maxIndex];
            curIndex = maxIndex;
            ans.push_back(cur.index);
            visited[maxIndex] = true;
            found++;
            cerr << c << " " << found << endl;
        }

        cout << ans.size() << endl;
        for (string ss : ans) {
            cout << ss << endl;
        }
        h.clear();
        v.clear();
    }

    return 0;
}