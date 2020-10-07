#pragma once

#include <map>
#include <sstream>

class jsonparser{
private:
public:
    static std::string rFVbQ (std::string st){   // alias: returnFirstValuebetweenQuotationmarks, finds the first substring that sits between " marks and returns it
        if (st.find('"') == std::string::npos) throw "invalid json syntax"; // if doesn't contain throw
        std::string tmp = st.substr(st.find('"')+1);
        if (tmp.find('"') == std::string::npos) throw "invalid json syntax"; // if doesn't contain throw
        return tmp.substr(0,tmp.find('"'));
    }
    static map<string, string>  istrmInp(std::istringstream& f){ // read the given istream file and convert the data to a map
        map<string, string> parsed;  
        std::string t = "";
        while (true) {
            //t = f.str();
            getline(f, t);
            cout << t << " asd \n";
            if (t.find('{') != std::string::npos) continue;
            if (t.find('}') != std::string::npos) break;
            try {
                std::string p1 = jsonparser::rFVbQ(t);
                if ( parsed.find(p1) != parsed.end()) throw "double declaration of variable name\n";
                parsed.insert(pair<std::string, std::string>(p1,t.substr(t.find(": ")+2))); //insert var name and value as strings
            }
            catch(const char* e)    {
                std::cerr << e << '\n';
                std::exit(-1);
            }               
        }
        return parsed;
    }
    static map<string, string>  fileInp(std::string fname){ // read lines from file and convert to istream
        map<string, string> parsed;
        std::ifstream f(fname);   
        std::string t,w;
        if (!f) throw fname+" file does not exist!" ;
        while (!f.eof()) {
                std::getline(f,t);
                w+=t+'\n';            
        }
        f.close();
        istringstream istr(w);
        return jsonparser::istrmInp(istr);
    }
    static map<string, string>  strInp(std::string str){    // convert the given string to istream
        istringstream f(str);
        return jsonparser::istrmInp(f);
    }
};