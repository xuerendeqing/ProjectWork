#include "RipplePge.h"
#include <algorithm>


RipplePge* RipplePge::create(const char* filename, const PhysicsRippleSpriteConfig& config)
{
	auto m_ripple = new (std::nothrow)RipplePge();

	if (m_ripple&&m_ripple->init(filename,config))
	{
		m_ripple->autorelease();
		return m_ripple;
	}
	else
	{
		CC_SAFE_DELETE(m_ripple);
		return NULL;
	}
}

RipplePge::RipplePge() 
{
	
}
RipplePge::~RipplePge()
{
	CC_SAFE_RELEASE(m_texture);
	CC_SAFE_DELETE_ARRAY(m_vertices); 
	CC_SAFE_DELETE_ARRAY(m_texCoords); 

	for (auto kv : m_rippleCoeffs) 
	{
		CC_SAFE_DELETE_ARRAY(kv.second);
	}
	CC_SAFE_DELETE_ARRAY(m_rippleSource);
	CC_SAFE_DELETE_ARRAY(m_rippleDest);
}

bool RipplePge::init(const char* filename, const PhysicsRippleSpriteConfig& config) 
{
	auto texture = Director::getInstance()->getTextureCache()->addImage(filename);
	if (!texture)
	{
		return false;
	}
	m_texture = texture;
	
	m_texture->retain();

	m_config = config;

	this->initRippleBuffer();
	this->initRippleCoeff();
	this->initRippleMesh();


	this->setContentSize(m_texture->getContentSize());

	this->setGLProgram(GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE));

	this->scheduleUpdate();

	return true;
}
void RipplePge::reset() 
{
	memset(m_rippleSource, 0, (m_config.quadCountX + 2) * (m_config.quadCountY + 2) * sizeof(float));
	memset(m_rippleDest, 0, (m_config.quadCountX + 2) * (m_config.quadCountY + 2) * sizeof(float)); 
	m_elapseTime = 0; 
}
void RipplePge::initRippleBuffer() 
{
	m_rippleSource = new float[(m_config.quadCountX + 2) * (m_config.quadCountY + 2) * sizeof(float)];
	m_rippleDest = new float[(m_config.quadCountX + 2) * (m_config.quadCountY + 2) * sizeof(float)];
	memset(m_rippleSource, 0, (m_config.quadCountX + 2) * (m_config.quadCountY + 2) * sizeof(float));
	memset(m_rippleDest, 0, (m_config.quadCountX + 2) * (m_config.quadCountY + 2) * sizeof(float));
}
void RipplePge::initRippleCoeff()
{
	this->generateRippleCoeff(m_config.touchRadius);//初始化的时候为1
}
void RipplePge::generateRippleCoeff(int touchRadius)//4
{
	if (m_rippleCoeffs.find(touchRadius) == m_rippleCoeffs.end()) 
	{ 
		auto rippleCoeff = new float[(touchRadius * 2 + 1) * (touchRadius * 2 + 1) * sizeof(float)];

		for (int y = 0; y <= 2 * touchRadius; ++y) 
		{
			for (int x = 0; x <= 2 * touchRadius; ++x) 
			{
				float distance = sqrt((x - touchRadius) * (x - touchRadius) + (y - touchRadius)*(y - touchRadius));
				float factor = distance / touchRadius;
				if (distance <= touchRadius)//如果距离
				{
					rippleCoeff[y * (touchRadius * 2 + 1) + x] = -(cos(factor * M_PI) + 1.0f) *1500.0f;
				}
				else 
				{
					rippleCoeff[y* (touchRadius * 2 + 1) + x] = 0.0f;
				}
			}
		}
		m_rippleCoeffs[touchRadius] = rippleCoeff;
	}
}
void RipplePge::initRippleMesh() 
{
	int verticesPerStrip =2* (m_config.quadCountX + 1);
	m_bufferSize = verticesPerStrip * m_config.quadCountY;
	m_vertices = new Vec2[m_bufferSize]; 
	m_texCoords = new Vec2[m_bufferSize];

	Size textureSize = m_texture->getContentSize();
	Vec2 normalized;

	int index = 0;
	for (int y = 0; y < m_config.quadCountY; ++y) 
	{
		for (int x = 0; x < (m_config.quadCountX + 1); ++x)
		{
			for (int z = 0; z <2; ++z)
			{
				normalized.x = (float)x / (float)m_config.quadCountX;
				normalized.y = (float)(y + z) / (float)m_config.quadCountY;
				m_vertices[index] = Vec2(normalized.x * textureSize.width, normalized.y * textureSize.height);
				m_texCoords[index] = Vec2(normalized.x * m_texture->getMaxS(), m_texture->getMaxT() - (normalized.y * m_texture->getMaxT()));
				++index;
			}
		}
	}
}
void RipplePge::onDraw(const Mat4& transform) 
{
	this->getGLProgram()->use();
	this->getGLProgram()->setUniformsForBuiltins(transform);

	if (m_texture != NULL)
	{
		GL::bindTexture2D(m_texture->getName());
		GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	
	CCAssert(sizeof(Vec2) == sizeof(Vec2), "Incorrect ripple sprite buffer format");
	if (m_texture != NULL)
	{
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, m_vertices);
		glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, m_texCoords);
	}
	int verticesPerStrip = m_bufferSize / m_config.quadCountY; 
	for (int i = 0; i < m_config.quadCountY; ++i)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, i * verticesPerStrip, verticesPerStrip);
	
	}
	
}
void RipplePge::update(float dt)
{
	m_elapseTime += dt;
	if (m_elapseTime < m_config.updateInterval)
	{
		return;
	}
	else
	{
		m_elapseTime -= int(m_elapseTime / m_config.updateInterval) * m_config.updateInterval;
	}
	for (int y = 0; y < m_config.quadCountY; ++y)
	{
		for (int x = 0; x < m_config.quadCountX; ++x)
		{

			float a = m_rippleSource[(y)* (m_config.quadCountX + 2) + x + 1];
			float b = m_rippleSource[(y + 2) * (m_config.quadCountX + 2) + x + 1];
			float c = m_rippleSource[(y + 1) * (m_config.quadCountX + 2) + x];
			float d = m_rippleSource[(y + 1) * (m_config.quadCountX + 2) + x + 2];
			float result = (a + b + c + d) / 2.f - m_rippleDest[(y + 1) * (m_config.quadCountX + 2) + x + 1];
			result -= result / 30.0f;
			m_rippleDest[(y + 1) * (m_config.quadCountX + 2) + x + 1] = result;
		}
	}

	int index = 0;
	for (int y = 0; y < m_config.quadCountY; ++y)
	{
		for (int x = 0; x < m_config.quadCountX; ++x)
		{
			float a = m_rippleDest[(y)* (m_config.quadCountX + 2) + x + 1];
			float b = m_rippleDest[(y + 2) * (m_config.quadCountX + 2) + x + 1];
			float c = m_rippleDest[(y + 1) * (m_config.quadCountX + 2) + x];
			float d = m_rippleDest[(y + 1) * (m_config.quadCountX + 2) + x + 2];
			const float offsetFactor = 4096;
			float s_offset = ((b - a) / offsetFactor);
			float t_offset = ((c - d) / offsetFactor);

			s_offset = (s_offset < -0.5f) ? -0.5f : s_offset;
			t_offset = (t_offset < -0.5f) ? -0.5f : t_offset;
			s_offset = (s_offset > 0.5f) ? 0.5f : s_offset;
			t_offset = (t_offset > 0.5f) ? 0.5f :
			y == m_config.quadCountY;
			for (int z = 0; z < 2; ++z)
			{
				float s_tc = (float)x / (float)m_config.quadCountX;
				s_tc *= m_texture->getMaxS();
				float t_tc = (float)(y + z) / (float)m_config.quadCountY;
				t_tc = m_texture->getMaxT() - (t_tc * m_texture->getMaxT());
				m_texCoords[index] = Vec2(s_tc + s_offset, t_tc + t_offset);
				++index;
			}
			if (x == m_config.quadCountX-1)
			{
				for (int z = 0; z < 2; ++z)
				{
					float s_tc = 1;
					s_tc *= m_texture->getMaxS();
					float t_tc = (float)(y + z) / (float)m_config.quadCountY;
					t_tc = m_texture->getMaxT() - (t_tc * m_texture->getMaxT());
					m_texCoords[index] = Vec2(s_tc + s_offset, t_tc + t_offset);
					++index;
				}
			}
		}
	
	}
	for (int y = 1; y < m_config.quadCountY; ++y)
	{
		for (int x = 1; x < (m_config.quadCountX + 1) * 2; x += 2)
		{
			m_texCoords[(y - 1) * (m_config.quadCountX + 1) * 2 + x] = m_texCoords[y * (m_config.quadCountX + 1) * 2 + x - 1];
		}
	}
	std::swap(m_rippleSource, m_rippleDest);
	
}
void RipplePge::addRipple(const Vec2& pos, float strength)
{
	Size textureSize = m_texture->getContentSize();//获取纹理内容大小
	int xIndex = (int)((pos.x / textureSize.width) * m_config.quadCountX);
	int yIndex = (int)((pos.y / textureSize.height) * m_config.quadCountY);
	int touchRadius = int(strength * m_config.touchRadius);//4*1

	this->generateRippleCoeff(touchRadius);//产生水波纹的公式

	for (int y = yIndex - touchRadius; y <= yIndex + touchRadius; ++y)
	{
		for (int x = xIndex - touchRadius; x <= xIndex + touchRadius; ++x)
		{
			if (x >= 0 && x < m_config.quadCountX &&y >= 0 && y < m_config.quadCountY)
			{
				float rippleCoeff = m_rippleCoeffs[touchRadius][(y - (yIndex - touchRadius)) * (touchRadius * 2 + 1) + x - (xIndex - touchRadius)];
				m_rippleSource[(y+1) * (m_config.quadCountX+2) + x + 1] += rippleCoeff;
			}
		}
	}
}
void RipplePge::draw(Renderer *renderer, const Mat4& transform, uint32_t flags) 
{
	m_customCommand.init(_globalZOrder);
	m_customCommand.func = CC_CALLBACK_0(RipplePge::onDraw,this, transform);
	renderer->addCommand(&m_customCommand); 
}