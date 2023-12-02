#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

int p1(std::string);
int p2(std::string);
int get_text_nums_from_line(std::string);
int get_num_from_line(std::string);

int main()
{
    int res_1 = p1("1/input.txt");
    int res_2 = p2("1/input.txt");

    if(res_1 == -1 || res_2 == -1)
        return -1;

    std::cout << "Part 1: " << res_1 << std::endl;
    std::cout << "Part 2: " << res_2 << std::endl;
    return 0;
}

int p1(std::string filename)
{
    int res = 0;
    std::string line;
    std::ifstream myfile(filename);

    int i = 0;
    if(myfile.is_open())
    {
        while(getline(myfile, line))
        {
            res += get_num_from_line(line);
        }

        myfile.close();
    } else {
        return -1;
    }

    return res;
}

int p2(std::string filename)
{
    int res = 0;
    std::string line;
    std::ifstream myfile(filename);

    if(myfile.is_open())
    {
        while(getline(myfile, line))
            res += get_text_nums_from_line(line);

        myfile.close();
    } else {
        return -1;
    }

    return res;
}

int get_text_nums_from_line(std::string line)
{
    std::map<std::string, std::string> mp;

    const char* nums[] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::vector<std::string> text_nums (nums, nums+9);

    int i;
    int n = text_nums.size();
    for(i = 0; i < n; i++)
        mp[text_nums[i]] = std::to_string(i + 1);

    // find substrings
    std::string first, last;
    int x, y, z;
    n = line.length();

    // FORWARDS
    for(x = 0; x < n; x++)
    {
        if(isdigit(line[x]))
        {
            first = line[x];
            break;
        }
        std::string temp;
        for(y = x; y < n; y++)
        {
            for(z = y; z < n; z++)
            {
                temp += line[z];

                if(temp.length() > 6)
                    break;

                // checking if temp in map
                std::map<std::string, std::string>::iterator t_mp = mp.find(temp);
                if(t_mp != mp.end())
                {
                    first = t_mp->second;
                    x = n;
                    y = n;
                    break;
                }
            }
        }
    }

    // BACKWARDS
    for(x = n-1; x >= 0; x--)
    {
        if(isdigit(line[x]))
        {
            last = line[x];
            break;
        }
        std::string temp;
        for(y = x; y >= 0; y--)
        {
            for(z = y; z >= 0; z--)
            {
                temp += line[z];

                if(temp.length() > 6)
                    break;
                // checking if temp in map

                // reversing
                std::string rev;
                int r;
                for(r = temp.length()-1; r >= 0; r--)
                    rev.push_back(temp[r]);

                std::map<std::string, std::string>::iterator t_mp = mp.find(rev);
                if(t_mp != mp.end())
                {
                    last = t_mp->second;
                    x = -1;
                    y = -1;
                    break;
                }
            }
        }
    }

    std::string res = first;
    res += last;

    return std::stoi(res);
}

int get_num_from_line(std::string line)
{
    char first, last;

    int n = line.size();
    int i;
    for(i = 0; i < n; i++)
    {
        if(isdigit(line[i]))
        {
            first = line[i];
            break;
        }
    }

    for(i = n-1; i >=0; i--)
    {
        if(isdigit(line[i]))
        {
            last = line[i];
            break;
        }
    }

    char arr[] = {first, last};
    return std::stoi(arr);
}


