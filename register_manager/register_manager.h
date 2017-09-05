#ifndef REGISTER_MANAGER
#define REGISTER_MANAGER

#include <string>
#include <map>

using namespace std;

class register_manager
{
public:
    map<string, bool> regs;

    register_manager();
    string get_free_register();
    void free_register(string reg);
};

#endif