#pragma once
if (onoff == true)
{
	owner_->active_ = true;

	AEInputInit();
	s32 x, y;
	AEInputGetCursorPosition(&x, &y);
	AEVec2 attackDir{ x - windowWidth / 2, windowHeight / 2 - y }, unitDir;
	AEVec2Normalize(&unitDir, &attackDir);
	if (AEInputCheckCurr(AEVK_LBUTTON))
	{

	}
}