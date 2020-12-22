#include "..\include\FTiler.hpp"
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(640,480), "Tile demo"); // window
	window.setFramerateLimit(60.f);

	sf::Texture tilemap_texture; // tilemap texture
	tilemap_texture.loadFromFile("../test/tile.png");

	std::ifstream is("../test/tilemap.txt"); // file for tilemap

	std::string str;
	if (is.is_open())
	{
	    std::string line;

	    while (getline (is,line))
	        str += line;

	    is.close();
	}

	FTiler tilemap(
		tilemap_texture,      // texture
		str,                  // tilemap
		32,                   // crop width
		sf::Vector2f(640,480) // fixed size
	);

	// print tilemap rects
	for (auto const& i : tilemap.getTileRect())
		std::cout << "x : " << i.left << ", y : " << i.top << ", w : " << i.width << ", h : " << i.height << std::endl;

	sf::Event event;

	while (window.isOpen())
	{
		 // event stuffs
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
				break;

				default:break;
			}
		}

		window.clear(sf::Color(55,65,85));

		// drawing
		tilemap.draw(window);

		window.display();
	}
	return 0;
}