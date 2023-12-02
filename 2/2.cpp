#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int p1(std::string);
int p2(std::string);
int is_game_valid(std::string);
int game_min_set_power(std::string);
std::vector<std::string> line_split(std::string, std::string);

int main()
{
    int res_1 = p1("2/input.txt");
    int res_2 = p2("2/input.txt");

    std::cout << "RES P1: " << res_1 << std::endl;
    std::cout << "RES P2: " << res_2 << std::endl;

    return 0;
}

int p1(std::string filename)
{
    std::string line;
    std::ifstream myfile(filename);
    int res = 0;

    if(myfile.is_open())
    {
        int id = 1;
        while(getline(myfile, line))
        {
            std::string delimiter = ":";
            line.erase(0, line.find(delimiter) + delimiter.length());
            if(is_game_valid(line))
                res += id;
            id++;
        }

        myfile.close();
    }

    return res;
}

int p2(std::string filename)
{
    std::string line;
    std::ifstream myfile(filename);
    int res = 0;

    if(myfile.is_open())
    {
        while(getline(myfile, line))
        {
            std::string delimiter = ":";
            line.erase(0, line.find(delimiter) + delimiter.length());
            res += game_min_set_power(line);
        }

        myfile.close();
    }

    return res;
}

int is_game_valid(std::string game_line)
{
    // takes input of just the game
    int red_max = 12;
    int green_max = 13;
    int blue_max = 14;

    std::vector<std::string> games = line_split(game_line, ";");

    // get the values from each game
    int i, j;
    for(i = 0; i < games.size(); i++)
    {
        // delimit on ","
        std::vector<std::string> game = line_split(games[i], ",");

        // get the numbers
        for(j = 0; j < game.size(); j++)
        {
            std::vector<std::string> game_info = line_split(game[j], " ");
            std::string word = game_info[2];
            int val = std::stoi(game_info[1]);

            if(word == "red")
                if(val > red_max)
                    return 0;
            if(word == "green")
                if(val > green_max)
                    return 0;
            if(word == "blue")
                if(val > blue_max)
                    return 0;
        }
    }

    return 1;
}

int game_min_set_power(std::string game_line)
{
    int min_red = 0;
    int min_blue = 0;
    int min_green = 0;

    std::vector<std::string> games = line_split(game_line, ";");

    // get the values from each game
    int i, j;
    for(i = 0; i < games.size(); i++)
    {
        // delimit on ","
        std::vector<std::string> game = line_split(games[i], ",");

        // get the numbers
        for(j = 0; j < game.size(); j++)
        {
            std::vector<std::string> game_info = line_split(game[j], " ");
            std::string word = game_info[2];
            int val = std::stoi(game_info[1]);

            if(word == "red")
            {
                if(val > min_red)
                    min_red = val;
            }
            else if(word == "green")
            {
                if(val > min_green)
                    min_green = val;
            }
            else // word is blue
            {
                if(val > min_blue)
                    min_blue = val;
            }
        }
    }

    return (min_red * min_green * min_blue);
}

std::vector<std::string> line_split(std::string line, std::string delimiter)
{
    std::vector<std::string> res;

    int pos = 0;
    std::string token;
    while((pos = line.find(delimiter)) != std::string::npos)
    {
        token = line.substr(0, pos);
        res.push_back(token);
        line.erase(0, pos + delimiter.length());
    }
    // final part of line
    res.push_back(line);

    return res;
}