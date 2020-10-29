#pragma once

#include <sstream>      // std::istringstream
#include <map> 
#include <fstream>
#include <iostream>

class jsonparser{
private:
public:
    static std::string rFVbQ (std::string st){   // alias: returnFirstValuebetweenQuotationmarks, finds the first substd::string that sits between " marks and returns it
        auto fstr = st.find('"');
        if (fstr == std::string::npos) throw -2; // if doesn't contain throw
        auto sstr = st.substr(fstr+1).find('"');
        if (sstr == std::string::npos) throw -2; // if doesn't contain throw
        return st.substr(fstr+1,sstr);
    }
    static std::map<std::string, std::string>  istrmInp(std::stringstream& f){ // read the given istream file and convert the data to a map
        std::map<std::string, std::string> parsed;
        std::string t = "";
        while (!f.eof()) {
            getline(f, t);
            try {
                std::string p1 = jsonparser::rFVbQ(t);
                if ( parsed.find(p1) != parsed.end()) throw -1;
                else{
                    auto d = t.find(": ");
                    if ( d == std::string::npos) throw -3;
                    parsed.insert(std::pair<std::string, std::string>(p1,t.substr(d+2))); //insert var name and value as std::strings
                }
            }
            catch(const int& e){
                switch (e) {
                case -1:
                    std::cerr << "double declaration of variable name\n";
                    std::exit(-1);
                case -2:
                    //std::cerr << "no key found";
                    continue;
                case -3:
                    std::cerr << "Invalid json syntax\n";
                    std::exit(-1);
                }
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