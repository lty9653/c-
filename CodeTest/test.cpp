#include <iostream>
#include <memory>
#include <numeric>
int main()
{
    auto pname = std::make_unique<std::string>("Algernon");
    pname.reset(new std::string{"Fred"});
    std::cout<<*pname << std::endl;

    auto up_name = std::make_unique<std::string> ("Algernon");
    std::unique_ptr<std::string> up_new_name{up_name.release()};
    if(up_new_name)
        std::cout << "The name is " << *up_new_name << std::endl;
    if(!up_name)
        std::cout << "The unique pointer is nullptr" << std::endl;
    std::cout << *up_new_name << std::endl;

    auto pn1 = std::make_unique<std::string>("Tack");
    auto pn2 = std::make_unique<std::string>("Till");
    pn1.swap(pn2);
    std::cout << *pn1 << " " << *pn2 << std::endl;


    auto pdata = std::make_shared<std::string>("kldla");
    std::shared_ptr<std::string> pdata2 {pdata};
    std::cout << pdata.unique();

    auto pData = std::make_shared<double>(9090);
    std::weak_ptr<double> pwData {pData};
      std::shared_ptr<double> pNew {pwData.lock()};
    if(pNew)
        std::cout << "\nShared" << std::endl;
    else
        std::cout << "Object no longer exists.\n";
}
