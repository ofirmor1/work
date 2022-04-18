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
    explicit Grid(std::string const& a_path = "puzzle.txt");

    void initializeGrid(std::ifstream& a_cwPuzzle);

    void searchWord(std::string const& a_word);

    void loadGrid(std::string const& a_path);

    void updateWordsTable(std::string const& a_word);

    void printWordsFrequency();

private:
    std::vector<std::vector<char>> m_grid;
    std::unordered_map<std::string, unsigned int> m_wordsFrequency;
};

// std::string getDirections(std::ifstream a_source);

// std::ifstream set;

}//namespace iq

/*algorithm:
1. keep search for the first char in word[i].
2. when found one, search for the next char in word in all directions recieved from file "directions"
3. if word found, keep the result in map, and search for next word. otherwise, keep searching for next match.
map - key is a direction, value is pair of word and frequeny.
*/