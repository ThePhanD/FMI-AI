#pragma once
#include <vector>
#include <utility>
#include "Event.h"

const int ATTRIBUTES_LENGTH[9] = { 9, 3, 12, 13, 2, 3, 2, 5, 2 };

struct Node
{
	char *data;
	std::vector<std::pair<const char*, std::vector<Event>>> eventsSet;
	std::vector<Node*> children;

	Node() {
		data = nullptr;
	}

	Node(const char *data) {
		this->data = new char[strlen(data) + 1];
		strcpy(this->data, data);
	}
};


