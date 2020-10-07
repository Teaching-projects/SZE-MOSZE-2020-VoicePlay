#pragma once

class jsonparser{
private:
public:
    static std::string rFVbQ (std::string st){   // alias: returnFirstValuebetweenQuotationmarks, finds the first substring that sits between " marks and returns it
        if (st.find('"') == std::string::npos) throw "invalid json syntax"; // if doesn't contain throw
        std::string tmp = st.substr(st.find('"')+1);
        if (tmp.find('"') == std::string::npos) throw "invalid json syntax"; // if doesn't contain throw
        return tmp.substr(0,tmp.find('"'));
    }
};