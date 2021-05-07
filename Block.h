#pragma once
//#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>
#include <time.h>
#include "sha256.h"
#include "uint256.h"

//std::string to_hex_string(const unsigned int i) {
//	std::stringstream s;
//	s << "0x" << std::hex << i;
//	return s.str();
//}
class wallet {
public:
	std::string walletaddress;
	std::string pubkey;
	std::string privkey;
	std::string calcedhash;
	wallet(std::string name, std::string pubkeya, std::string privkeyb) {
		this->walletaddress = name;
		this->pubkey = pubkeya;
		this->privkey = privkeyb;
		this->calcedhash = sha256(name + pubkeya + privkeyb);
	}
};

class transaction {
public:
	wallet* srcwallet;
	wallet* dstwallet;
	unsigned int timeStamp;
	float amount;
	std::string merkleHash;
	transaction(wallet* src, wallet* dst, float amount) {
		this->srcwallet = src;
		this->dstwallet = dst;
		this->amount = amount;
		this->timeStamp = time(nullptr);
		this->merkleHash = sha256(this->srcwallet->calcedhash + this->dstwallet->calcedhash + std::to_string(this->amount) + std::to_string(this->timeStamp));
	}
};

class Block {
public:
	//int nVersion;
	//uint256 hashPrevBlock;
	//uint256 hashMerkleRoot;
	//unsigned int nTime;
	//unsigned int nBits;
	//unsigned int nNonce;
	//mutable std::vector<uint256> vMerkleTree;

	std::string hash{};
	std::string previousHash{};
	std::string pool{};
	std::string data{};
	unsigned int timeStamp{};
	unsigned int nonce{};
	unsigned int index{};
	unsigned int targetbits{};

	std::vector<transaction*> transactions;

	bool transactionvalidandadd() {
		wallet* src = new wallet("A", "Monkey", "Chips");
		wallet* dst = new wallet("B", "Gorilla", "Chips");
		transaction* tx = new transaction(src, dst, nonce);
		if (tx->merkleHash == sha256(src->calcedhash + dst->calcedhash + std::to_string(tx->amount) + std::to_string(tx->timeStamp)))
			transactions.push_back(tx);
		else
			return false;
	}

	//void mineBlock(int difficulty) {
	//	std::string temp{};
	//	for (int i = 0; i < difficulty; i++) {
	//		temp += "0";
	//	}
	//	pool = temp;
	//	//std::cout << "Pool String : " << pool << std::endl;
	//	while (this->hash.substr(0, difficulty) != pool) {
	//		this->nonce++;
	//		this->hash = calculateHash();
	//		//std::cout << "Nonce : " << this->nonce << " hash substr 5 # " << this->hash.substr(0, difficulty) << std::endl;
	//	}

	//	std::cout << "Block Mined!!!, Hash : " << this->hash << std::endl;
	//}

	std::string calculateHash() {
		std::string temp = this->previousHash + std::to_string(this->timeStamp) + std::to_string(this->nonce) + this->data;
		std::string calculatedhash = sha256(temp);

		//std::cout << "testhash : " << calculatedhash << std::endl;
		return calculatedhash;
	}

	Block(std::string data, std::string previousHash, unsigned int idx, unsigned int diff, unsigned int timestamp = time(nullptr)) {
		std::cout << "Trying to Mine Block # " << idx << std::endl;
		this->index = idx;
		this->targetbits = diff;
		this->data = data;
		this->previousHash = previousHash;
		if (timestamp)
			this->timeStamp = timestamp;
		else
			this->timeStamp = (long)time(nullptr);

		std::string temp{};
		for (int i = 0; i < diff; i++) {
			temp += "0";
		}
		pool = temp;
		//std::cout << "Pool String : " << pool << std::endl;
		this->hash = this->calculateHash();
		while (this->hash.substr(0, diff) != pool) {
			if(transactionvalidandadd() == false)
				std::cout << "Transaction Validation Failure" << std::endl;
			this->nonce++;
			this->hash = calculateHash();
			//std::cout << "Nonce : " << this->nonce << " hash substr 5 # " << this->hash.substr(0, difficulty) << std::endl;
		}

		//nVersion = 0x1;
		//hashPrevBlock = uint256S(this->previousHash);
		//hashMerkleRoot = uint256S(this->hash);
		//nTime = this->timeStamp;
		//nNonce = this->nonce;

		std::cout << "Block Mined!!!, Hash : " << this->hash << std::endl;
	}
};