#pragma once

#ifndef QUANTLABCODINGTEST_H
#define QUANTLABCODINGTEST_H

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
private:
    string name;
    ulli prev_timestamp;
    ulli max_gap;
    int tot_vol;
    int max_price;
    int wa_price;
    ulli tot_pricevol;
};

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

private:
    unordered_map<string, asset> asset_db;
};

#endif