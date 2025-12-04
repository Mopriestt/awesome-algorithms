#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<string> split(const string &s, const string &delimiter) {
    size_t pos_start = 0, pos_end;
    const size_t delim_len = delimiter.length();
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        string token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(std::move(token));
    }

    res.push_back(s.substr(pos_start));
    return res;
}

int main() {
    string s = "abc.def.egh..   .kkk";
    auto segs = split(s, ".");
    cout<<segs.size()<<endl;
    for (auto _ : segs) cout<<_<<endl;
    return 0;
}