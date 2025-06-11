
#include <iostream>

#include "Dispatcher.hpp"

class Obj
{
public:
    Obj() = default;
    void Print_i(int i) {std::cout << "Obj::Print_i" << std::endl; }
    void Print() {std::cout << "Obj::Print" << std::endl; }
    void Printer(int i) {std::cout << "Obj::Printer" << std::endl; }
};

void TestDispatcher()
{
    Obj moshe;
    ilrd::Callback callb(moshe,
        &Obj::Print_i, &Obj::Print);
    Obj mosh;
    ilrd::Callback callb2(mosh, &Obj::Printer,
                                        &Obj::Print);
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