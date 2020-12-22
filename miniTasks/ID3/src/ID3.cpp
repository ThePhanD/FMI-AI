#include "ID3.h"

int ID3::numberOfEvent(const char *name, std::vector<Event> setsOfEvent) {
	int counter = 0;
	for (Event e : setsOfEvent) {
		if (!strcmp(e.name, name))
			counter++;
	}
	return counter;
}

void ID3::initPredictorsTypes() {
	// Age
	predictorsTypes[0].push_back("10-19");
	predictorsTypes[0].push_back("20-29");
	predictorsTypes[0].push_back("30-39");
	predictorsTypes[0].push_back("40-49");
	predictorsTypes[0].push_back("50-59");
	predictorsTypes[0].push_back("60-69");
	predictorsTypes[0].push_back("70-79");
	predictorsTypes[0].push_back("80-89");
	predictorsTypes[0].push_back("90-99");

	answerToInt.insert(std::make_pair("10-19", 0));
	answerToInt.insert(std::make_pair("20-29", 1));
	answerToInt.insert(std::make_pair("30-39", 2));
	answerToInt.insert(std::make_pair("40-49", 3));
	answerToInt.insert(std::make_pair("50-59", 4));
	answerToInt.insert(std::make_pair("60-69", 5));
	answerToInt.insert(std::make_pair("70-79", 6));
	answerToInt.insert(std::make_pair("80-89", 7));
	answerToInt.insert(std::make_pair("90-99", 8));

	//Menopause
	predictorsTypes[1].push_back("lt40");
	predictorsTypes[1].push_back("ge40");
	predictorsTypes[1].push_back("premeno");

	answerToInt.insert(std::make_pair("lt40", 0));
	answerToInt.insert(std::make_pair("ge40", 1));
	answerToInt.insert(std::make_pair("premeno", 2));

	//Tumor-size
	predictorsTypes[2].push_back("0-4");
	predictorsTypes[2].push_back("5-9");
	predictorsTypes[2].push_back("10-14");
	predictorsTypes[2].push_back("15-19");
	predictorsTypes[2].push_back("20-24");
	predictorsTypes[2].push_back("25-29");
	predictorsTypes[2].push_back("30-34");
	predictorsTypes[2].push_back("35-39");
	predictorsTypes[2].push_back("40-44");
	predictorsTypes[2].push_back("45-49");
	predictorsTypes[2].push_back("50-54");
	predictorsTypes[2].push_back("55-59");

	answerToInt.insert(std::make_pair("0-4", 0));
	answerToInt.insert(std::make_pair("5-9", 1));
	answerToInt.insert(std::make_pair("10-14", 2));
	answerToInt.insert(std::make_pair("15-19", 3));
	answerToInt.insert(std::make_pair("20-24", 4));
	answerToInt.insert(std::make_pair("25-29", 5));
	answerToInt.insert(std::make_pair("30-34", 6));
	answerToInt.insert(std::make_pair("35-39", 7));
	answerToInt.insert(std::make_pair("40-44", 8));
	answerToInt.insert(std::make_pair("45-49", 9));
	answerToInt.insert(std::make_pair("50-54", 10));
	answerToInt.insert(std::make_pair("55-59", 11));

	//Inv-nodes
	predictorsTypes[3].push_back("0-2");
	predictorsTypes[3].push_back("3-5");
	predictorsTypes[3].push_back("6-8");
	predictorsTypes[3].push_back("9-11");
	predictorsTypes[3].push_back("12-14");
	predictorsTypes[3].push_back("15-17");
	predictorsTypes[3].push_back("18-20");
	predictorsTypes[3].push_back("21-23");
	predictorsTypes[3].push_back("24-26");
	predictorsTypes[3].push_back("27-29");
	predictorsTypes[3].push_back("30-32");
	predictorsTypes[3].push_back("33-35");
	predictorsTypes[3].push_back("36-39");

	answerToInt.insert(std::make_pair("0-2", 0));
	answerToInt.insert(std::make_pair("3-5", 1));
	answerToInt.insert(std::make_pair("6-8", 2));
	answerToInt.insert(std::make_pair("9-11", 3));
	answerToInt.insert(std::make_pair("12-14", 4));
	answerToInt.insert(std::make_pair("15-17", 5));
	answerToInt.insert(std::make_pair("18-20", 6));
	answerToInt.insert(std::make_pair("21-23", 7));
	answerToInt.insert(std::make_pair("24-26", 8));
	answerToInt.insert(std::make_pair("27-29", 9));
	answerToInt.insert(std::make_pair("30-32", 10));
	answerToInt.insert(std::make_pair("33-35", 11));
	answerToInt.insert(std::make_pair("36-39", 12));

	//Node-caps
	predictorsTypes[4].push_back("yes");
	predictorsTypes[4].push_back("no");

	answerToInt.insert(std::make_pair("yes", 0));
	answerToInt.insert(std::make_pair("no", 1));

	//Deg-malig
	predictorsTypes[5].push_back("1");
	predictorsTypes[5].push_back("2");
	predictorsTypes[5].push_back("3");

	answerToInt.insert(std::make_pair("1", 0));
	answerToInt.insert(std::make_pair("2", 1));
	answerToInt.insert(std::make_pair("3", 2));

	//Breast
	predictorsTypes[6].push_back("left");
	predictorsTypes[6].push_back("right");

	answerToInt.insert(std::make_pair("left", 0));
	answerToInt.insert(std::make_pair("right", 1));

	//Breast-quad
	predictorsTypes[7].push_back("left-up");
	predictorsTypes[7].push_back("left-low");
	predictorsTypes[7].push_back("right-up");
	predictorsTypes[7].push_back("right-low");
	predictorsTypes[7].push_back("central");

	answerToInt.insert(std::make_pair("left-up", 0));
	answerToInt.insert(std::make_pair("left-low", 1));
	answerToInt.insert(std::make_pair("right-up", 2));
	answerToInt.insert(std::make_pair("right-low", 3));
	answerToInt.insert(std::make_pair("central", 4));
	//Irradiat
	predictorsTypes[8].push_back("yes");
	predictorsTypes[8].push_back("no");


	//Attributes index
	attributeIndex.insert(std::make_pair("age", 0));
	attributeIndex.insert(std::make_pair("menopause", 1));
	attributeIndex.insert(std::make_pair("tumor-size", 2));
	attributeIndex.insert(std::make_pair("inv-nodes", 3));
	attributeIndex.insert(std::make_pair("node-caps", 4));
	attributeIndex.insert(std::make_pair("deg-malig", 5));
	attributeIndex.insert(std::make_pair("breast", 6));
	attributeIndex.insert(std::make_pair("breast-quad", 7));
	attributeIndex.insert(std::make_pair("irradiat", 8));
}

