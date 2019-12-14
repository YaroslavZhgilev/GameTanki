#include <SFML/Graphics.hpp> 
#include <iostream>
#include <cmath>
#include <sstream>
#include "map.h" //подключили код с картой 
 
using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать 

////////////////////////////////////////////////////КЛАСС ИГРОКА//////////////////////// 
class Player { // класс Игрока
private: float x,y;
public:  float w, h, dx, dy, speed; //координаты игрока х и у, высота и ширина,        
		 //ускорение (по х и по у), сама скорость  
		 float CurrentFrame;//хранит текущий кадр 
		 int playerScore,health;//новая переменная, хранящая очки игр //направление (direction) движения игрока
		 bool life;
		 enum {left, right, up, down, stay} state;//добавляем тип перечисления - состояние объекта
		 std::string File; //файл с расширением  
		 Image image;//сфмл изображение  
		 Texture texture;//сфмл текстура  
		 Sprite sprite;//сфмл спрайт 
		 //Конструктор с параметрами для класса Player. При создании объекта класса мы будем задавать 
		 //имя файла, координату Х и У, ширину и высоту 

		 Player(std::string F, float X, float Y, float W, float H){
			 dx=0; dy=0; speed = 0; playerScore = 0;health=100;
			 CurrentFrame=0;
			 state=stay;
			 life=true;
			 File = F; //имя файла+расширение  
			 w = W; 
			 h = H; //высота и ширина  
			 image.loadFromFile("images/" + File);//загружаем в image изображение, вместо File  
			 //передадим то, что пропишем при создании объекта. В нашем случае это "hero.png". Получится  
			 //запись, идентичная image.loadFromFile("images/hero/png");  
			 image.createMaskFromColor(Color(41, 33, 59)); //убираем ненужный темно-синий цвет 
			 texture.loadFromImage(image); //заносим наше изображение в текстуру  
			 sprite.setTexture(texture); //заливаем спрайт текстурой  
			 x = X; 
			 y = Y; //координата появления спрайта                  
			 sprite.setTextureRect(IntRect(0, 0, w, h)); //Задаем спрайту один прямоугольник для  //вывода одного льва. IntRect – для приведения типов 
}

		 void control(){    
				if (Keyboard::isKeyPressed(Keyboard::Left)) {     
					state = left;   
					speed = 0.1;   
				}    
				if (Keyboard::isKeyPressed(Keyboard::Right)) {     
					state = right;  
					speed = 0.1; 
				} 
 
			    if (Keyboard::isKeyPressed(Keyboard::Up)) {    
					state = up; 
					speed = 0.1; 
				} 
 
			    if (Keyboard::isKeyPressed(Keyboard::Down)) { 
					state = down;   
				    speed = 0.1;  
				}  
}
		 void update(float time) //функция "оживления/обновления" объекта класса. Принимает в себя   
			 //время SFML, вследствие чего работает бесконечно, давая персонажу движение. 
		 {  
			 if(life){//жив ли герой
				 control();//функция управления персонажем
			 switch (state)//реализуем поведение в зависимости от направления. Каждая цифра 
				 //соответствует направлению.  
			 {
				case right:{//состояние идти вправо    
					dx = speed;    
					CurrentFrame += 0.005*time;   
					if (CurrentFrame > 3) CurrentFrame -= 3;
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); 
				    break; 
						  }  
				case left:{//состояние идти влево   
					dx = -speed;  
					CurrentFrame += 0.005*time;   
					if (CurrentFrame > 3) CurrentFrame -= 3;   
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); 
					break;   
						  }

				case up:{//идти вверх   
					dy = -speed;  
					CurrentFrame += 0.005*time;    
					if (CurrentFrame > 3) CurrentFrame -= 3; 
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); 
					break; 
						}

