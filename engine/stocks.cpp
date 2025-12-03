#include <iostream>
#include "stocks.h"
#include "IndexLists.h"
#include "StockLists.h"
#include "stocksdb.h"
#include "StockData.h"
#include "StockMetaData.h"
#include "StockQuoteData.h"
#include "StockYearWiseData.h"
using json = nlohmann::json;
int main() {
    
    /*RequestTask task("https://www.nseindia.com/api/equity-master");
    try {
        std::string response = task.fetch();
        std::cout << "Response: " << response << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }*/
    IndexLists indexLists;
    std::vector<std::unique_ptr<StockLists>> stockLists;
    std::unique_ptr<StockMetaData> stockMetaData;
    std::unique_ptr<StockQuoteData> stockQuoteData;
    std::unique_ptr<StockYearWiseData> stockYearWiseData;
    std::vector<json> v;
    try {
        StocksDB sdb;

        std::vector<std::string> response = indexLists.fetchIndexList();
        std::vector<std::vector<std::string>> vectorLists = indexLists.getList();
        std::vector<std::pair<std::string, StockData>> tempStockList;

size_t total = 0;
for (const auto& inner : vectorLists) {
    total += inner.size();
}
size_t totalsize = 0;
int i =0;
int j =1;

        for (const std::vector<std::string>& vectorList : vectorLists) {
            for (const std::string& index : vectorList) {
                i++;
                j=1;
                //std::cout << index << std::endl;
                stockLists.push_back(std::make_unique<StockLists>(index));
                StockLists* ptr = stockLists.back().get();
                ptr->fetchStockList();
                tempStockList = ptr->getList();
                totalsize = tempStockList.size();
                for(std::pair<std::string, StockData>& stock : tempStockList)
                {
                    std::cout <<j++ << "/" << totalsize << " "<< i << "/" << total << " ";
                    std::cout << stock.first << std::endl; 
                    if(!sdb.checkEntryExists(stock.first))
                    {
                        stockMetaData = std::make_unique<StockMetaData>(stock.first);
                        stockMetaData->fetchStockMetaData();
                        stock.second.market_type = stockMetaData->getData();
                        stockQuoteData = std::make_unique<StockQuoteData>(stock.second.market_type, stock.second.series, stock.second.symbol);
                        stockYearWiseData = std::make_unique<StockYearWiseData>(stock.second.symbol, stock.second.market_type, stock.second.series);
                        stockQuoteData->fetchStockQuoteData();
                        stockYearWiseData->fetchStockWeekData();
                        std::string pevalue = stockQuoteData->getData();
                        double weak_change_per = stockYearWiseData->getData();
                        if(pevalue != "0" && weak_change_per != 0){
                            sdb.addEntry(stock.second.symbol, pevalue, weak_change_per, stock.second.market_type, stock.second.series);
                        }
                    }
                }                
            }
        }


    } catch (const std::exception& e) {
        std::cerr << "Error fetching index list: " << e.what() << std::endl;
    }
    
    std::cout << "Stocks" << std::endl;
    return 0;
}