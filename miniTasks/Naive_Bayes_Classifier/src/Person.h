#pragma once
const int NAME_LENGTH = 16;
const int ATTRIBUTES_SIZE = 16;

struct Person {
	char name[NAME_LENGTH];
	char attributes[ATTRIBUTES_SIZE];
};