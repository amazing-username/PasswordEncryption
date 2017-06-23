#ifndef KEYRETRIEVAL_H
#define KEYRETRIEVAL_H

#include<vector>
#include<string>
#include<list>

class KeyRetrieval
{
public:
	KeyRetrieval();
	~KeyRetrieval() = default;

	void retrieveKey();
	void addToList();
	void addRange(int, const int);

	std::vector<std::string> keyStructure();
	std::vector<int> codeCharacterStructure();
private:
	std::string fileName{"default_keys.txt"};
	std::vector<std::string> keys;
	std::vector<char> characters;
	std::vector<int> codeCharacter;
	int keySize{5};
};
#endif
