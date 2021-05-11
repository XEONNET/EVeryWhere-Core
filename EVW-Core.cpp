//#include <Windows.h>
#include "EVW-Core.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "Block.h"
#include "Mine.h"
#include "json.hpp"
#include "uint256.h"

std::vector<Block*> BlockChain = std::vector<Block*>();

int difficulty = 3;

uint256 maxdifficulty = uint256S("0x00000000ffff0000000000000000000000000000000000000000000000000000");

bool isChainValid() {
    Block* currentBlock = nullptr;
    Block* previousBlock = nullptr;

    for (int i = 1; i < BlockChain.size(); i++) {
        currentBlock = BlockChain[i];
        int tmp = i - 1;
        previousBlock = BlockChain[tmp];

        if (currentBlock->hash.ToString() != currentBlock->calculateHash()) {
            std::cout << "Current Hashes not equal!" << std::endl;
            return false;
        }

        if (previousBlock->hash != currentBlock->previousHash) {
            std::cout << "Previous Hashes not equal!" << std::endl;
            return false;
        }

        std::string temp{};
        for (int i = 0; i < currentBlock->targetbits; i++) {
            temp += "0";
        }
        if (currentBlock->hash.ToString().substr(0, currentBlock->targetbits) != temp) {
            std::cout << "This block hasn't been mined" << std::endl;
            return false;
        }
    }
    return true;
}

void loadfromdb() {

}

void savetodb(json::JSON ad) {
    std::ofstream output("Blocks.evwdat", std::ios::app);
    output << ad <<",\n";
    output.close();
}

void FormattedPrint(Block* newBlock) {
    json::JSON TXIDs;

    for (int i = 0; i < newBlock->transactions.size(); i++) {
		json::JSON newTXID(
			{
				"SourceWallet", "0x"+newBlock->transactions[i]->srcwallet->walletaddress,
				"DestinyWallet", "0x"+newBlock->transactions[i]->dstwallet->walletaddress,
				"Amount", newBlock->transactions[i]->amount,
				"MerkleRoot", "0x"+newBlock->transactions[i]->merkleHash,
				"TimeStamp", newBlock->transactions[i]->timeStamp
			}
		);
        TXIDs[i] = newTXID;
    }

	json::JSON newJsonobj(
		{
			"index", newBlock->index,
			"nonce", newBlock->nonce,
			"hash", "0x"+newBlock->hash.ToString(),
			"previousHash", "0x"+newBlock->previousHash.ToString(),
			"timeStamp", std::to_string(newBlock->timeStamp),
            "txids", TXIDs
		}
	);

    savetodb(newJsonobj);
    //array[1] = TXIDs;
    //system("cls");
    std::cout << newJsonobj << std::endl;
    //std::cout << "{" << std::endl;
    //std::cout << "\"hash\" : " << "\"" + newBlock->hash << "\"," << std::endl;
    //std::cout << "\"previousHash\" : " << "\"" + newBlock->previousHash << "\"," << std::endl;
    //std::cout << "\"data\" : " << "\"" + newBlock->data << "\"," << std::endl;
    //std::cout << "\"timeStamp\" : " << "\"" + std::to_string(newBlock->timeStamp) << "\"," << std::endl;
    //std::cout << "\"nonce\" : " << "\"" + std::to_string(newBlock->nonce) << "\"," << std::endl;
    //std::cout << "}," << std::endl;
}

int main()
{

    // The First Validation.
    //Block(std::string data, uint256 previousHash, unsigned int idx, unsigned int diff, unsigned int timestamp = time(nullptr))
    //[EVW - EVeryWhere] Genesis Block 2021-04-30 AM 11:22:08 (GMT+9 - SEOUL. Korea)
    BlockChain.push_back(new Block(uint256S("0"), BlockChain.size(), 1, 1619749388));
    //BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);
    FormattedPrint(BlockChain[BlockChain.size() - 1]);
    Miner* pMiner = new Miner();
    //20160Blocks * 1Minues / last 20160blocks min

    //BlockChain.push_back(new Block("Hi Second", BlockChain[BlockChain.size() - 1]->hash));
    //std::cout << "Trying to Mine Block # " << BlockChain.size() << std::endl;
    //BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);
    //BlockChain.push_back(new Block("Hi Third", BlockChain[BlockChain.size() - 1]->hash));
    //std::cout << "Trying to Mine Block # " << BlockChain.size() << std::endl;
    //BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);

    //std::cout << "Validation : " << isChainValid() << std::endl;

    //for (int i = 0; i < BlockChain.size(); i++) {
    //    FormattedPrint(BlockChain[i]);
    //}
    //std::string blockChainJson
}
