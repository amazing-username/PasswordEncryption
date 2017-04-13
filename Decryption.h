#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <fstream>
#include <string>

#include "Cryption.h"

class Decryption : public Cryption
{
public:

	Decryption();
	Decryption(const std::string&);

	void setDecryptedMessage(const std::string&);
	void decryptMessage();

	std::string getDecryptedMessage() const;

private:
	std::string decryptedMessage;
};

#endif
