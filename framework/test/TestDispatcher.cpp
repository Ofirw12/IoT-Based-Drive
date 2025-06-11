
#include <iostream>
#include "Dispatcher.hpp"

class Moshe
{
public:
    Moshe() = default;
    void Do(int i) {std::cout << "Moshe::Do" << std::endl; }
    void DoHast() {std::cout << "Moshe::DoHast" << std::endl; }
    void DoHastMich(int i) {std::cout << "Moshe::DoHastMich" << std::endl; }
};

void TestDispatcher()
{
    Moshe moshe;
    ilrd::Callback callb(moshe,
        &Moshe::Do, &Moshe::DoHast);
    Moshe mosh;
    ilrd::Callback callb2(mosh, &Moshe::DoHastMich,
                                        &Moshe::DoHast);
    ilrd::Dispatcher<int> dispa;
    dispa.Register(&callb);
    dispa.Register(&callb);
    dispa.Notify(4);

    dispa.Register(&callb2);
    dispa.Register(&callb2);
    dispa.Unregister(&callb);
    dispa.Register(&callb);
    dispa.Notify(5);
    dispa.Unregister(&callb2);
    dispa.Unregister(&callb2);
    dispa.Notify(6);
}

int main()
{
    TestDispatcher();
    return 0;
}