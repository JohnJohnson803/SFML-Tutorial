#include <iostream>

class myFamily
{
    public:
    std::string myMom;
    std::string myDad;
    std::string mySister;

    myFamily()
    {
        myMom = "Rose Johnson";
        myDad = "James Johnson";
        mySister = "Tabatha";
    }

};

int main()
{
    myFamily myFamily;
    myFamily.myDad = "Unknown";
    std::cout << myFamily.myDad << std::endl;

    return 0;
}