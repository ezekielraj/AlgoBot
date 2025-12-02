#include <iostream>
#include "stocksdb.h"
#include "boughtdb.h"

int main()
{
        StocksDB sdb;
        BoughtDB bdb;
        char choice;
        std::string stockValue;
    try {
        sdb.changeDBNameToYesterday();
        std::vector<std::vector<std::string>> results = sdb.searchStock();

        for( auto &item : results)
        {
            for( auto &field : item)
            {
                std::cout << field << "  is this bought ? [y/n] :";
                std::cin >> choice;
                if(choice == 'y' || choice == 'Y')
                {
                    std::cout << "Enter the bought value : ";
                    std::cin >> stockValue;
                    bdb.addEntry(field, stockValue);
                }        
            }
            std::cout << std::endl;
        }
         
    } catch (const std::exception& e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
    }
    return 0;
}