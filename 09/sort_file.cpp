#include <iostream>
#include <fstream>
#include <thread>
#include <algorithm>
#include <sstream>
#include <vector>
#include <queue>
#include <iterator>

#define CHUNK_SIZE 1024 * 1024
//#define CHUNK_SIZE 20 * 8
using namespace std;

template <class MinHeap, class Out>
void mergek(MinHeap& heap, Out& out)
{
    while(!heap.empty()) {
        auto range = heap.top(); // pop minimum in O(1)
        heap.pop();
        auto n = *range.first++; // output the minimum, move input
        out.write(reinterpret_cast<char *>(&n), sizeof(uint64_t));
        if (range.first != range.second) // push unless empty range
            heap.emplace(range); // find new minimum in O(log k)
    }
}

int main() {
    auto *buf = new uint64_t[CHUNK_SIZE];
    /*ofstream out1("in.txt", ios::binary | ios::out);
    for (int i = 0; i < 100; ++i) {
        auto *n = new uint64_t(std::rand() % 100);
        out1.write(reinterpret_cast<char *>(n), sizeof(uint64_t));
    }
    out1.close();*/
    ifstream in("in.txt", ios::binary | ios::in);
    while (in) {
        uint64_t n;
        in.read(reinterpret_cast<char *>(&n), sizeof(uint64_t));
        cout << n << ' ';
    }
    cout << endl;
    in.close();
    in.open("in.txt", ios::binary | ios::in);
    size_t num_files = 0;
    vector<string> name;
    while (in) {
        in.read(reinterpret_cast<char *>(buf), CHUNK_SIZE);
        auto size_read = in.gcount();
        if (size_read > 0) {
            for (int i = 0; i < 2; ++i) {
                stringstream s;
                s << num_files;
                name.emplace_back();
                s >> name[num_files++];
            }
            std::thread t1([buf, size_read]() { sort(buf, buf + (size_read / (2 * sizeof(uint64_t)))); });
            std::thread t2([buf, size_read]() {
                sort(buf + size_read / (2 * sizeof(uint64_t)),
                     buf + size_read / sizeof(uint64_t));
            });
            t1.join();
            t2.join();
            for (size_t i = 0; i < size_read / sizeof(uint64_t); ++i) {
                cout << buf[i] << ' ';
            }
            cout << endl;
            ofstream out;
            out.open(name[num_files - 2]);
            for (size_t i = 0; i < size_read / (2 * sizeof(uint64_t)); ++i) {
                out << buf[i] << ' ';
            }
            out.close();
            out.open(name[num_files - 1]);
            for (size_t i = size_read / (2 * sizeof(uint64_t)); i < size_read / sizeof(uint64_t); ++i)  {
                out << buf[i] << ' ';
            }
            out.close();
        }
    }
    in.close();
    delete[] buf;
    ofstream out("out.txt", ios::binary);
    vector <ifstream> files (num_files);
    // merge sorted files
    typedef istream_iterator<uint64_t> It;
    // the heap contains pairs of iterators over files: (current_position, eof)
    typedef pair<It, It> Range;
    auto less_first = [](const Range& lhs, const Range& rhs) {
        return *lhs.first > *rhs.first;
    };
    priority_queue<Range, vector<Range>, decltype(less_first)> heap(less_first);
    auto cur_num = num_files;
    while (cur_num--) {
        files[cur_num].open(name[cur_num]);
        heap.emplace(It(files[cur_num]), It());
    }
    mergek(heap, out);
    for(size_t i = 0; i < num_files; ++i) {
        files[i].close();
        remove(name[i].c_str());
    }
    out.close();
    in.open("out.txt");
    while(in) {
        uint64_t n;
        in.read(reinterpret_cast<char *>(&n), sizeof(uint64_t));
        cout << n << ' ';
    }
    in.close();
    cout << endl << "done" << endl;
    return 0;
}