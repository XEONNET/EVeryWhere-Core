#pragma once
#include "Block.h"
#include <vector>


extern std::vector<Block*> BlockChain;

extern int difficulty;

extern bool isChainValid();

extern void FormattedPrint(Block* newBlock);
