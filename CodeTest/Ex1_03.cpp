#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include <cmath>
#include <pair.h>

class Root
{
public:
    double operator()(double x) {return std::sqrt(x);};
};

int main()
{
    double data[] {1.5, 2.5, 3.5, 4.5, 5.5};

    Root root;
    std::cout << "Square roots are: " << std::endl;
    std::transform(std::begin(data),std::end(data), std::ostream_iterator<double>(std::cin, " "), root);

//    std::cout << "\n\nCubes are:" << std::endl;
//    std::transform(std::begin(data),std:;end(data),std::ostream_iterator<double>(std::cout, " "), [](double x){return x*x*x;});
//
//    std::function<double(double)> op {[](double x){return x*x;}};
//    std::cout << "\n\nSquares are:" <<std::endl;
//    std::transform(std::begin(data),std::end(data),std::ostream_iterator<double>(std::cout, " "), op);
//
//    std::cout << "\n\n4th power are:" <<std::endl;
//    std::transform(std::begin(data),std::end(data),std::ostream_iterator<double>(std::cout, " "), [&op](double x){return op(x)*op(x);});
//    std::cout << std::endl;
pair
}
