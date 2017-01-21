#include "Quantlabcodingtest.h"

asset::asset(const string& symbol, ulli timestamp, int vol, int price) {
    name = symbol;
    prev_timestamp = timestamp;
    max_gap = 0;
    tot_vol = vol;
    max_price = wa_price = price;
    tot_pricevol = vol*price;
}

void asset::update(ulli timestamp, int vol, int price) {
    ulli gap = timestamp - prev_timestamp;
    max_gap = max_gap > gap ? max_gap : gap;
    prev_timestamp = timestamp;
    tot_vol += vol;
    max_price = max_price > price ? max_price : price;
    tot_pricevol += static_cast<ulli>(vol)*static_cast<ulli>(price);
    wa_price = static_cast<int>(tot_pricevol / static_cast<ulli>(tot_vol));
}

void query::readline(const string& symbol, ulli timestamp, int vol, int price) {
    const auto search_db = asset_db.find(symbol);
    if (search_db == asset_db.end()) {
        asset_db.insert(std::pair<string, asset>(symbol, asset(symbol, timestamp, vol, price)));
    }
    else {
        search_db->second.update(timestamp, vol, price);
    }
}

void query::process(const string& filename) {
    ifstream ifs(filename, ifstream::in);
    string line;
    while (std::getline(ifs, line)) {
        istringstream s(line);
        string item;
        std::getline(s, item, ',');
        char *pEnd;
        ulli timestamp = strtoull(item.c_str(), &pEnd, 10);
        std::getline(s, item, ',');
        string symbol = item;
        std::getline(s, item, ',');
        int vol = atoi(item.c_str());
        std::getline(s, item, ',');
        int price = atoi(item.c_str());

        readline(symbol, timestamp, vol, price);
    }
    ifs.close();
}

