//#include <Windows.h>
#include "EVW-Core.h"
#include <iostream>
#include <vector>
#include "Block.h"
#include "Mine.h"
#include "json.hpp"

std::vector<Block*> BlockChain = std::vector<Block*>();

int difficulty = 1;

static bool isChainValid() {
    Block* currentBlock = nullptr;
    Block* previousBlock = nullptr;

    for (int i = 1; i < BlockChain.size(); i++) {
        currentBlock = BlockChain[i];
        int tmp = i - 1;
        previousBlock = BlockChain[tmp];

        if (currentBlock->hash != currentBlock->calculateHash()) {
            std::cout << "Current Hashes not equal!" << std::endl;
            return false;
        }

        if (previousBlock->hash != currentBlock->previousHash) {
            std::cout << "Previous Hashes not equal!" << std::endl;
            return false;
        }

        if (currentBlock->hash.substr(0, difficulty) != currentBlock->pool) {
            std::cout << "This block hasn't been mined" << std::endl;
            return false;
        }
    }
    return true;
}

void FormattedPrint(Block* newBlock) {
	json::JSON newJsonobj(
		{
			"index", newBlock->index,
			"hash", newBlock->hash,
			"previousHash", newBlock->previousHash,
			"data", newBlock->data,
			"timeStamp", std::to_string(newBlock->timeStamp),
			"nonce", std::to_string(newBlock->nonce)
		}
	);
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
    BlockChain.push_back(new Block("[EVW - EVeryWhere] Genesis Block 2021-04-30 AM 11:22:08 (GMT+9 - SEOUL. Korea)", "0", BlockChain.size() - 1, 1619749388));
    std::cout << "Trying to Mine Block # " << BlockChain.size() - 1 << std::endl;
    std::cout << "Hash : " << BlockChain[BlockChain.size() - 1]->hash << std::endl;
    BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);
    Miner* pMiner = new Miner();
    //BlockChain.push_back(new Block("Hi Second", BlockChain[BlockChain.size() - 1]->hash));
    //std::cout << "Trying to Mine Block # " << BlockChain.size() << std::endl;
    //BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);
    //BlockChain.push_back(new Block("Hi Third", BlockChain[BlockChain.size() - 1]->hash));
    //std::cout << "Trying to Mine Block # " << BlockChain.size() << std::endl;
    //BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);

    std::cout << "Validation : " << isChainValid() << std::endl;

    for (int i = 0; i < BlockChain.size(); i++) {
        FormattedPrint(BlockChain[i]);
    }
    //std::string blockChainJson
}
