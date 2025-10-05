#ifndef UNO_H
#define UNO_H

#include <string>
#include <vector>


class UNOGame {
public:
    virtual ~UNOGame() = default;  // Virtual destructor

    // Initialize game with given number of players
    UNOGame(int numPlayers);

    // Shuffle and deal cards to players
    virtual void initialize() = 0;

    // Play one turn of the game
    virtual void playTurn() = 0;

    // Return true if game has a winner
    virtual bool isGameOver() const = 0;

    // Return index of winner
    virtual int getWinner() const = 0;

    // Return current state as string
    virtual std::string getState() const = 0;
};

#endif