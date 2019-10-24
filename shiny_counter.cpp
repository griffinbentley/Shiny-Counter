#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include <ctgmath>


void intro()
{
    std::cout << "WELCOME TO THE SHC!" << std::endl;
    std::cout << "To start a new hunt, press enter and then enter the "
                 "name of the pokemon you're hunting." << std::endl;
    std::cout << "To continue a hunt, enter the name of the pokemon that"
                 " you were hunting." << std::endl;
    std::cout << "To end the program, type exit at any point." << std::endl;
}


//Creates a new file with user provided information.
std::string newFile()
{
    std::string file;
    std::fstream myfile;
    std::cout << "What pokemon are you hunting? ";
    getline(std::cin, file);
    if(file == "exit")
    {
        return "exit";
    }
    file += ".txt";
    myfile.open(file, std::fstream::out);

    // asks user for the generation and method they're using
    std::string gen;
    std::string method;
    std::string shiny_charm;
    while(gen != "2" && gen != "3" && gen != "4" && gen != "5"
            && gen != "6" && gen != "7")
    {
        std::cout << "What generation are you hunting in? ";
        getline(std::cin, gen);
        if(gen == "exit")
        {
            return "exit";
        }
        else if(gen == "1")
        {
            std::cout << "Liar!" << std::endl;
        }
        else if(gen == "2")
        {
            while(method != "normal" && method != "breeding")
            {
                std::cout << "Normal or breeding? ";
                getline(std::cin, method);
            }
        }
        else if(gen == "4")
        {
            while(method != "normal" && method != "masuda" &&
                  method != "poke radar")
            {
                std::cout << "Normal, masuda, or poke radar? ";
                getline(std::cin, method);
            }
        }
        else if(gen == "5")
        {
            while(method != "normal" && method != "masuda")
            {
                std::cout << "Normal or masuda? ";
                getline(std::cin, method);
                if(method == "exit")
                {
                    return "exit";
                }
            }
            while(shiny_charm != "y" && shiny_charm != "n")
            {
                std::cout << "Shiny charm? (y/n) ";
                getline(std::cin, shiny_charm);
            }
        }
        else if(gen == "6")
        {
            while(method != "normal" && method != "masuda" &&
                  method != "friend safari" && method != "fishing" &&
                  method != "hidden pokemon")
            {
                std::cout << "Normal, masuda, friend safari, fishing, "
                             "or hidden pokemon? ";
                getline(std::cin, method);
                if(method == "exit")
                {
                    return "exit";
                }
            }
            while(shiny_charm != "y" && shiny_charm != "n")
            {
                std::cout << "Shiny charm? (y/n) ";
                getline(std::cin, shiny_charm);
            }
        }
        else if(gen == "7")
        {
            while(method != "normal" && method != "sos battles")
            {
                std::cout << "Normal or sos battles? ";
                getline(std::cin, method);
                if(method == "exit")
                {
                    return "exit";
                }
            }
            while(shiny_charm != "y" && shiny_charm != "n")
            {
                std::cout << "Shiny charm? (y/n) ";
                getline(std::cin, shiny_charm);
            }
        }
        if(shiny_charm == "exit" | method == "exit")
        {
            return "exit";
        }
    }


    //Writes in initial count of 0, generation, method, shiny charm
    // value, and start time.
    time_t now = time(nullptr);
    myfile << "0" << std::endl << gen << std::endl << method
           << std::endl << shiny_charm << std::endl
           << std::ctime(&now);
    myfile.close();
    return file;
}


//Takes the generation, string, shiny charm use, and count
// and returns the probability of a shiny pokemon on the
// next try.
double calcProb(const std::string& gen, const std::string& method,
                const bool& shiny_charm, const int& count)
{
    double probability;

    if(method == "normal")
    {
        if(gen == "2" | gen == "3" | gen =="4" | gen == "5")
        {
            probability = (shiny_charm ? 0.00036621093 : 0.00012207031);
        }
        else if(gen == "6" | gen == "7")
        {
            probability = 0.00024414062;
        }
    }
    else if(method == "breeding")
    {
        probability = 0.015625;
    }
    else if(method == )
    return (count + 1) * probability * pow(1 - probability,
            double(count));
}


void closeFile(std::string file, const int& count, const std::string& gen,
        const std::string& method, const std::string& shiny_charm,
        const std::string& start_date, const std::string& found_time)
{
    std::ofstream ofile(file);
    ofile << std::to_string(count - 1) << std::endl << gen << std::endl
         << method << std::endl << shiny_charm << std::endl << start_date
         << std::endl << found_time;
    ofile.close();
}


int main()
{
    intro();
    // moves into directory where hunt files are stored
    chdir("Hunts");
    // asks user for file to start hunting with
    std::cout << "Select a pokemon to begin with or press "
                 "enter to create a new hunt: ";
    std::string file;
    getline(std::cin, file);

    if(file == "exit")
        return 0;

    //Initializes count, gen, method, shiny_charm,
    // and start_date as global variables.
    std::string count;
    std::string gen;
    std::string method;
    std::string shiny_charm;
    std::string start_date;

    //If user input is empty then it asks for a name and
    // creates a file with that name and closes the file.
    if(file.empty())
    {
        file = newFile();
        if(file == "exit")
            return 0;
    }
    else
        file += ".txt";
    //Try to open the given file and if the file doesn't exist,
    // ask for file name again and try again.
    std::fstream myfile;
    myfile.open(file);
    while(!myfile.is_open())
    {
        std::cout << "Couldn't find that file. Please try again: ";
        getline(std::cin, file);
        if(file == "exit")
            return 0;
        file += ".txt";
        myfile.open(file);
    }
    getline(myfile, count);
    getline(myfile, gen);
    getline(myfile, method);
    getline(myfile, shiny_charm);
    getline(myfile, start_date);
    //turns count from given file into an integer
    int icount = stoi(count);
    bool sc = shiny_charm == "y";
    std::string string;
    std::cout << "Press enter to add a count, exit to quit program, "
                 "or shiny when you get a shiny." << std::endl;


    // loops and increases count
    // able to end the program entirely by typing "exit"
    // able to end hunt and start another one by typing "end" or "shiny"
    while(string != "exit" && string != "shiny" && string != "end")
    {
        std::cout << "Tries: " << std::to_string(icount) << std::endl;
        std::cout << "Probability: " << calcProb(gen, method,
                sc, icount);
        getline(std::cin, string);
        icount++;
    }


    // writes new count to the file
    if(string == "exit")
    {
        closeFile(file, icount, gen, method, shiny_charm, start_date, "");
        myfile.close();
    }

    // asks user if they want to delete the file since the hunt is over
    else if(string == "shiny")
    {
        std::cout << "CONGRATULATIONS!!!" << std::endl << "Would you like "
                     "to delete "<< file << "? (y/n) " << std::endl;
        std::string del;
        getline(std::cin, del);
        // deletes the file if the user inputs "y"
        if(del == "y")
        {
            remove("Absol.txt");
            std::cout << "File deleted." << std::endl;
            myfile.close();
        }
        // keeps the file and adds new count and found date to the file
        else
        {
            std::cout << "File kept." << std::endl;
            time_t now = time(nullptr);
            closeFile(file, icount, gen, method, shiny_charm, start_date,
                      std::ctime(&now));
            myfile.close();
        }
        main();
    }

    // ends the hunt and calls main again to allow user to pick a new hunt
    else if(string == "end")
    {
        closeFile(file, icount, gen, method, shiny_charm, start_date, "");
        myfile.close();
        main();
    }

    // moves path back to original directory
    chdir("..");
    return 0;
}