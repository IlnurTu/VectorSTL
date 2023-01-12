#include "MyVector/MyVector.h"
#include "MyVector/MyContiguousIterator.h"

int main() {
    Vector<int> ArrayInt;
    for(int i = 0;i<10;++i){
        ArrayInt.push_back(i);
    }
    for(const auto& el : ArrayInt){
        std::cout<<el<<' ';
    }
    return 0;
}
