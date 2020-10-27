/**
* \class jsonparser
*
* \brief jsonparser class
*
* This class contains the file reading logic of the project.
*
* \author Voros Bence, team VoicePlay
*
* \version 1.0
*
* \date 2020/10/27 21:45
*
* Created on: 2020/10/27 21:45

*/

#pragma once

#include <sstream>
#include <map> 
#include <fstream>
#include <iostream>

class jsonparser{
private:
public:
    /**
    * \brief This function finds the strings between " characters.
    * \return The string between " characters
    */
    static std::string rFVbQ (std::string st){   // alias: returnFirstValuebetweenQuotationmarks, finds the first substd::string that sits between " marks and returns it
        auto fstr = st.find('"');
        if (fstr == std::string::npos) throw -2; // if doesn't contain throw
        auto sstr = st.substr(fstr+1).find('"');
        if (sstr == std::string::npos) throw -2; // if doesn't contain throw
        return st.substr(fstr+1,sstr);
    }

    /**
    * \brief This function reads the file given to it, converts into map, and throws exceptions if it does not match the expected format.
    * \return map converted from the data given to the function
    */
    static std::map<std::string, std::string>  istrmInp(std::stringstream& f){
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

    /**
    * \brief This function converts the file to istream.
    * \return The map created by istrmINP() function from the file
    */
    static std::map<std::string, std::string>  fileInp(std::string fname){
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

    /**
    * \brief This function converts a given string to istream.
    * \return The map created by istrmINP() function from a string
    */
    static std::map<std::string, std::string>  strInp(std::string str){
        std::stringstream f(str);
        return jsonparser::istrmInp(f);
    }
};