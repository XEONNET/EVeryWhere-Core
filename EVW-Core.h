#pragma once
#include "Block.h"
#include <vector>


extern std::vector<Block*> BlockChain;

extern int difficulty;

extern uint256 maxdifficulty;

extern bool isChainValid();

extern void FormattedPrint(Block* newBlock);
