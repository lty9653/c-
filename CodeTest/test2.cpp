#include <array>
#include <iostream>
#include <numeric>
int main(){
    std::array<double, 10> values;
    std::iota(std::begin(values),std::end(values),10.0);
    for(auto iter =  std::begin(values); iter!=std::end(values); iter++){
        *iter += 1;
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
    for(auto iter =  std::cbegin(values); iter!=std::cend(values); iter++){
        std::cout << *iter << " ";
    }
    std::cout << std::endl;
}
