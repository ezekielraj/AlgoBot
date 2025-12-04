#include <iostream>
#include "StockYearWiseData.h"

#include "boughtdb.h"
#include "boughtdbc.h"
int main()
{
    std::cout << "Sell Interface" << std::endl;
    BoughtDB bdb;
    BoughtDBC bdbc;
    std::vector<std::string> boughtStocks = bdb.getAllBoughtStocks();
    std::unique_ptr<StockYearWiseData> stockYearWiseData;
    std::vector<std::string> boughtStockc;// = bdb.getAllBoughtStocks();
    std::string mtype, series;
    for( const auto& stock : boughtStocks ) {
        boughtStockc = bdbc.checkEntryExists(stock);
        mtype = boughtStockc[3];
        series = boughtStockc[4];
        stockYearWiseData = std::make_unique<StockYearWiseData>(stock, mtype, series);
        stockYearWiseData->fetchStockWeekData();
        double weak_change_per = stockYearWiseData->getData();
        //if(pevalue != "0" && weak_change_per != 0){
        if(weak_change_per > 10){
            std::cout << "Sell Stock: " << stock << std::endl;
            std::cout << weak_change_per << std::endl;
        }
        //}

        
    }
std::cout << "Sell Interface End" << std::endl;    
return 0;
}