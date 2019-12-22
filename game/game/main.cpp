#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <iostream> 
#include <cmath> 
#include <sstream> 
#include "map.h" //подключили код с картой 
#include "entity.h"
#include "random.h"
#include "gmenu.h"
#include <list>
#include <ctime>
 
using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать 
bool startGame(){
	srand(time(NULL));
		int DeadEnemyGame=0;
		//Создаём окно 
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
		sf::RenderWindow window(sf::VideoMode(800, 640, desktop.bitsPerPixel), "Lesson 6");
		//RenderWindow window(sf::VideoMode(1376, 768), "))");
	    menu(window);//вызов меню

		Font font;//шрифт 
		font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта 
		Text text("", font, 20);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях); 
		//сам объект текст (не строка) 
		text.setColor(Color::Green);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый 
		text.setStyle(Text::Bold);//жирный текст. 

		Image map_image;//объект изображения для карты,проигрыша,выигрыша
		map_image.loadFromFile("images/map_new.png");//загружаем файл для карты 
		Texture map,lose,win;;//текстура карты 
		lose.loadFromFile("images/enemy.png");
		win.loadFromFile("images/hero.png");
		Sprite win1(win),lose1(lose);
		map.loadFromImage(map_image);//заряжаем текстуру картинкой 
		Sprite s_map;//создаём спрайт для карты 
		s_map.setTexture(map);//заливаем текстуру спрайтом 

	Clock clock; //создаем переменную времени и одновременно запускаем часы! 
	Clock gameTimeClock;//переменная игрового времени, будем здесь хранить время игры 
	int gameTime = 0;//объявили игровое время, инициализировали. 

		Image heroImage; 
		heroImage.loadFromFile("images/hero.png"); // загружаем изображение игрока 

		Image easyEnemyImage; 
		easyEnemyImage.loadFromFile("images/enemy.png"); // загружаем изображение врага 

		Image BulletImage;//изображение для пули 
		BulletImage.loadFromFile("images/bullet.png");//загрузили картинку в объект изображения 

		Player p(heroImage, 50, 50, 50, 50, "Player1");//объект класса игрока 

	std::list<Entity*> enemies; //список врагов 
	std::list<Entity*> Bullets; //список пуль 
	std::list<Entity*> Bulletsenemy;//список пуль врага 
	std::list<Entity*>::iterator it; //итератор чтобы проходить по элементам списка 
	std::list<Entity*>::iterator it2; 

		Music music;
		music.openFromFile("music.ogg");
		music.play();

		SoundBuffer UdarBuffer;//создаём буфер для звука
		UdarBuffer.loadFromFile("Udar.ogg");//загружаем в него звук
		Sound Udar(UdarBuffer);//создаем звук и загружаем в него звук из буфера

		SoundBuffer shootBuffer;//создаём буфер для звука
		shootBuffer.loadFromFile("shoot.ogg");//загружаем в него звук
		Sound shoot(shootBuffer);//создаем звук и загружаем в него звук из буфера

	const int ENEMY_COUNT = 2; //максимальное количество врагов в игре 
	int enemiesCount = 0; //текущее количество врагов в игре 
	//Заполняем список объектами врагами 
	for (int i = 0; i < ENEMY_COUNT; i++) { 
		float xr = 250 + rand() % 100; //случайная координата врага на поле игры по оси “x” 
		float yr = 150 + rand() % 150; //случайная координата врага на поле игры по оси “y” //создаем врагов и помещаем в список 
			enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 50, 50, "EasyEnemy")); 
			enemiesCount += 1; //увеличили счётчик врагов 
} 


	int createObjectForMapTimer = 0;//Переменная под время для генерирования камней 
	int enemyTimer=0;//Переменная под время для генерации врагов 
	randomMapGenerate();
		while (window.isOpen()) //Пока окно открыто 
				{ 
					if (p.playerScore==5){
						win1.setPosition(0, 0);
						if (Keyboard::isKeyPressed(Keyboard::Escape)) { return true; }//если таб, то перезагружаем игру
						 }
					if (p.health<=0){
						lose1.setPosition(0, 0);
						if (Keyboard::isKeyPressed(Keyboard::Escape)) { return true; }//если таб, то перезагружаем игру
					}

				// дать время с последнего перезапуска часов, в данном случае время, прошедшее с 
				//предыдущей итерации и вызова restart(); 
					float time = clock.getElapsedTime().asMicroseconds(); 
					if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); 
						//игровое время в секундах идёт вперед, пока жив игрок. 
						//Перезагружать как time его не надо. оно не обновляет логику игры 
						clock.restart(); //перезапуск часов 
						time = time / 800; //скорость игры 

					createObjectForMapTimer += time;//наращиваем таймер 
						if (createObjectForMapTimer>1000){ 
								//randomMapGenerate();//генерация камней 
							for (it = enemies.begin(); it != enemies.end(); it++){ 
									if((*it)->life){ 
									Bulletsenemy.push_back(new Bullet(BulletImage, (*it)->x, (*it)->y, 16, 16, "Bullet", (*it)->state));
									shoot.play();
									} 
								} 
						createObjectForMapTimer = 0;//обнуляем таймер 
						} 
		enemyTimer+=time; 
		if(enemyTimer>5000){ 
				const int ENEMY_COUNT = 1; //максимальное количество врагов в игре 
				int enemiesCount = 0; //текущее количество врагов в игре 
				//Заполняем список объектами врагами 
					for (int i = 0; i < ENEMY_COUNT; i++) { 
						float xr = 250 + rand() % 100; //случайная координата врага на поле игры по оси “x”
						float yr = 150 + rand() % 150; //случайная координата врага на поле игры по оси “y” //создаем врагов и помещаем в список 
							enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 50, 50, "EasyEnemy")); 
							enemiesCount += 1; //увеличили счётчик врагов 
						} 
						enemyTimer=0; 
					} 

			sf::Event event; 
				while (window.pollEvent(event)) 
					{ 
						if (event.type == sf::Event::Closed) 
						window.close(); 

//стреляем по нажатию клавиши "P" 
				if (event.type == sf::Event::KeyPressed) 
					{ 
					if (event.key.code == sf::Keyboard::Space) 
						{ 
						Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 16, 16, "Bullet", p.state)); 
						shoot.play();
							} 
					} 
			} 

	p.update(time); //оживляем объект “p” класса “Player” с помощью времени sfml, 
	// передавая время в качестве параметра функции update. 
	//СТолкновение врагов 

		for (it = enemies.begin(); it != enemies.end(); it++)//проходимся по эл-там списка 
			{ 
				for (it2 = enemies.begin(); it2 != enemies.end(); it2++){ 
					if ((*it)->getRect() != (*it2)->getRect())//при этом это должны быть разные прямоугольники 
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//если столкнулись два объекта и они враги 
					{ 
						(*it)->dx *= -1;//меняем направление движения врага 
						(*it)->dy *= -1; 
					} 
				} 
			} 


		for (it = enemies.begin(); it != enemies.end();)//говорим что проходимся от начала до конца 
			{ 
				Entity *b = *it;//для удобства, чтобы не писать (*it)-> 
				//b->update(time);//вызываем ф-цию update для всех объектов (по сути для тех, кто жив) 
				if (b->life == false) { it = enemies.erase(it); delete b; }// если этот объект мертв, то удаляем его 
				else it++;//и идем курсором (итератором) к след объекту. так делаем со всеми объектами списка 
			} 



		for (it2 = Bullets.begin(); it2 != Bullets.end(); it2++)//проходимся по эл-там списка 
			{ 
				for (it = enemies.begin(); it != enemies.end(); it++){ 
					if ((*it)->getRect().intersects((*it2)->getRect()))//если прямоугольник спрайта объекта пересекается с игроком 
						{ (*it2)->life=0; 
						if ((*it)->name == "EasyEnemy"){//и при этом имя объекта EasyEnemy,то.. 
								(*it)->health -= 50; //иначе враг подошел к нам сбоку и нанес урон 
							} 
						} 
					} 
				} 

