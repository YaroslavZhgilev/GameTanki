#include <SFML/Graphics.hpp> 
 
using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать 
int main() {  //Создаём окно  
	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 2"); 
 
	Image heroimage; //создаем объект Image (изображение)  
	heroimage.loadFromFile("images/hero.png");//загружаем в него файл 
 
	Texture herotexture;//создаем объект Texture (текстура)  
	herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения) 
 
	 Sprite herosprite;//создаем объект Sprite(спрайт)  
	 herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)  
	 herosprite.setPosition(50, 25);//задаем начальные координаты появления спрайта 
 
 while (window.isOpen())  //Пока окно открыто  
	{   
		 sf::Event event;   
		 while (window.pollEvent(event))  
			 {    
				 if (event.type == sf::Event::Closed)    
				 window.close();   
			} 
 
  window.clear(); //Очищаем экран   
  window.draw(herosprite);//рисуем объект   
  window.display(); //Показываем объект на экране 
	 } 
 
 return 0; 
 } 