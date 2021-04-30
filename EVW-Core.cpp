#include <Windows.h>
#include <iostream>
#include <vector>
#include "Block.h"

static std::vector<Block*> BlockChain = std::vector<Block*>();

int difficulty = 3;

static bool isChainValid() {
    Block* currentBlock = nullptr;
    Block* previousBlock = nullptr;

    for (int i = 1; i < BlockChain.size(); i++) {
        currentBlock = BlockChain[i];
        previousBlock = BlockChain[i - 1];

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
    std::cout << "{" << std::endl;
    std::cout << "\"hash\" : " << "\"" + newBlock->hash << "\"," << std::endl;
    std::cout << "\"previousHash\" : " << "\"" + newBlock->previousHash << "\"," << std::endl;
    std::cout << "\"data\" : " << "\"" + newBlock->data << "\"," << std::endl;
    std::cout << "\"timeStamp\" : " << "\"" + std::to_string(newBlock->timeStamp) << "\"," << std::endl;
    std::cout << "\"nonce\" : " << "\"" + std::to_string(newBlock->nonce) << "\"," << std::endl;
    std::cout << "}," << std::endl;
}

int main()
{
    std::cout << "Hello World!\n";
    BlockChain.push_back(new Block("Hi Genesis", "0"));
    std::cout << "Trying to Mine Block # " << BlockChain.size() << std::endl;
    std::cout << "Hash : " << BlockChain[BlockChain.size() - 1]->hash << std::endl;
    BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);
    BlockChain.push_back(new Block("Hi Second", BlockChain[BlockChain.size() - 1]->hash));
    std::cout << "Trying to Mine Block # " << BlockChain.size() << std::endl;
    BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);
    BlockChain.push_back(new Block("Hi Third", BlockChain[BlockChain.size() - 1]->hash));
    std::cout << "Trying to Mine Block # " << BlockChain.size() << std::endl;
    BlockChain[BlockChain.size() - 1]->mineBlock(difficulty);

    std::cout << "Validation : " << isChainValid() << std::endl;

    for (int i = 0; i < BlockChain.size(); i++) {
        FormattedPrint(BlockChain[i]);
    }
    //std::string blockChainJson
}
