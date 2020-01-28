#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <vector>
using std::map;
using std::string;
using std::getline;
using std::find;
/* в файле текст
 * в тексте встречаются http://some.url
 * все, что начинается http:// и заканчивается пробелом -> считается урлом
 * найти все урлы, выдать пять самых встречающихся
 */
int main() {
    string token;
    string url("http://");
    std::map<string, size_t> url_counter;
    std::ifstream f("urls.txt");
    if (f.is_open()) {
        while (f.good()) {
            getline(f, token, ' ');
            if (token.find(url) == 0) {
                if (url_counter.find(token) != url_counter.end()) {
                    url_counter[token]++;
                } else {
                    url_counter.emplace(token, 1);
                }
            }
        }
    }
    std::vector<std::pair<size_t, string>> for_sort;
    for (auto & it : url_counter) {
        for_sort.emplace_back(it.second, it.first);
    }
    std::sort(for_sort.rbegin(), for_sort.rend());
    const size_t top5 = 5;
    size_t i = 0;
    auto it = for_sort.begin();
    while ((i < top5) && (it != for_sort.end())) {
        std::cout << it->second << std::endl;
        ++it;
        ++i;
    }
    return 0;
}