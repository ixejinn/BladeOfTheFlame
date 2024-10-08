#pragma once

class GameObject;

class SpawnManager
{
public:
	virtual void Initialize(int maxNum, int maxActiveNum, double spawnPeriod, int spawnNumPerWave) = 0;
	virtual void Spawn() = 0;
	virtual void Clear() = 0;
};