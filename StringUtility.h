//
//  StringUtility.h
//  testtest
//
//  Created by  on 12/07/18.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef _StringUtility_h
#define _StringUtility_h
#include "string"
#include "vector"

using namespace std;

namespace CornStarch {
    class CStringUtility
    {
    public:
        static vector<string> split(string str, string delim);
    };
}

#endif
