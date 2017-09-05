#include "register_manager.h"

register_manager::register_manager()
{
    regs = { {"$t0", true}, {"$t1", true}, {"$t2", true}, {"$t3", true}, 
    {"$t4", true}, {"$t5", true}, {"$t6", true}, {"$t7", true},
    {"$t8", true}, {"$t9", true} };
}

string register_manager::get_free_register()
{
    for(map<string, bool>::iterator it = regs.begin(); it != regs.end(); it++)
    {
        if(it->second)
        {
            it->second = false;
            return it->first;
        }
    }

    return "empty";
}

void register_manager::free_register(string reg)
{
    regs[reg] = true;
}