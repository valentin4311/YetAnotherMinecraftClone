#ifndef BLOCK_H_
#define BLOCK_H_

#include <vector>
#include <client/render/WorldRenderer.h>
#include <client/render/BlockRenderer.h>
#include <util/Side.h>

enum RenderLayer;
class AABB;

class Block
{
private:
	static std::vector<Block*> blockList;
protected:
	unsigned short id;
	unsigned int textureId;
	std::string name;

public:

	static Block* AIR;
	static Block* STONE;
	static Block* DIRT;
	static Block* GRASS;
	static Block* SAND;
	static Block* WATER;
	static Block* LEAVES_OAK;
	static Block* LEAVES_BIRCH;
	static Block* LEAVES_PINE;
	static Block* WOOD_OAK_LOG;
	static Block* WOOD_BIRCH_LOG;
	static Block* WOOD_PINE_LOG;
	static Block* TALL_GRASS;
	static Block* FLOWER_ROSE;
	static Block* FLOWER_DANDELION;
	static Block* SUGAR_CANE;
	static Block* RED_MUSHROOM;
	static Block* BROWN_MUSHROOM;
	static Block* OAK_PLANKS;
	static Block* BIRCH_PLANKS;
	static Block* PINE_PLANKS;
	static Block* GRAVEL;
	static Block* COBBLESTONE;
	static Block* MOSSY_COBBLESTONE;
	static Block* OBSIDIAN;
	static Block* COB_WEB;
	static Block* GLASS;
	static Block* BOOKSHELF;

	Block(unsigned short id, int textureId);

	short getId();

	Block* setName(const std::string& name);
	std::string getName();

	virtual int getTexture(Side faceSide);

	virtual bool isVisible();

	virtual bool isSideVisible(Block* neighbour, Side faceSide);

	virtual bool hideNeighbourFace(Block* neighbour, Side neighbourSide);

	virtual RenderLayer getRenderLayer();

	virtual AABB getHitbox(int x, int y, int z);

	virtual AABB getRenderHitbox();

	virtual bool canCollide();

	virtual bool isSimpleBlock();

	virtual RenderType getRenderType();

	static Block* getBlock(unsigned short id);

	static std::vector<Block*>& getBlockList();
};

#endif