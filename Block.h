#pragma once
//#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <sstream>
#include <string>
#include <time.h>
#include <thread>
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

	uint256 hash{};
	uint256 previousHash{};
	unsigned int timeStamp{};
	unsigned int nonce{};
	unsigned int index{};
	unsigned int targetbits{};

	std::vector<transaction*> transactions;

	bool MakeTransaction(std::string errordat = "") {
		wallet* src = new wallet("A", "Monkey", "Chips");
		wallet* dst = new wallet("B", "Gorilla", "Chips");
		transaction* tx = new transaction(src, dst, nonce);
		std::string tmp = sha256(src->calcedhash + dst->calcedhash + std::to_string(tx->amount) + std::to_string(tx->timeStamp));
		if (tx->merkleHash == tmp)
			transactions.push_back(tx);
		else {
			errordat = tx->merkleHash + " | " + tmp;
			return false;
		}
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
		std::string temp = this->previousHash.ToString() + std::to_string(this->timeStamp) + std::to_string(this->nonce);
		std::string calculatedhash = sha256(temp);

		//std::cout << "testhash : " << calculatedhash << std::endl;
		return calculatedhash;
	}

	//uint256 calculateHash() {
	//	std::string temp = this->previousHash.ToString() + std::to_string(this->timeStamp) + std::to_string(this->nonce);
	//	std::string calculatedhash = sha256(temp);
	//	uint256 res = uint256S(calculatedhash);
	//	//std::cout << "testhash : " << calculatedhash << std::endl;
	//	return res;
	//}

	std::string dec2hex(std::string decimal_value) {
		std::stringstream ss;
		ss << std::hex << decimal_value; // int decimal_value
		std::string res(ss.str());

		std::cout << res;
		return res;
	}

	std::string hex2dec(std::string hexadecimal_value) {
		std::stringstream ss;
		ss << std::dec << hexadecimal_value; // int decimal_value
		std::string res(ss.str());

		std::cout << res;
		return res;
	}

	Block(uint256 previousHash, unsigned int idx, unsigned int diff, unsigned int timestamp = time(nullptr)) {
		if(idx == 0)
			std::cout << "Genesis Block Mining... Yay!" << std::endl;
		else
			std::cout << "Trying to Mine Block # " << idx << std::endl;
		this->index = idx;
		this->targetbits = diff;
		this->previousHash = previousHash;
		if (timestamp)
			this->timeStamp = timestamp;
		else
			this->timeStamp = time(nullptr);

		std::string temp{};
		for (int i = 0; i < this->targetbits; i++) {
			temp += "0";
		}
		std::string bsum = this->calculateHash();
		std::cout << "Genesisblock : " << bsum << std::endl;
		uint256 hashtemp = uint256S(bsum);
		//BigNumber CBigHashTemp(hex2dec(hashtemp.ToString()));
		//BigNumber CBigMax(hex2dec(max.ToString()));
		//uint256 a = uint256S("c25460078fb27d6ecc2050371fda0bf14bc6c6edc3aa88f820a276a1164678a2");

		while (bsum.substr(0, this->targetbits) != temp) {
			this->nonce++;
			bsum = this->calculateHash();
		}
		this->hash = uint256S(bsum);
		std::cout << "Block Mined!!!, Hash : " << this->hash.ToString() << std::endl;
	}
};