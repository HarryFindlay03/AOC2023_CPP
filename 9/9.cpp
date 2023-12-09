#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int p1(std::string filename);

typedef std::vector<std::vector<int> > oasis_t;

int main()
{
    int res_1 = p1("9/input.txt");

    std::cout << "RES 1: " << res_1 << std::endl;
    return 0;
}

int p1(std::string filename)
{
    std::string line;
    std::ifstream myfile(filename);

    oasis_t my_input;

    std::string token;
    std::string delimiter = " ";
    int pos = 0;

    // GET INPUT IN CORRECT FORMAT
    if(myfile.is_open())
    {
        while(getline(myfile, line))
        {
            std::vector<int> line_nums;
            // delimit on space
            while((pos = line.find(delimiter)) != std::string::npos)
            {
                token = line.substr(0, pos);
                line_nums.push_back(std::stoi(token));
                line.erase(0, pos+delimiter.length());
            }
            line_nums.push_back(std::stoi(line));
            my_input.push_back(line_nums);
        }
        myfile.close();
    }

    // FOR EACH LINE
    int res = 0;
    oasis_t::iterator it;
    for(it = my_input.begin(); it != my_input.end(); ++it)
    {
        // difference array
        oasis_t difference_vectors;
        int break_test = 0;
        difference_vectors.push_back(*it);
        
        while(!break_test)
        {
            std::vector<int> curr_line = difference_vectors.back();
            std::vector<int> difference;

            std::vector<int>::iterator curr_line_it;
            for (curr_line_it = curr_line.begin() + 1; curr_line_it != curr_line.end(); ++curr_line_it)
            {
                difference.push_back(*curr_line_it - *(curr_line_it - 1));
            }
            difference_vectors.push_back(difference);

            // testing for all zeros
            break_test = 1;
            for(curr_line_it=difference.begin(); curr_line_it != difference.end(); ++curr_line_it)
            {
                if(*curr_line_it != 0)
                    break_test = 0;                   
            }
        }

        // extraction
        oasis_t::iterator diff_it;
        for(diff_it = difference_vectors.end()-2; diff_it != difference_vectors.begin()-1; --diff_it)
            (diff_it)->push_back((diff_it+1)->back() + (diff_it)->back());

        res += difference_vectors[0].back();
    }

    return res;
}