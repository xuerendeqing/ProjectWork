#ifndef _RIPPLE_PGE_H_
#define _RIPPLE_PGE_H_

#include "GameDefine.h"

class RipplePge :public Node
{
public:
	static RipplePge* create(const char* filename, const PhysicsRippleSpriteConfig& config = PhysicsRippleSpriteConfig());

	RipplePge();

	virtual ~RipplePge();

	bool init(const char* filename, const PhysicsRippleSpriteConfig& config);

	void reset();

	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags); 

	void onDraw(const Mat4& transform); 

	virtual void update(float dt);

	void addRipple(const Vec2& pos, float strength);
	
private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	void initRippleBuffer();
	void initRippleCoeff();
	void initRippleMesh();
	void generateRippleCoeff(int touchRadius);

	PhysicsRippleSpriteConfig m_config;

	Texture2D* m_texture{ nullptr };
	int m_bufferSize{ 0 }; 
	Vec2* m_vertices{ nullptr }; 
	Vec2* m_texCoords{ nullptr };

	
	map<int, float*> m_rippleCoeffs;
	float* m_rippleSource{ nullptr };
	float* m_rippleDest{ nullptr };

	float m_elapseTime{ 0 };

	CustomCommand m_customCommand;
};
#endif