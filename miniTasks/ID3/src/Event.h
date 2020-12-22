#pragma once
const int NAME_LENGTH = 32;
const int ATTRIBUTES_SIZE = 9;
const int ATTRIBUTE_NAME_LENGTH = 16;

struct Event {
	char name[NAME_LENGTH];
	char attributes[ATTRIBUTES_SIZE][ATTRIBUTE_NAME_LENGTH];
};