double ID3::entropyCalc(double a, double b) {
	double c = a + b;
	if (c == a || c == b)
		return 0;

	double p1 = a / c;
	double p2 = b / c;
	double logP1 = log(p1) / log(2);
	double logP2 = log(p2) / log(2);
	return -(p1 * logP1) - (p2 * logP2);
}

ID3::ID3(int k) : k(k) {
	initPredictorsTypes();
}

void deleteNode(Node *node) {
	if (node->children.size() != 0) {
		for (Node *tmp : node->children) {
			deleteNode(tmp);
		}
	}

	delete node->data;
	delete node;
}
ID3::~ID3() {
	deleteNode(root);
}

double ID3::entropyTwoElements(int recAnswers[], int noRecAnswers[], int answersSize, int attrLength) {
	double result = 0;
	for (int i = 0; i < attrLength; ++i) {
		double p = (double)(recAnswers[i] + noRecAnswers[i]) / answersSize;
		double e = entropyCalc(recAnswers[i], noRecAnswers[i]);
		result += p * e;

	}

	return result;
}

double ID3::gain(int recAnswers[], int noRecAnswers[], int answersSize, int attrLength) {
	return entropyTarget - entropyTwoElements(recAnswers, noRecAnswers, answersSize, attrLength);
}

int ID3::getBestAtrrGain(std::vector<Event> learnEventSet, double &maxGain, std::vector<int> attributesIndex) {
	int attrIdx = -1;
	int counter = 0;
	int removeIdx = 0;
	for (int i : attributesIndex) {

		int countRecAnswers[13] = { 0 };
		int countNoRecAnswers[13] = { 0 };
		int answersSize = 0;

		for (Event e : learnEventSet) {
			if (!strcmp(e.name, REC)) {
				countRecAnswers[answerToInt[e.attributes[i]]]++;
				answersSize++;
			}
			else {
				countNoRecAnswers[answerToInt[e.attributes[i]]]++;
				answersSize++;
			}
		}

		double attrGain = gain(countRecAnswers, countNoRecAnswers, answersSize, ATTRIBUTES_LENGTH[i]);
		if (maxGain <= attrGain) {
			maxGain = attrGain;
			attrIdx = i;
			removeIdx = counter;
		}
		counter++;
	}

	attributesIndex.erase(attributesIndex.begin() + removeIdx);

	return attrIdx;
}

