#include "JSON.h"

enum vartypes {string, integer, doubl, ls}; ///< enumerate to seperate different datatypes of keys's values
using MAP = std::map<std::string, std::variant<std::string, int, double, JSON::list>>;

MAP JSON::parseFromIstr (std::stringstream& f){ // read the given istream file and convert the data to a map
    MAP parsed;
    std::list <std::variant<std::string, int, double >>  listvalues;
    std::string t = "";
    int vartype;
    while (std::getline(f, t)) {
        if (t == "}" || t == "{") continue;
        try {
            std::string p1,val;
            while(t!=""){
                p1 = JSON::rFVbQ(t);
                if ( parsed.find(p1) != parsed.end()) throw -1;
                else{
                    auto d = t.find(":");
                    if ( d == std::string::npos) throw -3;
                    val = t.substr(d+1);
                    val = val.substr(val.find_first_not_of(" \t\v"));
                    size_t pos1 = val.find_first_not_of(" \t\v");
                    if (val[0] == '\"'){
                        val = val.substr(1);
                        val = val.substr(0, val.find_first_of("\""));
                        vartype = string;
                        t = t.substr(t.find(val) + val.size());
                        t = t.substr(t.find_first_of("\n,") + 1);
                    }else if (pos1 != std::string::npos && val[pos1] == '[') {
                        vartype = ls;
                        val = val.substr(1);
                        do{
                            if (val == ""){
                                std::getline(f, val);
                                continue;
                            }
                            pos1 = val.find_first_not_of(" \t\v");
                            if (pos1 != std::string::npos && val[pos1] == '\"'){
                                val = val.substr(pos1 + 1);
                                pos1 = val.find("\"");
                                listvalues.push_back(val.substr(0, pos1));
                            }
                            val = val.substr(pos1);
                            pos1 = val.find_first_not_of(" \t\v\"");
                            if (pos1 != std::string::npos && val[val.find_first_not_of(" \t\v\"")] == ']') break;
                            std::getline(f, val);
                        } while (pos1 == std::string::npos || val[val.find_first_not_of(" \t\v")] != ']');
                        t = "";
                    }else{
                        val = val.substr(0,val.find_first_of(","));
                        if (val.find('.') != std::string::npos){
                            vartype = doubl;
                        }else{
                            vartype = doubl;
                        }
                        t = t.substr(t.find(val) + val.size());
                        t = t.substr(t.find_first_of("\n,") + 1);
                    }
                    if (t.find_first_not_of(" ,\n\t\"") == std::string::npos || t[t.find_first_not_of(",\n\t\" ")] == '}'){
                        t = "";
                    }
                    std::variant<std::string, int, double, list> mapvalue;
                    if (vartype == string)
                    {
                        mapvalue = val;
                    }
                    else if (vartype == integer)
                    {
                        mapvalue = std::stoi(val);
                    }
                    else if (vartype == doubl)
                    {
                        mapvalue = std::stod(val);
                    }
                    else if (vartype == ls)
                    {
                        mapvalue = list(listvalues);
                    }
                    parsed[p1] = mapvalue;
                }
            }
        }catch(const int e){
            switch (e) {
            case -1:
                std::cerr << "double declaration of variable name\n";
                std::exit(-1);
            case -3:
                std::cerr << "Invalid json syntax\n";
                std::exit(-1);
            }
        }               
    }
    return parsed;
}