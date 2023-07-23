#pragma once

namespace pixel
{


// Heap data structure
template <typename T>
class priority_queue
{
    public:
        priority_queue();
        priority_queue(priority_queue& q);
        priority_queue(priority_queue&& q);
        ~priority_queue();

    private:
};

}
