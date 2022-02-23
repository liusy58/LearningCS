#include<thread>
class background_task
{
public:
    void do_something()const{}
    void do_something_else()const{}
    void operator()() const
    {
        do_something();
        do_something_else();
    }
};

int main(){
    std::thread my_thread(background_task());
}
