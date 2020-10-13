#pragma once

#include <sstream>      // std::istringstream
#include <map> 
#include <fstream>

class jsonparser{
private:
public:
    static std::string rFVbQ (std::string st){   // alias: returnFirstValuebetweenQuotationmarks, finds the first substd::string that sits between " marks and returns it
        if (st.find('"') == std::string::npos) throw "invalid json syntax"; // if doesn't contain throw
        std::string tmp = st.substr(st.find('"')+1);
        if (tmp.find('"') == std::string::npos) throw "invalid json syntax"; // if doesn't contain throw
        return tmp.substr(0,tmp.find('"'));
    }
    static std::map<std::string, std::string>  istrmInp(std::stringstream& f){ // read the given istream file and convert the data to a map
        std::map<std::string, std::string> parsed;
        std::string t = "";
        while (true) {
            getline(f, t);
            if (t.find('{') != std::string::npos) continue;
            if (t.find('}') != std::string::npos) break;
            try {
                std::string p1 = jsonparser::rFVbQ(t);
                if ( parsed.find(p1) != parsed.end()) throw "double declaration of variable name\n";
                parsed.insert(std::pair<std::string, std::string>(p1,t.substr(t.find(": ")+2))); //insert var name and value as std::strings
            }
            catch(const char* e)    {
                std::cerr << e << '\n';
                //std::exit(-1);
            }               
        }
        return parsed;
    }
    static std::map<std::string, std::string>  fileInp(std::string fname){ // read lines from file and convert to istream
        std::map<std::string, std::string> parsed;
        std::ifstream f(fname);   
        std::string t,w;
        if (!f) throw fname+" file does not exist!" ;
        while (!f.eof()) {
                std::getline(f,t);
                w+=t+'\n';            
        }
        f.close();
        std::stringstream istr(w);
        return jsonparser::istrmInp(istr);
    }
    static std::map<std::string, std::string>  strInp(std::string str){    // convert the given std::string to istream
        std::stringstream f(str);
        return jsonparser::istrmInp(f);
    }
};