				case down:{//идти вниз 
					dy = speed;   
					CurrentFrame += 0.005*time;  
					if (CurrentFrame > 3) CurrentFrame -= 3;    
					sprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96));
					break; 
						  }   
				case stay:{//стоим    
					dy = speed;   
					dx = speed;    
				    break;     
						  } 
			 }
 
		 x += dx*time; //движение по “X”   
		 checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х 
	     y += dy*time; //движение по “Y” 
		 checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y 
		 speed = 0;    //обнуляем скорость, чтобы персонаж остановился.   //state = stay; //состояние - стоит 
	     sprite.setPosition(x, y); //переставляем спрайт в новую позицию (x, y). 
 
		if (health <= 0){ life = false; }//если жизней меньше 0, либо равно 0, то умираем 
			 } 
		 }

	//Функция проверки столкновений с элементами карты 
		 void checkCollisionWithMap(float Dx, float Dy) {
			 for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты 
				 for (int j = x / 32; j<(x + w) / 32; j++)  { 
					 if (TileMap[i][j] == '0')//если элемент тайлик земли   
					 { 
						 if (Dy > 0) { y = i * 32 - h;  dy = 0; }//по Y   
						 if (Dy < 0) { y = i * 32 + 32; dy = 0; }//столкновение с верхними краями карты  
						 if (Dx > 0) { x = j * 32 - w; dx = 0; }//с правым краем карты   
						 if (Dx < 0) { x = j * 32 + 32; dx = 0; }// с левым краем карты 
					 }   
					 if (TileMap[i][j] == 's') { 
						 playerScore++; //если взяли камень, переменная playerScore=playerScore+1; 
						 TileMap[i][j] = ' ';  
							} 
					 if (TileMap[i][j] == 'f') {  
						 health -= 40;//если взяли ядовитый цветок,то переменная health=health-40;    
						 TileMap[i][j] = ' ';//убрали цветок  
							} 
					 if (TileMap[i][j] == 'h') {  
						 health += 20;//если взяли сердечко,то переменная health=health+20; 
						 TileMap[i][j] = ' ';//убрали сердечко  
					 }
				 }
		 }

		 FloatRect getRect(){
			 //метод получения прямоугольника. его коорд, размеры (шир,высот). 
			 FloatRect FR(x, y, w, h); // переменная FR типа FloatRect  
			 return FR;  //Тип данных (класс) "sf::FloatRect" позволяет хранить четыре координаты прямоугольника 
			 //в нашей игре это координаты текущего расположения тайла на карте 
			 //далее это позволит спросить, есть ли ещё какой-либо тайл на этом месте   
			 //эта ф-ция нужна для проверки пересечений   
		 }
};
int main() {  //Создаём окно   
	Player p("hero.png", 250, 250, 96.0, 96.0); //создаем объект “p” класса “Player”, //задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
	sf::RenderWindow window(sf::VideoMode(640, 480, desktop.bitsPerPixel), "Lesson 6"); 


Font font;//шрифт   
font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта  
Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);
//сам объект текст (не строка)  
text.setColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый  
text.setStyle(Text::Bold);//жирный текст.
	Image map_image;//объект изображения для карты 
	map_image.loadFromFile("images/map_new.png");//загружаем файл для карты 
	Texture map;//текстура карты 
	map.loadFromImage(map_image);//заряжаем текстуру картинкой  
	Sprite s_map;//создаём спрайт для карты 
	s_map.setTexture(map);//заливаем текстуру спрайтом   
 
	Clock clock;   //создаем переменную времени и одновременно запускаем часы!
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры  
	int gameTime = 0;//объявили игровое время, инициализировали.
 
	int createObjectForMapTimer = 0;//Переменная под время для генерирования камней 

 while (window.isOpen())  //Пока окно открыто  
	{   

		// дать время с последнего перезапуска часов, в данном случае время, прошедшее с              
		//предыдущей итерации и вызова restart();   
		float time = clock.getElapsedTime().asMicroseconds();
		if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds();   
		//игровое время в секундах идёт вперед, пока жив игрок.     
		//Перезагружать как time его не надо. оно не обновляет логику игры
		clock.restart(); //перезапуск часов   
		time = time / 800; //скорость игры  

		createObjectForMapTimer += time;//наращиваем таймер   
		if (createObjectForMapTimer>100){    
			randomMapGenerate();//генерация  камней   
			createObjectForMapTimer = 0;//обнуляем таймер   
 }
		    
		 sf::Event event;   
		 while (window.pollEvent(event))  
			 {    
				 if (event.type == sf::Event::Closed)    
				 window.close();   
			} 

		 p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml, 
		 // передавая время в качестве параметра функции update. 
  window.clear(); //Очищаем экран   

  /////////////////////////////Рисуем карту///////////////////// 
  for (int i = 0; i < HEIGHT_MAP; i++) 
	  for (int j = 0; j < WIDTH_MAP; j++)  {  
		  if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //если        
		  //встретили символ пробел, то рисуем 1-й квадратик   
		  if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//если   
		  //встретили символ s, то рисуем 2й квадратик   
		  if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(64, 0, 32, 32));//если 
		  //встретили символ 0, то рисуем 3й квадратик 
		  if ((TileMap[i][j] == 'f')) s_map.setTextureRect(IntRect(96, 0, 32, 32));//цветок  
		  if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(128, 0, 32, 32));//сердце 
  s_map.setPosition(j * 32, i * 32);//раскладываем квадратики в карту. 
 
  window.draw(s_map);//рисуем квадратики на экран 
	  }

	  std::ostringstream playerHealthString, gameTimeString;//объявили переменную здоровья и времени 
	  playerHealthString << p.health; gameTimeString << gameTime;//формируем строку 
	  text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str());//задаем строку тексту 
	  text.setPosition(50, 50);//задаем позицию текста 
	  window.draw(text);//рисуем этот текст

  window.draw(p.sprite);//рисуем объект   
  window.display(); //Показываем объект на экране 
	 } 
 
 return 0; 
 } 