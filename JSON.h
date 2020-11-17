#pragma once

#include <sstream>      // std::istringstream
#include <map> 
#include <list>
#include <fstream>
#include <exception>
#include <algorithm>
#include <string>
#include <iostream>
#include <variant>

using MAP = std::map<std::string, std::variant<std::string,int,double>>;

class JSON {
private:
    MAP content;
    class JSONparser{
    private:
        static std::string rFVbQ (std::string st){   // alias: returnFirstValuebetweenQuotationmarks, finds the first substd::string that sits between " marks and returns it
            auto fstr = st.find('"');
            if (fstr == std::string::npos) return st; // if doesn't return st
            auto sstr = st.substr(fstr+1).find('"');
            if (sstr == std::string::npos) return st; // if doesn't return st
            return st.substr(fstr+1,sstr);
        }
    public:
        static std::map<std::string, std::string>  istrmInp(std::stringstream& f){ // read the given istream file and convert the data to a map
            std::map<std::string, std::string> parsed;
            std::string t = "";
            std::string asd;
            while (std::getline(f, t)) {
                if (t == "}" || t == "{") continue;
                try {
                    std::string p1,val;
                    while(t!=""){
                        p1 = JSONparser::rFVbQ(t);
                        if ( parsed.find(p1) != parsed.end()) throw -1;
                        else{
                            auto d = t.find(":");
                            if ( d == std::string::npos) throw -3;
                            t = t.substr(d+1);
                            auto d1 = t.find('"');
                            auto d2 = t.find(',');
                            if(d1<d2){
                                val=t.substr(d1+1);
                                val=val.substr(0,val.find('"'));
                            }else{
                                val = t.substr(0,t.find(','));
                            }
                            if(d2 == std::string::npos){
                                t = "";
                            }else{
                                t = t.substr(t.find(val)+val.size());
                                t = t.substr(t.find_first_of("\n,")+1);
                            }
                            parsed.insert(std::pair<std::string, std::string>(p1,val));
                        }
                    }
                }catch(const int& e){
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
        static MAP fileInp(std::string fname){ // read lines from file and convert to istream
            MAP parsed;
            std::ifstream f(fname);   
            std::string t,w;
            if (!f) throw fname+" file does not exist!" ;
            while (!f.eof()) {
                    std::getline(f,t);
                    w+=t+'\n';            
            }
            f.close();
            std::stringstream istr(w);
            std::map<std::string, std::string> tmp = JSONparser::istrmInp(istr);
            for (auto v: tmp){
                try{
                    parsed.insert(std::pair<std::string, std::variant<std::string,int,double>>(v.first,std::stod(v.second)));
                }catch(const std::invalid_argument& ia){
                    parsed.insert(std::pair<std::string, std::variant<std::string,int,double>>(v.first,JSONparser::rFVbQ(v.second)));
                }
            }
            return parsed;
        }
        static MAP  strInp(std::string str){    // convert the given std::string to istream
            MAP parsed;
            std::stringstream f(str);
            std::map<std::string, std::string> tmp = JSONparser::istrmInp(f);
            for (auto v: tmp){
                try{
                    parsed.insert(std::pair<std::string, std::variant<std::string,int,double>>(v.first,std::stod(v.second)));
                }catch(const std::invalid_argument& ia){
                    parsed.insert(std::pair<std::string, std::variant<std::string,int,double>>(v.first,JSONparser::rFVbQ(v.second)));
                }
            }
            return parsed;
        }

};
public:
    JSON(MAP content): content(content) {}
    static JSON parseFromFile(std::string fname){
        MAP res = JSONparser::fileInp(fname);
        return JSON(res);
    }
    static JSON parseFromString(std::string str){
        MAP res = JSONparser::strInp(str);
        return JSON(res);
    }
	int count(const std::string& key)
	{
		if (content.count(key)) return 1;

		return 0;
	}

	template<typename T>
	T get(const std::string& key)
	{
		T returner = std::get<T>(content.at(key));
		return returner;

	}
    class ParseException : std::exception
	{
	public:
		ParseException(){}
	};
};