#include "sensors_loader.hpp"

using namespace std;

namespace impl
{

unique_ptr<home::SensorAgent> makeAgent(std::vector<string>& a_words)
{
    if (a_words[2] == "temperature") 
    {
        return unique_ptr<home::SensorAgent>(new home::TemperatureSensor(a_words[0], a_words[1], a_words[2], a_words[3], a_words[4], a_words[5], "127.0.0.1", 5555));
    }
    else if (a_words[2] == "lights") 
    {
        return unique_ptr<home::SensorAgent>(new home::LightSensor(a_words[0], a_words[1], a_words[2], a_words[3], a_words[4], a_words[5], "127.0.0.1", 5555));
    }
    else if (a_words[2] == "fire") 
    {
        return unique_ptr<home::SensorAgent>(new home::FireSensor(a_words[0], a_words[1], a_words[2], a_words[3], a_words[4], a_words[5], "127.0.0.1", 5555));
    }

    return unique_ptr<home::SensorAgent>(new home::SensorAgent(a_words[0], a_words[1], a_words[2], a_words[3], a_words[4], a_words[5], "127.0.0.1", 5555));
}


}//namespace impl

namespace home
{

SensorsLoader::SensorsLoader()
{

}

void SensorsLoader::readFile(std::ifstream& file, std::vector< std::unique_ptr<SensorAgent>>& a_agents)
 {
    string line, word1, word2, word3; 

    while(file.good())
    {
        vector<string> words;
        getline(file, line);
        if(!(line.size() > 0)){continue;} 
        words.push_back(line);
        
        while(line.size() > 0 && file.good())
        {
            getline(file, line);
            if (line.size() > 0)
            {
                stringstream iss(line);
                iss >> word1 >> word2 >> word3;
                
                if(word1.compare("config") != 0)
                {
                    words.push_back(word3); 
                }
                else
                {
                    std::size_t pos = line.find("=");    
                    word3 = line.substr(pos+2);          
                    words.push_back(word3);        
                }
            }
        } 
        
        a_agents.push_back(impl::makeAgent(words));
    } 
}


}// namespace home

