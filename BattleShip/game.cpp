#include "game.h"

Game::Game()
{
    server = new Player();
    client = new Player();
}

Game::~Game()
{

}
