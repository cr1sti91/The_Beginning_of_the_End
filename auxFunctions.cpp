#include "auxFunctions.h"


const sf::Vector2f getMousePosView(const sf::RenderWindow& window)
{
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	mousePosWindow = sf::Mouse::getPosition(window);
	mousePosView = window.mapPixelToCoords(mousePosWindow);

	return mousePosView; 
}


void initTexAndSpr(std::unique_ptr<sf::Texture>& ptrTex, std::unique_ptr<sf::Sprite>& ptrSpr,
				   const std::string& path, const std::string& Error)
{
	ptrTex = std::make_unique<sf::Texture>(); 
	if (!(ptrTex->loadFromFile(path)))
	{
		std::cout << Error;
	}

	ptrSpr = std::make_unique<sf::Sprite>();
	ptrSpr->setTexture(*ptrTex);
}

void initTex(std::unique_ptr<sf::Texture>& ptrTex, const std::string& path, const std::string& Error)
{
	ptrTex = std::make_unique<sf::Texture>();
	if (!(ptrTex->loadFromFile(path)))
	{
		std::cout << Error;
	}
}


void resetSprite(std::unique_ptr<sf::Sprite>& sprite, std::unique_ptr<sf::Texture>& texture, sf::Vector2f& position)
{
	sprite.reset();
	sprite = std::make_unique<sf::Sprite>();

	sprite->setTexture(*texture);
	sprite->setPosition(position);
}


void resetMusicForCase(std::atomic<bool>& musicIsStopped, std::atomic<bool>& musicIsInitialized, std::unique_ptr<sf::Music>& music,
					   const std::string& path, const std::string& error)
{
	while (!musicIsStopped)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	musicIsInitialized = false;

	music.reset();
	music = std::make_unique<sf::Music>();
	if (!(music->openFromFile(path)))
		std::cout << error << std::endl;

	music->setLoop(true);

	musicIsInitialized = true;
}


const short dirToDegree(const short& dir_x, const short& dir_y)
{
	//In sensul acelor ceasornic are loc rotirea
	switch (dir_x)
	{
		case 1:
		{
			switch (dir_y)
			{
				case 1:
				{
					return 45; 
				}break;
				case 0:
				{
					return 90; 
				}break;
				case -1:
				{
					return 135; 
				}break;
				default:
				{
					std::cout << "ERROR::Wizard::setSpriteDirection::Directie incorecta!" << std::endl;
				}break;
			}
		}break;
		case 0:
		{
			switch (dir_y)
			{
				case 1:
				{
					return 0; 
				}break;
				case 0:
				{
					return 360; 
				}break;
				case -1:
				{
					return 180; 
				}break;
				default:
				{
					std::cout << "ERROR::Wizard::setSpriteDirection::Directie incorecta!" << std::endl;
				}break;
			}
		}break;
		case -1:
		{
			switch (dir_y)
			{
				case 1:
				{
					return 315;
				}break;
				case 0:
				{
					return 270; 
				}break;
				case -1:
				{
					return 225; 
				}break;
				default:
				{
					std::cout << "ERROR::Wizard::setSpriteDirection::Directie incorecta!" << std::endl;
				}break;
			}
		}break;
		default:
		{
			std::cout << "ERROR::Wizard::setSpriteDirection::Directie incorecta!" << std::endl;
		}break;
	}
}


const float distanceBetweenPoints(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
	return std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2)); 
}



// Helper function to check if a pixel is transparent
const bool isPixelTransparent(const sf::Uint8* pixelArray, unsigned int x, unsigned int y, unsigned int width) {
	unsigned int index = 4 * (y * width + x);
	return pixelArray[index + 3] == 0; // Check alpha value (4th element in the pixel)
									   // Daca a patra valoare ce descrie pixelul este nula, atunci acesta este transparent
}

const bool pixelPerfectCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
	// Get the bounding boxes of the sprites
	sf::FloatRect bounds1 = sprite1.getGlobalBounds();
	sf::FloatRect bounds2 = sprite2.getGlobalBounds();

	// Check if the bounding boxes intersect
	if (!bounds1.intersects(bounds2)) {
		return false;
	}

	// Get the intersection rectangle
	sf::FloatRect intersection;
	bounds1.intersects(bounds2, intersection);

	// Get textures and pixel data of the sprites
	const sf::Texture* texture1 = sprite1.getTexture();
	const sf::Texture* texture2 = sprite2.getTexture();

	sf::Image image1 = texture1->copyToImage();
	sf::Image image2 = texture2->copyToImage();

	// Get the local bounding boxes (relative to the sprites' positions)
	sf::IntRect localBounds1 = sprite1.getTextureRect();
	sf::IntRect localBounds2 = sprite2.getTextureRect();

	// Loop through the intersection rectangle and check pixels
	for (int i = intersection.left; i < intersection.left + intersection.width; ++i) {
		for (int j = intersection.top; j < intersection.top + intersection.height; ++j) {
			// Calculate the positions in local texture space
			sf::Vector2f localPos1 = sprite1.getInverseTransform().transformPoint(i, j);
			sf::Vector2f localPos2 = sprite2.getInverseTransform().transformPoint(i, j);

			// Check bounds
			if (localPos1.x < 0 || localPos1.x >= localBounds1.width || localPos1.y < 0 || localPos1.y >= localBounds1.height ||
				localPos2.x < 0 || localPos2.x >= localBounds2.width || localPos2.y < 0 || localPos2.y >= localBounds2.height) {
				continue;
			}

			// Check transparency
			if (!isPixelTransparent(image1.getPixelsPtr(), localPos1.x, localPos1.y, localBounds1.width) &&
				!isPixelTransparent(image2.getPixelsPtr(), localPos2.x, localPos2.y, localBounds2.width)) {
				return true; // Collision detected
			}
		}
	}

	return false;
}



