#include <SFML/Graphics.hpp> 
#include <iostream>
#include <cmath>
 
using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать 
int main() {  //Создаём окно   
	
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 6"); 
 
	Image heroimage; //создаем объект Image (изображение)  
	heroimage.loadFromFile("images/hero.png");//загружаем в него файл 
 
	Texture herotexture;//создаем объект Texture (текстура)  
	herotexture.loadFromImage(heroimage);//передаем в него объект Image (изображения) 

	float CurrentFrame=0; //хранит текущий кадр 
	Clock clock;   //создаем переменную времени и одновременно запускаем часы!
 
	 Sprite herosprite;//создаем объект Sprite(спрайт)  
	 herosprite.setTexture(herotexture);//передаём в него объект Texture (текстуры)  
	 herosprite.setTextureRect(IntRect(0, 192, 96, 96));//получили нужный прямоугольник 
	 herosprite.setPosition(250, 250);//задаем начальные координаты появления спрайта 
 
 while (window.isOpen())  //Пока окно открыто  
	{   

		// дать время с последнего перезапуска часов, в данном случае время, прошедшее с              
		//предыдущей итерации и вызова restart();   
		float time = clock.getElapsedTime().asMicroseconds();    
		clock.restart(); //перезапуск часов   
		time = time / 800; //скорость игры   
		    
		 sf::Event event;   
		 while (window.pollEvent(event))  
			 {    
				 if (event.type == sf::Event::Closed)    
				 window.close();   
			} 
		 //"-0,1" - будем считать скоростью, умножаем её на наше время “time” и получаем    
		 //пройденное расстояние 
 
		 if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) 
		 { 
			 //если нажата клавиша стрелка влево или англ буква А  
			 CurrentFrame += 0.005*time;  //служит для прохождения по "кадрам". Переменная доходит до трех, суммируя произведение 
			 //времени и скорости. Изменив 0.005, можно изменить скорость анимации  
			 if (CurrentFrame > 3) CurrentFrame -= 3; //если пришли к третьему кадру - откатываемся 
			 //назад.  
			 herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //проходим по 
			 //координатам Х. Получается, что начинаем рисование с координаты Х равной 0,96,96*2, и опять 0  
			 herosprite.move(-0.1*time, 0); //происходит движение персонажа влево 
		 } 

		 if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) 
		 {   
			 CurrentFrame += 0.005*time;     
			 if (CurrentFrame > 3) CurrentFrame -= 3;     
			 herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96));     //проходим по координатам Х. получается 96,96*2,96*3 и опять 96 
		     herosprite.move(0.1*time, 0); //движение персонажа вправо 
 
		 }

		 if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) 
		 {    
			 CurrentFrame += 0.005*time;     
			 if (CurrentFrame > 3) CurrentFrame -= 3;     
			 herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96));     //проходим по координатам Х. получается 96,96*2,96*3 и опять 96   
			 herosprite.move(0, -0.1*time); //движение персонажа вверх   
		 } 

         if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) 
		 {    
			 CurrentFrame += 0.005*time;     
			 if (CurrentFrame > 3) CurrentFrame -= 3;     
			 herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));     //проходим по координатам Х. получается 96,96*2,96*3 и опять 96    
			 herosprite.move(0, 0.1*time); // движение персонажа вниз   
		 }

  window.clear(); //Очищаем экран   
  window.draw(herosprite);//рисуем объект   
  window.display(); //Показываем объект на экране 
	 } 
 
 return 0; 
 } 