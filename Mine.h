#include "Block.h"
#include "EVW-Core.h"
#include <thread>

class Miner {
private:
	bool MiningFlag = false;
	bool ValidationFlag = true;
	//std::vector<Block*> BlockChain{};
public:
	Miner() {
		//BlockChain = vBlockList;
		std::cout << "Checking Block Data Validations..." << std::endl;
		if (isChainValid() == true) {
			std::cout << "Validations : OK" << std::endl;
			MiningFlag = true;
			while (MiningFlag == true && ValidationFlag == true)
			{
				if (this->AddNewBlockAndMine() == true) {
					FormattedPrint(BlockChain[BlockChain.size()-1]);
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}
			if (MiningFlag == false) {
				std::cout << "Miner Stopped." << std::endl;
			}
		}
		else {
			std::cout << "Chain Validation Check Failure..." << std::endl;
		}
	}

	bool AddNewBlockAndMine() {
		Block* MiningBlock = new Block("Index # " + std::to_string(BlockChain.size()), BlockChain[BlockChain.size() - 1]->hash, BlockChain.size(), difficulty);
		//BlockChain.push_back(new Block("Index # " + std::to_string(BlockChain.size()), BlockChain[BlockChain.size() - 1]->hash));
		//MiningBlock->mineBlock(difficulty);
		Block* currentBlock = nullptr;
		Block* previousBlock = nullptr;
		currentBlock = MiningBlock;
		previousBlock = BlockChain[BlockChain.size() - 1];
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

		BlockChain.push_back(MiningBlock);
		return true;
	}

	void StopWorker() {
		MiningFlag = false;
	}
};

//static bool isChainValid() {
//	Block* currentBlock = nullptr;
//	Block* previousBlock = nullptr;
//
//	for (int i = 1; i < BlockChain.size(); i++) {
//		currentBlock = BlockChain[i];
//		int tmp = i - 1;
//		previousBlock = BlockChain[tmp];
//
//		if (currentBlock->hash != currentBlock->calculateHash()) {
//			std::cout << "Current Hashes not equal!" << std::endl;
//			return false;
//		}
//
//		if (previousBlock->hash != currentBlock->previousHash) {
//			std::cout << "Previous Hashes not equal!" << std::endl;
//			return false;
//		}
//
//		if (currentBlock->hash.substr(0, difficulty) != currentBlock->pool) {
//			std::cout << "This block hasn't been mined" << std::endl;
//			return false;
//		}
//	}
//	return true;
//}