#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

namespace iq
{
class Grid
{
public:
    Grid(std::string const& a_wordsFilePath, std::string const& a_gridpFileath, std::string const& a_directions);

    void searchDirections(std::string const& a_directions);

    void initializeGrid(std::ifstream& a_cwPuzzle);

    void buildDirectionMap();

    void searchWord(std::string const& a_word);

    void loadGrid(std::string const& a_path);

    void loadWords(std::string const& a_wordsFile);

    void updateWordsTable(std::string const& a_word);

    void printWordsFrequency();

private:
    std::vector<std::vector<char>> m_matrix;
    std::vector<std::string> m_wordsVec;
    int m_rows;
    int m_columns;
    std::unordered_map<std::string, int> m_wordsFrequency;
    std::vector<std::pair<int, int>> m_directVec;
    std::unordered_map<char, std::pair<int, int>> m_directMap;
};

}//namespace iq

/*algorithm:
1. keep search for the first char in word[i].
2. when found one, search for the next char in word in all directions recieved from file "directions"
3. if word found, keep the result in map, and search for next word. otherwise, keep searching for next match.
map - key is a direction, value is pair of word and frequeny.
*/