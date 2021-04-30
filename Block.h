#pragma once
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include "sha256.h"

//std::string to_hex_string(const unsigned int i) {
//	std::stringstream s;
//	s << "0x" << std::hex << i;
//	return s.str();
//}

class Block {
public:
	std::string hash{};
	std::string previousHash{};
	std::string pool{};
	std::string data{};
	long timeStamp{};
	int nonce{};

	void MineRes() {

	}

	void mineBlock(int difficulty) {
		std::string temp{};
		for (int i = 0; i < difficulty; i++) {
			temp += "0";
		}
		pool = temp;
		//std::cout << "Pool String : " << pool << std::endl;
		while (this->hash.substr(0, difficulty) != pool) {
			this->nonce++;
			this->hash = calculateHash();
			//std::cout << "Nonce : " << this->nonce << " hash substr 5 # " << this->hash.substr(0, difficulty) << std::endl;
		}

		std::cout << "Block Mined!!!, Hash : " << this->hash << std::endl;
	}

	std::string calculateHash() {
		std::string temp = this->previousHash + std::to_string(this->timeStamp) + std::to_string(this->nonce) + this->data;
		std::string calculatedhash = sha256(temp);

		//std::cout << "testhash : " << calculatedhash << std::endl;
		return calculatedhash;
	}

	Block(std::string data, std::string previousHash) {
		this->data = data;
		this->previousHash = previousHash;
		this->timeStamp = (long)time(nullptr);
		this->hash = this->calculateHash();
	}
};