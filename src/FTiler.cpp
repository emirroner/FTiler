#include "..\include\FTiler.hpp"

FTiler::FTiler()
: m_tileMap({}), m_cropWidth(0)
{

}

FTiler::FTiler(sf::Texture& texture,std::string tileMap,int cropWidth,sf::Vector2f size)
{
	setCropWidth(cropWidth);
	setTexture(texture);
	setTileMap(tileMap);
	setSize(size);
}

FTiler::FTiler(sf::Texture& texture,std::vector<FTile> tileMap,int cropWidth,sf::Vector2f size)
{
	setCropWidth(cropWidth);
	setTexture(texture);
	setTileMap(tileMap);
	setSize(size);
}

void FTiler::setColor(sf::Color color)
{
	m_drawingSprite.setColor(color);
}

void FTiler::setTexture(const sf::Texture& texture)
{
	m_texture = texture;
	m_drawingSprite.setTexture(m_texture);
}

void FTiler::setTileMap(std::string tileMap)
{
	m_tileMap = parseTileMap(tileMap);
}

void FTiler::setTileMap(std::vector<FTile> tileMap)
{
	m_tileMap = tileMap;
}

void FTiler::setCropWidth(int cropWidth)
{
	m_cropWidth = cropWidth;
}

void FTiler::setSize(sf::Vector2f size)
{
	int col_maxSize = 0;

	for (auto const& i : m_tileMap)
	{
		int column = i.column;

		if (column > col_maxSize)
			col_maxSize = column;
	}

	col_maxSize++;

	int row_maxSize = 1;
	for (auto const& i : m_tileMap)
	{
		int row = i.row+1;

		if (row > row_maxSize)
			row_maxSize = row;
	}

	if (m_tileMap.size() > 0 && col_maxSize > 0)
		m_drawingSprite.setScale(size.x/(m_cropWidth*col_maxSize),size.y/(m_texture.getSize().y*row_maxSize));
}

void FTiler::draw(sf::RenderTarget& target,sf::RenderStates states)
{
	sf::Vector2f pos(0,0);
	for (auto const& i : m_tileMap)
	{
		if (i.textureID > 0)
		{
			pos.x = i.column * (m_cropWidth*m_drawingSprite.getScale().x);
			pos.y = i.row * (m_texture.getSize().y*m_drawingSprite.getScale().y);

			m_drawingSprite.setPosition(pos.x,pos.y);

			m_drawingSprite.setTextureRect(sf::IntRect(m_cropWidth*(i.textureID-1), 0, m_cropWidth,m_texture.getSize().y));
			if (i.flip == 1 || i.flip == 3)
				m_drawingSprite.setTextureRect(sf::IntRect(m_cropWidth*(i.textureID),m_drawingSprite.getTextureRect().top,-m_cropWidth,m_drawingSprite.getTextureRect().height));
			if (i.flip == 2 || i.flip == 3)
				m_drawingSprite.setTextureRect(sf::IntRect(m_drawingSprite.getTextureRect().left,(m_texture.getSize().y*(i.row+1)),m_drawingSprite.getTextureRect().width,-m_texture.getSize().y));

			target.draw(m_drawingSprite);
		}
	}
}

std::vector<sf::IntRect> FTiler::getTileRect()
{
	std::vector<sf::IntRect> result;

	for (auto const& i : m_tileMap) {
		if (i.ghostTile == 0) {
			result.push_back(sf::IntRect(i.column*(m_cropWidth*m_drawingSprite.getScale().x),i.row*(m_texture.getSize().y*m_drawingSprite.getScale().y),m_cropWidth,m_texture.getSize().y));
		}
	}

	return result;
}

std::vector<FTile> FTiler::parseTileMap(std::string str)
{
	std::vector<FTile> result;

    while (str.find('\n') <= str.size()) {str.erase(str.begin()+str.find('\n'));}

	str = trim(str);

	for (auto const& i : split(str,"|"))
	{
		FTile data;

		auto values    = split(i,".");

		data.textureID = std::stoi(values[0]);
		data.column    = std::stoi(values[1]);
		data.row       = std::stoi(values[2]);
		data.flip      = std::stoi(values[3]);
		data.ghostTile = std::stoi(values[4]);

		result.push_back(data);
	}

	return result;
}

std::string FTiler::mergeTileMap(std::vector<FTile> str)
{
	std::string result = "";
	for (auto const& i : str)
	{
		result += std::to_string(i.textureID) + "." + std::to_string(i.column) + "." + std::to_string(i.row) + "." + std::to_string(i.flip) + "." + std::to_string(i.ghostTile) + "|";
	}

	return result;
}

std::string &FTiler::ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

std::string &FTiler::rtrim(std::string &s) {
	s.erase(std::find_if(s.rbegin(), s.rend(),std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

std::string &FTiler::trim(std::string &s) {
	return ltrim(rtrim(s));
}

std::vector<std::string> FTiler::split(std::string str,std::string token)
{
	std::vector<std::string>result;
	std::string firststr = str;

	while(str.size())
	{
		size_t index = str.find(token);

		if(index != std::string::npos)
		{
			result.push_back(str.substr(0,index));
			str = str.substr(index+token.size());

			if (str.size() == 0)
				result.push_back(str);
		} else {
			result.push_back(str);
			str = "";
		}
	}

	str = firststr[firststr.length()-1];

	if (str == token)
		result.pop_back();

	return result;
}