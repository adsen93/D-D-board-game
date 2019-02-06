#include "NimbleFighterBuilder.h"

#include <algorithm>


void NimbleFighterBuilder::buildAbilityScores()
{
	int scores[] = {
		product->curStr,
		product->curDex,
		product->curCon,
		product->curInt,
		product->curWis,
		product->curCha
	};
	std::sort(scores, scores + 6);
	std::reverse(scores, scores + 6);
	product->curDex = scores[0];
	product->curCon = scores[1];
	product->curStr = scores[2];
	product->curInt = scores[3];
	product->curWis = scores[4];
	product->curCha = scores[5];
	//product->recalculateAttributes();
}