//Проверка пересечения пули врага с пулей игрока 

		for (it2 = Bullets.begin(); it2 != Bullets.end(); it2++)//проходимся по эл-там списка 
			{ 
				for (it = Bulletsenemy.begin(); it != Bulletsenemy.end(); it++){ 
					if ((*it)->getRect().intersects((*it2)->getRect()))//если прямоугольник спрайта объекта пересекается с игроком 
						{ (*it2)->life=0; 
						(*it)->life=0;
						} 
					} 
				} 
	//Проверка пересечения игрока с пулей 
	//Если пересечение произошло, то "health = -50" 

			if (p.life == true){//если игрок жив 
				for (it = Bulletsenemy.begin(); it != Bulletsenemy.end(); it++){ 
					//бежим по списку пуль 
					if (p.getRect().intersects((*it)->getRect())){ 
						(*it)->life=0; 
						if(((*it)->name == "Bullet")){ 
						p.health -= 50; 
						Udar.play();
							} 
						} 
					} 
				} 

//оживляем врагов 
	for (it = enemies.begin(); it != enemies.end(); it++) { 
		(*it)->update(time); //запускаем метод update() 
	} 


//оживляем пули 
	for (it = Bullets.begin(); it != Bullets.end(); it++) { 
		(*it)->update(time); //запускаем метод update() 
	} 
