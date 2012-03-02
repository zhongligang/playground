/**
 * Copyright (c) 2012 Flatter World. All Rights Reserved
 * $Id$ 
 * 
 * @file random.cc
 * @author zhongligang <ligang@flatterworld.com>
 * @date 2012-02-20 18:44:49
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    char buffer[1024];
    ifstream in("bj");
    ofstream out("bj.out");
    string name;
    string domain;
    string str;
    int pos;
    map<string, vector<string> > m;
    map<string, vector<string> >::iterator itr;
    int i;

    i = 0;
    while (!in.eof()) {
       in.getline(buffer, 1024); 

        str.assign(buffer);
        pos = str.find('@');
        if (pos == -1) {
            continue;
        }
        name = str.substr(0, pos);
        domain = str.substr(pos + 1, str.size() - pos - 1);

        itr = m.find(domain);
        if (itr != m.end()) {
            itr->second.push_back(name);
        } else {
            vector<string> vct;
            vct.clear();
            vct.push_back(name);
            m.insert(map<string, vector<string> >::value_type(domain,vct));
        }
        i++;
        if (i > 10) {
            break;
        }
    }

    while (true) {
        if (m.size() == 0) {
            break;
        }
        itr = m.begin();
        while (itr != m.end()) {
            out<<itr->second.back()<<"@"<<itr->first<<endl;
            itr->second.pop_back();
            if (itr->second.empty()) {
                m.erase(itr++);
            } else {
                itr++;
            }
        }
    }
}

/* vim: set ts=4 sw=4 sts=4 tw=100 et: */
