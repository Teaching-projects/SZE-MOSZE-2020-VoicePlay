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
#include <fstream>

class JSON{
public:
	class list
	{
		std::list<std::variant<std::string, int, double>> List;
	public:
		list(std::list<std::variant<std::string, int, double>> ls) : List(ls){}
		auto begin(){
			return List.begin();
		}
		auto end(){
			return List.end();
		}
		friend bool operator==(const list& lh, const list& rh){
			return lh.List == rh.List;
		}
	};
private:
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> content;
	static std::string rFVbQ (std::string st){   // alias: returnFirstValuebetweenQuotationmarks, finds the first substd::string that sits between " marks and returns it
        auto fstr = st.find('"');
        if (fstr == std::string::npos) return st; // if doesn't return st
        auto sstr = st.substr(fstr+1).find('"');
        if (sstr == std::string::npos) return st; // if doesn't return st
        return st.substr(fstr+1,sstr);
    }
public:
    JSON(){}
	JSON(std::map<std::string, std::variant<std::string, int, double, JSON::list>> cont) : content(cont) {}
    static std::map<std::string, std::variant<std::string, int, double, JSON::list>> parseFromIstr(std::stringstream& f);
	static JSON parseFromFile(std::string fname){
        std::ifstream f(fname);   
        std::string t,w;
        if (!f) throw fname+" file does not exist!" ;
        while (!f.eof()) {
                std::getline(f,t);
                w+=t+'\n';            
        }
        f.close();
        std::stringstream istr(w);
        std::map<std::string, std::variant<std::string, int, double, JSON::list>> res = JSON::parseFromIstr(istr);
        return JSON(res);
    }
    static JSON parseFromString(std::string str){
        std::stringstream f(str);
        std::map<std::string, std::variant<std::string, int, double, JSON::list>> res = JSON::parseFromIstr(f);
        return JSON(res);
    }
    JSON operator= (std::map<std::string, std::variant<std::string, int, double, JSON::list>> other) {
		JSON json(other);
		return json;
	}

	template<typename T>
	T get(const std::string& key){
		T returner = std::get<T>(content.at(key));
		return returner;
	}
	int count(const std::string& key) {
		if (content.count(key)) return 1;
		return 0;
	}
	class ParseException : std::exception{
		public:
		ParseException() {}
	};
};