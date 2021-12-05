#include<iostream>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <future>
#include<algorithm>
#include <sstream>
#include <execution>
#include<vector>
#include <future>
#include<queue>
using namespace std;

//1
class pcout : public std::ostringstream
{
public:
    ~pcout()
    {
        lock_guard<mutex> guard(mutex);
        cout << this->str() << endl;
    }
private:
    static std::mutex _mutexPrint;
};
std::mutex pcout::_mutexPrint{};
//2
int primeNumber(int n)
{
    vector<int> primeNumber;
    int y = 2;
    while(primeNumber.size()<n) {
                 
                for (size_t i = 2; i <= y; i++)
                {                    
                    if (y % i == 0 && i < y) break;
                    if (i == y || y % i == 0)
                    {
                        primeNumber.push_back(i);
                        cout << primeNumber.back() << "" << endl;
                    }
                }
        y++;
    }
    thread::id thread_id = this_thread::get_id();
    cout << "primeNumber thread id: " << thread_id << endl;
    return primeNumber.back();
}
//3

queue<string> items;
mutex m;
condition_variable semophore;
void owner(){
    for (size_t i = 0u; i < 5; i++)
    {        
        lock_guard<mutex> lock(m);
        items.push("Vase");
        semophore.notify_one();
        cout << "added" << endl;
        //---------------------
        thread::id thread_id = this_thread::get_id();
        cout << "primeNumber thread id: " << thread_id << endl;
    }
}

void thief() {
    for (size_t i = 0u; i < 5; i++)
    {
        unique_lock<mutex> lock(m);
        semophore.wait(lock, [] {return !items.empty(); });
        cout << items.front() << endl;
        items.pop();
        //---------------------
        thread::id thread_id = this_thread::get_id();
        cout << "primeNumber thread id: " << thread_id << endl;
    }
}

int main()
{   
    //1
    {
        pcout prt;
        string val = "val";
        prt << "str";
        pcout{} << "my_val=" << val << std::endl;
        pcout{} << "my_val=" << "123" << std::endl;
        
    }

    //2
    {
        
        auto future = std::async(primeNumber, 100);
        int primeNumber = future.get();
        cout << "your prime number is=" << primeNumber << endl;
        thread::id thread_id = this_thread::get_id();
        cout << "Main thread id: " << thread_id << endl;

    }
    //3
    {
       thread th1(owner);
       thread th2(thief);
       th1.join();
       th2.join();
    }
    
    
}
