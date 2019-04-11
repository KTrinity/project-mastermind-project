#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <time.h>
#include <vector>

std::vector<std::string> codeGen(std::vector<std::string> colours)
{
    std::vector<std::string> codePegs;
    for (int i = 0; i < colours.size(); i++)
    {
        for (int j = 0; j < 4; j++)
        {
            codePegs.push_back(colours[i]);
        }
    }
    std::srand(time(NULL));
    std::random_shuffle(codePegs.begin(), codePegs.end());
    std::vector<std::string> randomPegs (codePegs.begin(), codePegs.begin()+4);

    // prints the codePegs for debugging, just add/remove /* in the line below to toggle comments
    /*std::cout << "randomPegs: ";
    for (int r = 0; r < 4; r++)
    {
        std::cout << randomPegs[r];
        if (r != 3)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    //*/

    return randomPegs;
}

int correctLoc(std::vector<std::string> guessPegs, std::vector<std::string> codePegs)
{
    int correct = 0;
    for (int i = 0; i < 4; i++)
    {
        if (guessPegs[i] == codePegs[i])
        {
            correct++;
        }
    }
    return correct;
}

int matching(std::vector<std::string> guessPegs, std::vector<std::string> codePegs)
{
    int codeCount, guessCount;
    int matches = 0;
    std::vector<std::string> uniqueCPs;

    for (int i = 0; i < codePegs.size(); i++)
    {
        if (std::find(uniqueCPs.begin(), uniqueCPs.end(), codePegs[i]) == uniqueCPs.end())
        {
            uniqueCPs.push_back(codePegs[i]);
        }
    }
    for (int u = 0; u < uniqueCPs.size(); u++)
    {
        guessCount = std::count(guessPegs.begin(), guessPegs.end(), uniqueCPs[u]);
        codeCount = std::count(codePegs.begin(), codePegs.end(), uniqueCPs[u]);
        matches += std::min(guessCount, codeCount);
    }
    return matches;
}

std::string getUserPeg(int pegNo)
{
    std::string peg;
    std::string numberEnd;

    if (pegNo == 1)
    {
        numberEnd = "st";
    }
    else if (pegNo == 2)
    {
        numberEnd = "nd";
    }
    else if (pegNo == 3)
    {
        numberEnd = "rd";
    }
    else
    {
        numberEnd = "th";
    }

    std::cout << "Enter the choice for the " << pegNo << numberEnd << " peg: ";
    std::cin >> peg;

    if (std::tolower(peg[0]) == "red"[0])
    {
        return "Red";
    }
    else if (std::tolower(peg[0]) == "blue"[0])
    {
        return "Blue";
    }
    else if (std::tolower(peg[0]) == "green"[0])
    {
        return "Green";
    }
    else if (std::tolower(peg[0]) == "orange"[0])
    {
        return "Orange";
    }
    else if (std::tolower(peg[0]) == "yellow"[0])
    {
        return "Yellow";
    }
    else if (std::tolower(peg[0]) == "pink"[0])
    {
        return "Pink";
    }
    else
    {
        std::cout << "That is not a valid option" << std::endl;
    }
}

int main()
{
    std::string colourLst[] = {"Red","Blue","Green","Orange","Yellow","Pink"};
    std::vector<std::string> colours (colourLst, colourLst + sizeof(colourLst)/24);
    std::vector<std::string> masterPegs, playerPegs;
    masterPegs = codeGen(colours);
    bool playing = true;
    int rounds = 0;

    while (playing)
    {
        // clears the playerpegs otherwise the vector just keeps getting longer
        playerPegs.clear();

        std::cout << "Available options are: Red, Blue, Green, Orange, Yellow, Pink" << std::endl;
        for (int p = 1; p < 5; p++)
        {
            playerPegs.push_back(getUserPeg(p));
        }

        int match = matching(playerPegs, masterPegs);
        int correct = correctLoc(playerPegs, masterPegs);

        std::cout << "Matching Pegs: " << match << std::endl;
        std::cout << "Correct Pegs: " << correct << std::endl << std::endl;

        rounds++;

        if (correct == 4)
        {
            std::string repeat;
            std::cout << "That is the correct sequence, you solved the code in " << rounds << " attempts" << std::endl;
            std::cout << "Play Again (Y/n): ";
            std::cin >> repeat;
            if (repeat == "" || std::tolower(repeat[0]) == "yes"[0])
            {
                masterPegs.clear();
                masterPegs = codeGen(colours);
                rounds = 0;
            } else {
                playing = false;
            }
        }
    }
    return 0;
}
