#include <iostream>
#include <string>
#include <vector>
#include <ctime>
struct catagories;
struct player;
std::string setPlayerName(int i);
struct player
{
    std::string playerName;
    std::vector<int> dices = {};
};
struct catagories
{
    int one, two, three, four, five, six;
    int pair, twoPair, threeOfKind, fourOfKind;
    int smallLadder, bigLadder, fullHouse, chance, yatzy;
};
int rolldice()
{
    return 1 + rand() % 6;
}
std::vector<player> createPlayers()
{
    std::vector<player> players;
    player player;
    int playerCount;
    std::cout << "Write how many players that will be playing" << std::endl;
    std::cin >> playerCount;
    for (int i = 0; i < playerCount; i++)
    {
        player.playerName = setPlayerName(i);
        players.push_back(player);
    }
    return players;
}
std::string setPlayerName(int i)
{
    std::string playerName;
    std::cout << "Write player" << i << " name: ";
    std::cin >> playerName;
    return playerName;
}

void rules()
{
    std::cout << "Yatzy Rules " << std::endl
              << "Game Setup:" << std::endl
              << "Yatzy is played with 5 dice." << std::endl
              << "Players take turns rolling the dice, trying to achieve specific combinations for points." << std::endl
              << "Scoring Combinations :" << std::endl
              << "Ones : Sum of all dice showing the number" << std::endl
              << " 1. Twos : Sum of all dice showing the number 2. Threes : Sum of all dice showing the number 3. Fours : Sum of all dice showing the number 4. Fives : Sum of all dice showing the number 5. Sixes : Sum of all dice showing the number 6. One Pair : Two dice showing the same number.Score the sum of the pair.Two Pairs : Two different pairs.Score the sum of all four dice.Three of a Kind : Three dice showing the same number.Score the sum of those three.Four of a Kind : Four dice showing the same number.Score the sum of those four.Full House : Three of one number and" << std::endl
              << "two of another.Score 25 points.Small Straight : A sequence of" << std::endl
              << "four(e.g., 1 - 2 - 3 - 4)" << std::endl
              << ".Score 30 points.Large Straight : A sequence of" << std::endl
              << "five(e.g., 1 - 2 - 3 - 4 - 5)" << std::endl
              << ".Score 40 points.Yatzy : All five dice showing the same number.Score 50 points.Chance : Sum of all dice.(No specific combination required)" << std::endl
              << ".Gameplay :" << std::endl
              << "Each player gets three rolls per turn.After each roll," << std::endl
              << "the player can choose to keep some dice and" << std::endl
              << "re - roll others.After the third roll," << std::endl
              << "the player must choose a scoring category and cannot change it.Ending the Game :" << std::endl
              << "The game ends when all scoring categories have been filled.The player with the highest total score wins ";
}
std::vector<int> reRollDice(std::vector<int> dice)
{
    std::vector<bool> keep(dice.size(), false);
    char input;

    std::cout << "Which dice would you like to keep? (Enter indices, e.g., 0 2 for dice 1 and 3): ";
    for (size_t i = 0; i < dice.size(); ++i)
    {
        std::cout << i << ": " << dice[i] << "  ";
    }
    std::cout << std::endl;

    while (std::cin >> input)
    {
        if (input == 'q')
            break;               // Quit if user types 'q'
        int index = input - '0'; // Convert char to int
        if (index >= 0 && index < dice.size())
        {
            keep[index] = true; // Mark dice to keep
        }
    }

    // Re-roll the dice that are not marked to keep
    for (size_t i = 0; i < dice.size(); ++i)
    {
        if (!keep[i])
        {
            dice[i] = rolldice(); // Re-roll
        }
    }
    return dice;
}
void displayDice(std::vector<int> dice, std::string playerName)
{
    std::cout << playerName << " has these dices: " << std::endl;
    for (int i = 0; i < 5; i++)
    {
        std::cout << "dice " << i << " : " << dice.at(i) << std::endl;
    }
}
bool gameMenu()
{
    int choice;
    do
    {
        std::cout << "Welcome to Yatzy game" << std::endl;
        std::cout << "1. Display Rules" << std::endl;
        std::cout << "2. Start game" << std::endl;
        std::cout << "3. Exit game" << std::endl;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            rules();
            break;
        case 2:
            return true;
            break;
        case 3:
            return false;
            break;
        default:
            std::cout << "Need to be between 1-3!" << std::endl;
            break;
        }
    } while (choice != 3 || choice != 2);
}

int main()
{

    std::vector<player> currentplayers;
    srand(time(0));
    bool isgamestarting = gameMenu();
    if (isgamestarting == true)
    {
        currentplayers = createPlayers();
        while (isgamestarting == true)
        {
            for (player thisplayer : currentplayers)
            {
                std::cout << thisplayer.playerName << "'s turn" << std::endl;
                for (int i = 0; i < 5; i++)
                {
                    thisplayer.dices.push_back(rolldice());
                }
                thisplayer.dices = reRollDice(thisplayer.dices);
                displayDice(thisplayer.dices, thisplayer.playerName);
            }
        }
    }

    std::cout << "Exit game" << std::endl;
    return 0;
}