#pragma once
#include "AllAdditionalAndLibraries.h"


const sf::Vector2f getMousePosView(const sf::RenderWindow& window);

void initTexAndSpr(std::unique_ptr<sf::Texture>& ptrTex, std::unique_ptr<sf::Sprite>& ptrSpr,
				   const std::string& path, const std::string& Error);

void initTex(std::unique_ptr<sf::Texture>& ptrTex, const std::string& path, const std::string& Error);

void resetSprite(std::unique_ptr<sf::Sprite>& sprite, std::unique_ptr<sf::Texture>& texture, sf::Vector2f& position); 

void resetMusicForCase(std::atomic<bool>& musicIsStopped, std::atomic<bool>& musicIsInitialized, std::unique_ptr<sf::Music>& music,
					   const std::string& path, const std::string& error); 

void resetBattleSprite(std::unique_ptr<sf::Sprite>& battleSpr, const std::unique_ptr<sf::Texture>& newTexture, const sf::Vector2f origin);

const double calculateAngle(const sf::Vector2f point, const sf::Vector2f referencePoint); 

const short dirToDegree(const short& dir_x, const short& dir_y); 

//O alternativa mai buna pentru metoda 'intersect' cand verificam coliziunea intre doua sprite-uri
const bool pixelPerfectCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2); 

const float distanceBetweenPoints(const sf::Vector2f& point1, const sf::Vector2f& point2); 


