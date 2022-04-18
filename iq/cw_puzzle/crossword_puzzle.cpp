#include "crossword_puzzle.hpp"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace iq
{
Grid::Grid(std::string const& a_path)
: m_grid()
{
   loadGrid(a_path);
}

void Grid::loadGrid(std::string const& a_path)
{
    std::ifstream file;
    file.open(a_path);
    
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<char> row;

        for (char const& c : line)
        {
            if (c != ' ')
            {
                row.push_back(c);
            }   
        }
        m_grid.push_back(row);
    }
}

void Grid::searchWord(std::string const& a_word)
{
    char firstChar = a_word[0];
    unsigned int row = 0;
    auto it = m_grid[row].begin();
    std::cout <<  "it: " <<*it << std::endl;
    std::cout << "size: " <<m_grid.size() << std::endl;
    
    while (row < m_grid.size())
    {
        while(it != m_grid[row].end())
        {
            auto nextChar = std::find(it, m_grid[row].end(), firstChar);
            //check right   
            unsigned int i = 0;
            std::cout <<  "check: " <<row << std::endl;
            std::cout <<  "1: "  << *nextChar << std::endl;
            std::cout <<  "2: "  << nextChar - m_grid[row].begin() << std::endl;
            unsigned int col = nextChar - m_grid[row].begin();
            std::cout <<  "3: "  << col << std::endl;
            // std::cout <<  m_grid[i][col+1] << std::endl;
            std::cout <<  "4: "  << a_word[i] << std::endl;
            if(col < m_grid.size())
            {
                while (i < a_word.length() && m_grid[i][col+1] == a_word[i])
                {
                    ++i;
                }
                if (i == a_word.length())
                {
                    updateWordsTable(a_word);
                    break;
                }
            }

            //check left
            // it = std::find(++it, m_grid[row].end(), firstChar);
            // col = it - m_grid[row].begin();
            // std::cout <<  *it << std::endl;
            // std::cout <<  col << std::endl;
            i = 0;
            if(col > 0)
            {
                while (i < a_word.length() && m_grid[i][col-1] == a_word[i])
                {
                    ++i;
                }
                if (i == a_word.length())
                {
                    updateWordsTable(a_word);
                }     
            }
            //check up
            i = 0;
            if(i > 0)
            {
                while (i < a_word.length() && m_grid[i-1][col] == a_word[i])
                {
                    ++i;
                }
                if (i == a_word.length())
                {
                    updateWordsTable(a_word);
                }
            }
    

            //check down
            i = 0;
            if(i < m_grid.size())
            {
                while (i < a_word.length() && m_grid[i+1][col] == a_word[i])
                {
                    ++i;
                }
                if (i == a_word.length())
                {
                    updateWordsTable(a_word);
                }
            }

            //check up and right
            i = 0;
            if(i > 0 && col < m_grid.size())
            {
                while (i < a_word.length() && m_grid[i-1][col+1] == a_word[i])
                {
                    ++i;
                }
                if (i == a_word.length())
                {
                    updateWordsTable(a_word);
                }
            }
            //check up and left
            i = 0;
            if(i > 0 && col > 0)
            {
                while (i < a_word.length() && m_grid[i-1][col-1] == a_word[i])
                {
                    ++i;
                }
                if (i == a_word.length())
                {
                    updateWordsTable(a_word);
                }
            }
            
            //check down and right
            i = 0;
            if(i < m_grid.size() && col < m_grid.size())
            {
                while (i < a_word.length() && m_grid[i+1][col+1] == a_word[i])
                {
                    ++i;
                }
                if (i == a_word.length())
                {
                    updateWordsTable(a_word);
                }
            }

            //check up and left
            i = 0;
            if(i < m_grid.size() && col > 0)
            {
                while (i < a_word.length() && m_grid[i+1][col-1] == a_word[i])
                {
                    ++i;
                }
                if (i == a_word.length())
                {
                    updateWordsTable(a_word);
                }
            }
            it++;
            nextChar++;
            std::cout <<  "it: " <<*it << std::endl;
        }
        ++row;
    }
}

void Grid::updateWordsTable(std::string const& a_word)
{
    ++m_wordsFrequency[a_word];
}

// void Grid::initializeGrid(std::ifstream& a_cwPuzzle)
// {
//     std::string line;
//     char byte = 0;

//     for(auto row : m_matrix)
//     {
//        while(getline(a_cwPuzzle, line))
//         {
//             for(auto const& col : line)
//             {
//                 m_matrix[row][col] = 
//             }
//         }
        
//         {
//             a_cwPuzzle >> byte;
//             a_cwPuzzle >> m_matrix
//         }
//     }
// }

void Grid::printWordsFrequency()
{
    for (auto const& pair : m_wordsFrequency)
    {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}
 
}//namespace iq


