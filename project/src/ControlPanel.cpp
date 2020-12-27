#include "ControlPanel.h"

void ControlPanel::getTokens(std::vector<std::string> &tokens, std::string input) {
	/*std::string delimiter = " ";

	size_t pos = 0;
	std::string token;
	while ((pos = input.find(delimiter)) != std::string::npos) {
		token = input.substr(0, pos);
		tokens.push_back(token);
		input.erase(0, pos + delimiter.length());
	}*/

	std::istringstream iss(input);
	tokens = std::vector<std::string>(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());

}

bool iequals(const std::string &a, const std::string &b) {
	return std::equal(a.begin(), a.end(), b.begin(),
		[](char a, char b) {
		return tolower(a) == tolower(b);
	});
}

bool ControlPanel::isPlaceShipAction(std::string action) {
	std::vector<std::string> tokens;
	getTokens(tokens, action);
	return iequals(tokens[ACTION_NAME], PLACE) && tokens.size() == PLACE_ARG_COUNT;
}

bool ControlPanel::isMoveShipAction(std::string action) {
	std::vector<std::string> tokens;
	getTokens(tokens, action);
	return iequals(tokens[ACTION_NAME], MOVE) && tokens.size() == MOVE_ARG_COUNT;
}

bool ControlPanel::isAttackAction(std::string action) {
	std::vector<std::string> tokens;
	getTokens(tokens, action);
	return iequals(tokens[ACTION_NAME], ATTACK) && tokens.size() == ATTACK_ARG_COUNT;
}

bool ControlPanel::placeShip(BoardHub *boardHub, Ship *ship, std::string startPosition, std::string endPosition) {
	return boardHub->placeShip(ship, startPosition, endPosition);
}

bool ControlPanel::moveShip(BoardHub *boardHub, std::string shipPosition, std::string newStartPosition, std::string newEndPosition) {
	return boardHub->changeShipPosition(shipPosition, newStartPosition, newEndPosition);
}

bool ControlPanel::attack(BoardHub *boardHub, std::string position) {
	return boardHub->attack(position);
}