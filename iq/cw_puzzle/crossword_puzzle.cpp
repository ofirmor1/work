#include "crossword_puzzle.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace iq
{
Grid::Grid(std::string const& a_wordsFilePath, std::string const& a_gridpFileath, std::string const& a_directions)
: m_matrix()
, m_directVec()
, m_directMap()
{
    loadGrid(a_gridpFileath);
    m_rows = m_matrix.size();
    m_columns = m_matrix[0].size();
    buildDirectionMap();
    searchDirections(a_directions); 
    loadWords(a_wordsFilePath);
}

void Grid::loadGrid(std::string const& a_gridFilePath)
{
    std::ifstream file;
    file.open(a_gridFilePath);
    if(file.fail())
    {
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::vector<char> row;

        for (char const& ch : line)
        {
            if (ch != ' ')
            {
                row.push_back(ch);
            }   
        }
        m_matrix.push_back(row);
    }
}

void Grid::loadWords(std::string const& a_wordsFilePath)
{
    std::ifstream file;
    file.open(a_wordsFilePath);
    
    std::string line;
    while(!file.fail())
    {
        std::string line;
        getline(file, line);
        
        if(line.empty())
        {
            break;
        }
        m_wordsVec.push_back(line);
    }
    for (size_t i = 0; i < m_wordsVec.size(); ++i)
    {
        searchWord(m_wordsVec[i]);
    }  
}

void Grid::buildDirectionMap()
{
    m_directMap['r'] = {1, 0};
    m_directMap['l'] = {-1, 0};
    m_directMap['u'] = {0, 1};
    m_directMap['d'] = {0, -1};
    m_directMap['x'] = {-1, -1};
    m_directMap['y'] = {1, -1};
    m_directMap['z'] = {-1, 1};
    m_directMap['t'] = {1, 1};
}

void Grid::searchDirections(std::string const& a_directions)
{
    std::unordered_map<char, std::pair<int, int>>::iterator it;
    for (size_t i = 0; i < a_directions.length(); ++i)
    {
        it = m_directMap.find(a_directions[i]);
        if(it != m_directMap.end())
        {
            m_directVec.push_back(m_directMap[a_directions[i]]);
        }
    }
    // for(auto e : m_directVec)
    // {
    //     std::cout << e.first << e.second << std::endl;
    // }
}

void Grid::searchWord(std::string const& a_word)
{
    for (int row = 0; row < m_rows; ++row)
    {
        for (int col = 0; col < m_columns; ++col)
        {
            for (auto dir : m_directVec) 
            {
                int rd = row + dir.first;
                int cd = col + dir.second;
                if (m_matrix[row][col] != a_word[0])
                {
   
                    break;
                }
                size_t index = 1;
                for (;index < a_word.length(); ++index) 
                {
                    if (m_matrix[rd][cd] != a_word[index])
                    {
                        break;
                    }
                    
                    if (rd >= m_rows || rd < 0 || cd >= m_columns || cd < 0)
                    {
                        
                        break;
                    }           
                    rd += dir.first, cd += dir.second;
                }

                if (index == a_word.length())
                {
                    updateWordsTable(a_word);
                }    
            }
        }
    }
}

void Grid::updateWordsTable(std::string const& a_word)
{
    ++m_wordsFrequency[a_word];
}

void Grid::printWordsFrequency()
{
    for (auto const& pair : m_wordsFrequency)
    {
        std::cout << "word: " << pair.first << std::endl;
        std::cout << "frequency: "<< pair.second << std::endl;
    }
}
 
}//namespace iq


