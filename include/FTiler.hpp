#ifndef F_TILER_HPP
#define F_TILER_HPP

#include <SFML\Graphics.hpp>
#include <algorithm>
#include <vector>

struct FTile {
	unsigned short textureID;
	int column;
	int row;
	unsigned char flip;
	bool ghostTile;
};

class FTiler {
public:
	FTiler();
	FTiler(sf::Texture& texture,std::string tileMap,int cropWidth,sf::Vector2f size);
	FTiler(sf::Texture& texture,std::vector<FTile> tileMap,int cropWidth,sf::Vector2f size);

	// sets color of the m_drawingSprite
	void setColor(sf::Color color);

	// sets tilemap texture
	void setTexture(const sf::Texture& texture);

	// sets tilemap
	void setTileMap(std::string tileMap);
	void setTileMap(std::vector<FTile> tileMap);

	// sets crop width
	// crop width using for slicing the texture
	void setCropWidth(int cropWidth);

	// sets fixed tilemap size
	// i prefer use this after setting tilemap
	void setSize(sf::Vector2f size);

	// draws tilemap
	void draw(sf::RenderTarget& target,sf::RenderStates states = sf::RenderStates::Default);

	// returns tilemap rect (if ghostTile of tile is 0)
	std::vector<sf::IntRect> getTileRect();

	// parses tilemap
	//  input  : "1.0.1.2.0|3.1.1.0.1"
	//  output : {FTile{1,0,1,2,0},FTile{3,1,1,0,1}}
	static std::vector<FTile> parseTileMap(std::string str);

	// merges tilemap
	//  input  : {FTile{1,0,1,2,0},FTile{3,1,1,0,1}}
	//  output : "1.0.1.2.0|3.1.1.0.1"
	static std::string mergeTileMap(std::vector<FTile> str);

private:
	std::vector<FTile> m_tileMap;

	int m_cropWidth;

	sf::Sprite m_drawingSprite;

	sf::Texture m_texture;

	// eH (parse things)
	static std::string &ltrim(std::string &s);
	static std::string &rtrim(std::string &s);
	static std::string &trim(std::string &s);
	static std::vector<std::string> split(std::string str,std::string token);
};

#endif // F_TILER_HPP
