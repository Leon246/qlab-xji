#pragma once

#ifndef QUANTLABCODINGTEST_H
#define QUANTLABCODINGTEST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>

using std::string;
using std::map;
using std::unordered_map;
using std::ostream;
using std::ifstream;
using std::istringstream;

typedef unsigned long long int ulli;

class asset {
public:
    asset(const string&, ulli, int, int);
    ~asset() = default;

    void update(ulli, int, int);
    ostream& print(ostream&) const;

    string get_name() const { return name; }
    ulli get_max_gap() const { return max_gap; }
    int get_tot_vol() const { return tot_vol; }
    int get_max_price() const { return max_price; }
    int get_wa_price() const { return wa_price; }
private:
    string name;
    ulli prev_timestamp;
    ulli max_gap;
    int tot_vol;
    int max_price;
    int wa_price;
    ulli tot_pricevol;
};

inline ostream& operator<<(ostream& os, const asset& s) {
    return s.print(os); 
}

class query {
public:
    query() = default;
    query(const query&) = delete;
    query& operator=(const query&) = delete;
    ~query() = default;

    // potential overriding/overloading for other means of input streams
    virtual void process(const string&);
    void readline(const string&, ulli, int, int);
    ostream& print(ostream&) const;

    const unordered_map<string, asset>& get_asset_db() const { return asset_db; }
private:
    // database constantly asscessed/updated for each readline
    // using hashmap for O(1) efficiency
    unordered_map<string, asset> asset_db;
};

inline ostream& operator<<(ostream& os, const query& q) {
    return q.print(os);
}

#endif