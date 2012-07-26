//
//  StringUtility.cpp
//  testtest
//
//  Created by  on 12/07/18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "StringUtility.h"
using namespace std;

namespace CornStarch {
    
    vector<string> CStringUtility::split(string str, string delim)
    {
        std::vector<std::string> items;
        std::size_t dlm_idx;
        if(str.npos == (dlm_idx = str.find_first_of(delim))) {
            items.push_back(str.substr(0, dlm_idx));
        }
        while(str.npos != (dlm_idx = str.find_first_of(delim))) {
            if(str.npos == str.find_first_not_of(delim)) {
                break;
            }
            items.push_back(str.substr(0, dlm_idx));
            dlm_idx++;
            str = str.erase(0, dlm_idx);
            if(str.npos == str.find_first_of(delim) && "" != str) {
                items.push_back(str);
                break;
            }
        }
        return items;
    }

}