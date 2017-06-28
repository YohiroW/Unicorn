#include "UcText.h"
#include "UcShaderMgr.h"
#include "UcGame.h"
#include "UcCamera.h"
NS_UNICORN;

Text::Text(const std::string& content, const Vector2& pos) :
RenderableObject(),
_font(Font::DEFAULT_FONT),
_textColor(ColorFRGBA::BLACK),
_scaleFactor(1.0f),
_position(Vector2(pos))
{

}

Text::~Text()
{

}

bool Text::initialize(const std::string& content, const Vector2& pos /* = Vector2(0,0) */)
{
	if (!_shader)
	{
		if (!ShaderMgr::DEFAULT_FONT)
		{
			ShaderMgr::DEFAULT_FONT = ShaderMgr::getInstance()->createShaderProgram(ShaderMgr::DEFAULT_FONT_VS,
																					ShaderMgr::DEFAULT_FONT_FS);
		}
	}
	_shader = ShaderMgr::DEFAULT_FONT;

	_shader->apply();
	_shaderLoc[0] = _shader->getLocation("projection");
	_shaderLoc[1] = _shader->getLocation("textColor");
	_shaderLoc[2] = _shader->getLocation("text");

	_textContent = content;
	_position = pos;

	this->_setup();

	return true;
}

void Text::onPreRender(Camera* cam)
{
	//
	Game* game = Game::getInstance();
	Matrix4x4 proj = cam->getOrthoMatrix(0.0f, game->getWidth(), 0.0f, game->getHeight());
	//
	_shader->apply();
	_shader->setVector3(_shaderLoc[1], _textColor.R, _textColor.G, _textColor.B);
	_shader->setMatrix4(_shaderLoc[0], proj);

	//
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Text::draw(float dt)
{
	this->_renderText(_textContent, _transform.Position().x, _transform.Position().y, _scaleFactor, _textColor);
}

void Text::onPostRender()
{

}

void Text::_setup()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* 6* 4, NULL, GL_DYNAMIC_DRAW); //two triangles as panel of character
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat)* 4, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Text::_renderText(const std::string& text, float x, float y, float scale, ColorFRGBA textColor)
{

	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(_vao);

	std::string::const_iterator iter;
	for (iter = text.begin(); iter != text.end(); ++iter)
	{
		Font::SimpleChar sch = _font.getCharFromMap(*iter); 
		
		float posx = x + sch.bearing.x * scale;
		float posy = y - (sch.size.y - sch.bearing.y)* scale;

		float width = sch.size.x * scale;
		float height = sch.size.y * scale;

		float vertices[6][4] = {
			{ posx, posy + height,       0.0, 0.0 },
			{ posx, posy,                0.0, 1.0 },
			{ posx+ width, posy ,        1.0, 1.0 },
			{ posx, posy + height,       0.0, 0.0 },
			{ posx+ width, posy,         1.0, 1.0 },
			{ posx+ width, posy+ height, 1.0, 0.0 }
		};

		glBindTexture(GL_TEXTURE_2D, sch.textureID);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//draw ch
		glDrawArrays(GL_TRIANGLES, 0, 6);

		//move to next origin point, the unit is 1/64
		x += (sch.advanced >> 6) * scale; 
	}
	
	//
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

