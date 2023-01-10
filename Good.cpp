#include "Good.h"
 Good::Good()
 {
    store = nullptr;
 }   
void Good::SetStore(Commercial * shop)
{
    this->store = shop;
}
bool Good::HasStore()
{
    if(this->store != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}