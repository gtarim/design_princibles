#include <iostream>
#include <vector>
#include <memory>

namespace before
{
class ProcessManager
{
    std::vector<int> pids;
public:
    void add(int pid) { pids.push_back(pid); }
    void run() 
    {
        while(pids.size())
        {
            std::cout << pids.back() << "\n";
            pids.pop_back(); 
        }
    }
};
};

///////////////

namespace after
{
struct Process
{
    std::vector<int> pids;
    void add(int pid){ pids.push_back(pid); }
};
class ProcessManager
{
    std::shared_ptr<Process> process;
public:
    ProcessManager(std::shared_ptr<Process> process) : process{process} { }
    void run()
    {
        while(process->pids.size())
        {
            std::cout << process->pids.back() << "\n";
            process->pids.pop_back();
        }
    }
};
};

int main()
{
    std::cout << "before:\n";
    before::ProcessManager mgr;
    mgr.add(10);
    mgr.add(20);
    mgr.add(30);
    mgr.run();

    ///////////////

    std::cout << "after:\n";
    auto process = std::make_shared<after::Process>();
    process->add(10);
    process->add(20);
    process->add(30);
    after::ProcessManager mgrAfter{process};
    mgrAfter.run();
}