void ID3::initEventSets(Node *node, int attrIdx, std::vector<Event> events) {
	for (int i = 0; i < ATTRIBUTES_LENGTH[attrIdx]; ++i) {
		std::vector<Event> set;
		for (Event e : events) {
			if (!strcmp(predictorsTypes[attrIdx][i], e.attributes[attrIdx])) {
				set.push_back(e);
			}
		}
		if (set.size() != 0)
			node->eventsSet.push_back(std::make_pair(predictorsTypes[attrIdx][i], set));
	}
}

void ID3::buildTree(Node* &root, std::vector<Event> learnEventSet, std::vector<int> attributesIndex) {

	int recCounter = numberOfEvent(REC, learnEventSet);
	int noRecCounter = numberOfEvent(NO_REC, learnEventSet);
	entropyTarget = entropyCalc(recCounter, noRecCounter);

	const char *attrName;
	if (learnEventSet.size() <= k) {
		if (recCounter > noRecCounter) {
			attrName = REC;
		}
		else {
			attrName = NO_REC;
		}

		root = new Node(attrName);
		root->eventsSet.push_back(std::make_pair(attrName, learnEventSet));
		return;
	}

	double gain = 0;
	int attrIdx = getBestAtrrGain(learnEventSet, gain, attributesIndex);

	if (gain == 0) {
		if (!strcmp(learnEventSet[0].name, REC)) {
			attrName = REC;
		}
		else {
			attrName = NO_REC;
		}

		root = new Node(attrName);
		root->eventsSet.push_back(std::make_pair(attrName, learnEventSet));
		return;
	}

	attrName = predictors[attrIdx];
	root = new Node(attrName);
	initEventSets(root, attrIdx, learnEventSet);

	for (std::pair<const char*, std::vector<Event>> set : root->eventsSet) {
			Node *node = new Node();
			std::vector<int> vectorIndex(attributesIndex);
			buildTree(node, set.second, vectorIndex);
			root->children.push_back(node);
	}
}

void ID3::learn(std::vector<std::vector<Event>> setsOfEvent) {
	attributesIndex = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<Event> learnEventSet;
	for (std::vector<Event> es : setsOfEvent) {
		for (Event e : es) {
			learnEventSet.push_back(e);
		}
	}

	int recCounter = numberOfEvent(REC, learnEventSet);
	int noRecCounter = numberOfEvent(NO_REC, learnEventSet);
	entropyTarget = entropyCalc(recCounter, noRecCounter);

	buildTree(root, learnEventSet, attributesIndex);
}

char* ID3::getClass(Node* node, Event e, int idx) {
	if (!strcmp(node->data, REC) || !strcmp(node->data, NO_REC))
		return node->data;
	
	int i = 0;
	for (i; i < node->eventsSet.size(); ++i) {
		if (!strcmp(node->eventsSet[i].first, e.attributes[idx])) {
			int attrIdx = attributeIndex[node->children[i]->data];
			return getClass(node->children[i], e, attrIdx);
		}
	}

	int attrIdx = attributeIndex[node->children[i - 1]->data];
	return getClass(node->children[i - 1], e, attrIdx);
}

int ID3::predict(std::vector<Event> events) {
	int match = 0;
	int counter = 0;
	for (Event e : events) {
		counter++;
		int attrIdx = attributeIndex[root->data];
		char* className = getClass(root, e, attrIdx);
		if (!strcmp(className, e.name))
			match++;
	}

	return match;
}
