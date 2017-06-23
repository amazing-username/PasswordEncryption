#ifndef DECRYPTION_H
#define DECRYPTION_H

#include<fstream>
#include<string>
#include<map>
#include"Cryption.h"

class Decryption : public Cryption
{
public:
	Decryption() = default;
	~Decryption() = default;
	Decryption(const std::string&);

	void setDecryptedMessage(const std::string&);
	void setMessage(const std::string&) override;
	void decryptMessage();

	std::string getDecryptedMessage() const;
	std::string getMessage() const override;
private:
	void setupMap();
	std::string cstringToString(char[], const int&);
	std::string decryptedMessage;
	std::map<std::string, char> decryptedCharacters;
};

#endif
