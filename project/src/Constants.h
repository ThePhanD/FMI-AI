#pragma once
#include <string>
#include "ShipType.h"

const std::string INCORRECT_BOARD = "The board can't be null!";
const std::string INIT_DEFAULT_BOARD = "The board couldn't be copied.\nA default board was created.";

const int ZERO = 0;
const int TEN = 10;

const std::string FIELD_INTERRUPTION = "The chosen field is interrupted!";
const std::string FIELD_ALREADY_DESTROYED = "The chosen field is already destroyed, choose another one!";
const std::string INCORRECT_SHIP_FIELD = "The chosen field isn't correct size for the ship!";
const std::string INCORRECT_COORDINATES = "The coordinates must be between row A to J and between col 1 to 10!";
const std::string INVALID_COMMAND = "INVALID COMMAND";

const char EMPTY_FIELD = '-';
const char SHIP_FIELD = '*';
const char HIT_SHIP_FIELD = 'X';
const char HIT_EMPTY_FIELD = 'O';
const char INCORRECT_FIELD = '#';

const std::string SHIP_UNCHANGEABLE = "The ship can't change his position!";
const std::string SHIP_UNAVAILABLE = "This type of ship can't be placed anymore!";
const std::string SHIP_NOT_EXIST = "This ship doesn't exist!";
const std::string CHANGE_SHIP = "Please choose a different ship!";

const std::string MOVE = "move";
const std::string PLACE = "place";
const std::string ATTACK = "attack";

const int PLACE_ARG_COUNT = 4;
const int MOVE_ARG_COUNT = 4;
const int ATTACK_ARG_COUNT = 2;
const int ACTION_NAME = 0;

const std::string LAST_TURN = "Opponent last turn: ";

const char START_POSITION = 'A';
const int ROW = 0;
const int COL = 1;
const int LOW_PROBABILITY = 1;
const int HIGH_PROBABILITY = 50;

const int NO_HEALTH = 0;
const int SUBMARINE_SIZE = 2;
const int DESTROYER_SIZE = 3;
const int CRUISER_SIZE = 4;
const int CARRIER_SIZE = 5;

const std::string SUBMARINE_STR = "SUBMARINE";
const std::string DESTROYER_STR = "DESTROYER";
const std::string CRUISER_STR = "CRUISER";
const std::string CARRIER_STR = "CARRIER";

const ShipType SUBMARINE = ShipType::SUBMARINE;
const ShipType DESTROYER = ShipType::DESTROYER;
const ShipType CRUISER = ShipType::CRUISER;
const ShipType CARRIER = ShipType::CARRIER;
