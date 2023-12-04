#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int p1(std::string);
int check_square_position(const std::vector<std::string>&, int, int);
int is_symbol(char);

int main()
{
    int res_1 = p1("3/input.txt");

    std::cout << "RES 1: " << res_1 << std::endl;
    return 0;
}

int p1(std::string filename)
{
    int res = 0;
    std::vector<std::string> lines;

    std::string line;
    std::ifstream myfile(filename);

    if(myfile.is_open())
        while(getline(myfile, line))
            lines.push_back(line);

    std::vector<std::string>::iterator it;
    for(it = lines.begin(); it != lines.end(); ++it)
    {
        // line in iterator
        std::string curr_line = *it;
        std::string::iterator line_itr;
        for(line_itr = curr_line.begin(); line_itr != curr_line.end(); ++line_itr)
        {
            if(!(isdigit(*line_itr))) continue;

            // if it is a digit look at the square positions around it
            int curr_row_pos = it - lines.begin();
            int curr_col_pos = line_itr - curr_line.begin();

            if(check_square_position(lines, curr_row_pos, curr_col_pos))
            {
                // get the start of the number - go backwards from number until char is not digit
                std::string::iterator r = line_itr;
                while (isdigit(*r))
                    r--;
                r++;

                std::string temp_num;
                while (isdigit(*r))
                {
                    temp_num.push_back(*r);
                    r++;
                }
                line_itr = --r;
                res += std::stoi(temp_num);
            }
        }
    }

    return res;
}

int check_square_position(const std::vector<std::string> & lines, int row_pos, int col_pos)
{
    int i, j;
    for(i = -1; i <= 1; i++)
    {
        if(row_pos + i < 0)
            i++;
        if(row_pos + i == lines.size())
            break;
        for(j = -1; j <= 1; j++)
        {
            if(col_pos + j < 0)
                j++;
            if(col_pos + j == lines[i].size())
                break;
            if(is_symbol(lines[row_pos + i][col_pos + j]))
                return 1;
        }
    }

    return 0;
}

int is_symbol(char ch)
{
    if(ch != '.' && !(isdigit(ch)))
        return 1;
    return 0;
}