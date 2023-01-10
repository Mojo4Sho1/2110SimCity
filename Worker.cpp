#include "Worker.h"
Worker::Worker()
{
    this->job = nullptr;
}                  
void Worker::SetEmployment(Cell * loc)
{
    this->job = loc;
}
Cell* Worker::IsEmployed()
{
    if(job == nullptr)
    {
        return nullptr;
    }
    else
    {
        return job;
    }
}           