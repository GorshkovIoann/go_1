#include <iostream>

#include "go.h"


int main()
{
    try
    {
        GO game{{0, 20}};
        
        return Graph_lib::gui_main();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}