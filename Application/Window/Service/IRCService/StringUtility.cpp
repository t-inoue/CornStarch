//
//  StringUtility.cpp
//  testtest
//
//  Created by  on 12/07/18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "StringUtility.hpp"
using namespace std;

namespace CornStarch {
    
    vector<wxString> CStringUtility::split(wxString str, wxString delim)
    {
        std::vector<wxString> items;
        std::size_t delimIndex = str.find_first_of(delim);
        if(wxString::npos == delimIndex) {
            items.push_back(str.substr(0, delimIndex));
        }
        while(wxString::npos != (delimIndex = str.find_first_of(delim))) {
            if(wxString::npos == str.find_first_not_of(delim)) {
                break;
            }
            items.push_back(str.substr(0, delimIndex));
            delimIndex++;
            str = str.erase(0, delimIndex);
            if(wxString::npos == str.find_first_of(delim) && "" != str) {
                items.push_back(str);
                break;
            }
        }
        return items;
    }

}
