#include<iostream>
#include "boughtdbc.h"
using namespace std;

int main() {

        BoughtDBC bdbc;
        std::vector<std::vector<std::string>> boughtStocks = bdbc.getAll();
        for (const auto& row : boughtStocks) {
            std::cout << row[1] << ": GTT Sell Value :" << ((double(std::stod(row[2]))*10)/9) << std::endl;;
        }
    return 0;
}