//оживляем пули врага 
	for (it = Bulletsenemy.begin(); it != Bulletsenemy.end(); it++) { 
		(*it)->update(time); //запускаем метод update() 
	} 


//Проверяем список на наличие "мертвых" пуль и удаляем их 
		for (it = Bullets.begin(); it != Bullets.end(); )//говорим что проходимся от начала до конца 
			{ 
			// если этот объект мертв, то удаляем его 
			if ((*it)-> life == false) { it = Bullets.erase(it);} 
			else it++;//и идем курсором (итератором) к след объекту. 
			} 
//Проверяем список на наличие мертвых вргаов 
		for (it = enemies.begin(); it != enemies.end(); )//говорим что проходимся от начала до конца 
			{ 
			// если этот объект мертв, то удаляем его
			if ((*it)-> life == false) { it = enemies.erase(it); DeadEnemyGame++;}
			else it++;//и идем курсором (итератором) к след объекту. 
			} 
//Проверяем список на наличие "мертвых" пуль врага и удаляем их 
		for (it = Bulletsenemy.begin(); it != Bulletsenemy.end();)//говорим что проходимся от начала до конца 
			{ 
			// если этот объект мертв, то удаляем его 
			if ((*it)-> life == false) { it = Bulletsenemy.erase(it);} 
			else it++;//и идем курсором (итератором) к след объекту. 
			} 

//Проверка пересечения игрока с врагами 
//Если пересечение произошло, то "health = 0", игрок обездвижевается и 
//выводится сообщение "you are lose" 
		if (p.life == true){//если игрок жив 
		for (it = enemies.begin(); it != enemies.end(); it++){ 
		//бежим по списку врагов 
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy")){ 
			p.health = 0; 
		} 
	} 
} 

window.clear(); //Очищаем экран 

/////////////////////////////Рисуем карту///////////////////// 
	for (int i = 0; i < HEIGHT_MAP; i++) 
		for (int j = 0; j < WIDTH_MAP; j++) { 
			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(64, 0, 32, 32)); //если 
			//встретили символ пробел, то рисуем 1-й квадратик 
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//если 
			//встретили символ 0, то рисуем 3й квадратик 
			if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(150, 0, 32, 32));//сердце 
			s_map.setPosition(j * 32, i * 32);//раскладываем квадратики в карту. 

window.draw(s_map);//рисуем квадратики на экран 
} 

	std::ostringstream playerHealthString, gameTimeString,enemyDead,Score;//объявили переменную здоровья и времени 
	playerHealthString << p.health; gameTimeString << gameTime; enemyDead << DeadEnemyGame;Score<<p.playerScore;//формируем строку 
	text.setString("Здоровье: " + playerHealthString.str() + "\nВремя игры: " + gameTimeString.str()+"\nУбито врагов:"+enemyDead.str()+"\nСобрано бонусов:"+Score.str());//задаем строку тексту 
	text.setPosition(0, 0);//задаем позицию текста 
	window.draw(text);//рисуем этот текст 

	window.draw(p.sprite);//рисуем объект 
	//рисуем врагов 
		for (it = enemies.begin(); it != enemies.end(); it++){ 
			window.draw((*it)->sprite); //рисуем enemies объекты 
		} 
//рисуем пули 
		for (it = Bullets.begin(); it != Bullets.end(); it++) { 
			if ((*it)->life) //если пули живы 
			window.draw((*it)->sprite); //рисуем объекты 
		} 
//рисуем пули 
		for (it = Bulletsenemy.begin(); it != Bulletsenemy.end(); it++) { 
			if ((*it)->life) //если пули живы 
			window.draw((*it)->sprite); //рисуем объекты 
		} 

window.display(); //Показываем объект на экране 
	}
}

void gameRunning(){//ф-ция перезагружает игру , если это необходимо
	if (startGame()) { gameRunning(); }////если startGame() == true, то вызываем занова ф-цию isGameRunning, которая в свою очередь опять вызывает startGame() 
}
int main() {
	gameRunning();	 
	return 0; 
}

