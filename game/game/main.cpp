#include <SFML/Graphics.hpp> 
#include <SFML/Audio.hpp>
#include <iostream> 
#include <sstream> 
#include "map.h" //���������� ��� � ������ 
#include "entity.h"
#include "random.h"
#include "gmenu.h"
#include <list>
#include <ctime>
 
using namespace sf;//�������� ������������ ���� sf, ����� ��������� �� ������ 

bool startGame(){
		srand(time(NULL));
		int DeadEnemyGame=0;
		//������ ���� 
		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();  
		sf::RenderWindow window(sf::VideoMode(800, 640, desktop.bitsPerPixel), "Tanchik");
	     menu(window);//����� ����

		Font font;//����� 
		font.loadFromFile("CyrilicOld.ttf");//�������� ������ ������ ���� ������ 
		Text text("", font, 20);//������� ������ �����. ���������� � ������ ����� ������, �����, ������ ������(� ��������); 
		//��� ������ ����� (�� ������) 
		text.setColor(Color::White);//��������� ����� � �����. ���� ������ ��� ������, �� �� ��������� �� ����� 
		text.setStyle(Text::Bold);//������ �����. 

		Image map_image;//������ ����������� ��� �����
		map_image.loadFromFile("images/map_new.png");//��������� ���� ��� ����� 
		map_image.createMaskFromColor(Color(0, 0, 0));
		Texture map;//�������� ����� 

		map.loadFromImage(map_image);//�������� �������� ��������� 	
		Sprite s_map;//������ ������ ��� ����� 
		s_map.setTexture(map);//�������� �������� �������� 

	Clock clock; //������� ���������� ������� � ������������ ��������� ����! 
	Clock gameTimeClock;//���������� �������� �������, ����� ����� ������� ����� ���� 
	int gameTime = 0;//�������� ������� �����, ����������������. 

		Image heroImage; 
		heroImage.loadFromFile("images/hero.png"); // ��������� ����������� ������ 
		heroImage.createMaskFromColor(Color(0, 0, 0));

		Image easyEnemyImage; 
		easyEnemyImage.loadFromFile("images/enemy.png"); // ��������� ����������� ����� 
		 easyEnemyImage.createMaskFromColor(Color(0, 0, 0));

		Image BulletImage;//����������� ��� ���� 
		BulletImage.loadFromFile("images/bullet.png");//��������� �������� � ������ ����������� 

		Player p(heroImage, 32, 32, 32, 32, "Player1");//������ ������ ������ 

	std::list<Entity*> enemies; //������ ������ 
	std::list<Entity*> Bullets; //������ ���� 
	std::list<Entity*> Bulletsenemy;//������ ���� ����� 
	std::list<Entity*>::iterator it; //�������� ����� ��������� �� ��������� ������ 
	std::list<Entity*>::iterator it2; 

		Music music;
		music.openFromFile("music.ogg");
		music.play();
		music.setVolume(50);

		SoundBuffer hitBuffer;//������ ����� ��� �����
		hitBuffer.loadFromFile("hit.ogg");//��������� � ���� ����
		Sound hit(hitBuffer);//������� ���� � ��������� � ���� ���� �� ������

		SoundBuffer shootBuffer;//������ ����� ��� �����
		shootBuffer.loadFromFile("shoot.ogg");//��������� � ���� ����
		Sound shoot(shootBuffer);//������� ���� � ��������� � ���� ���� �� ������

	const int ENEMY_COUNT = 1; //������������ ���������� ������ � ���� 
	int enemiesCount = 0; //������� ���������� ������ � ���� 
	//��������� ������ ��������� ������� 
	for (int i = 0; i < ENEMY_COUNT; i++) { 
		float xr = 250 + rand() % 100; //��������� ���������� ����� �� ���� ���� �� ��� �x� 
		float yr = 150 + rand() % 150; //��������� ���������� ����� �� ���� ���� �� ��� �y� //������� ������ � �������� � ������ 
			enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 32, 32, "EasyEnemy")); 
			enemiesCount += 1; //��������� ������� ������ 
} 

	int createObjectForMapTimer = 0;//���������� ��� ����� ��� ������������� ���� ����� 
	int enemyTimer=0;//���������� ��� ����� ��� ��������� ������ 
	randomMapGenerate();
		while (window.isOpen()) //���� ���� ������� 
				{ //������� ������ �� ����
					if (p.playerScore==5){
						cout<<"You WIN!!!";
						return true;
						 }
					if (p.health<=0){
						cout<<"You LOSE(((";
						return true;
					}

				// ���� ����� � ���������� ����������� �����, � ������ ������ �����, ��������� � 
				//���������� �������� � ������ restart(); 
					float time = clock.getElapsedTime().asMicroseconds(); 
					if (p.life) gameTime = gameTimeClock.getElapsedTime().asSeconds(); 
						//������� ����� � �������� ��� ������, ���� ��� �����. 
						//������������� ��� time ��� �� ����. ��� �� ��������� ������ ���� 
						clock.restart(); //���������� ����� 
						time = time / 1000; //�������� ���� 

					createObjectForMapTimer += time;//���������� ������ 
						if (createObjectForMapTimer>1000){ 
								//randomMapGenerate();//��������� ������ 
							for (it = enemies.begin(); it != enemies.end(); it++){ 
									if((*it)->life){ 
									Bulletsenemy.push_back(new Bullet(BulletImage, (*it)->x, (*it)->y, 16, 16, "Bullet", (*it)->state));								
									} 
								} 
						createObjectForMapTimer = 0;//�������� ������ 
						} 
		enemyTimer+=time; 
		if(enemyTimer>5000){ 
				const int ENEMY_COUNT = 1; //������������ ���������� ������ � ���� 
				int enemiesCount = 0; //������� ���������� ������ � ���� 
				//��������� ������ ��������� ������� 
					for (int i = 0; i < ENEMY_COUNT; i++) { 
						float xr = 250 + rand() % 300; //��������� ���������� ����� �� ���� ���� �� ��� �x�
						float yr = 250 + rand() % 150; //��������� ���������� ����� �� ���� ���� �� ��� �y� //������� ������ � �������� � ������ 
							enemies.push_back(new Enemy(easyEnemyImage, xr, yr, 32, 32, "EasyEnemy")); 
							enemiesCount += 1; //��������� ������� ������ 
						} 
						enemyTimer=0; 
					} 

			sf::Event event; 
				while (window.pollEvent(event)) 
					{ 
						if (event.type == sf::Event::Closed) 
						window.close(); 

//�������� �� ������� ������� "Space" 
				if (event.type == sf::Event::KeyPressed) 
					{ 
					if (event.key.code == sf::Keyboard::Space) 
						{ 
						Bullets.push_back(new Bullet(BulletImage, p.x, p.y, 16, 16, "Bullet", p.state)); 
						shoot.play();
							} 
					} 
			} 

	p.update(time); //�������� ������ �p� ������ �Player� � ������� ������� sfml, 
	// ��������� ����� � �������� ��������� ������� update. 
	//������������ ������ 

		for (it = enemies.begin(); it != enemies.end(); it++)//���������� �� ��-��� ������ 
			{ 
				for (it2 = enemies.begin(); it2 != enemies.end(); it2++){ 
					if ((*it)->getRect() != (*it2)->getRect())//��� ���� ��� ������ ���� ������ �������������� 
					if (((*it)->getRect().intersects((*it2)->getRect())) && ((*it)->name == "EasyEnemy") && ((*it2)->name == "EasyEnemy"))//���� ����������� ��� ������� � ��� ����� 
					{ 
						(*it)->dx *= -1;//������ ����������� �������� ����� 
						(*it)->dy *= -1; 
						(*it2)->dx *= -1;
						(*it2)->dy *= -1;
					} 
				} 
			}
		//�������� ����������� ���� ����� � ������

		for (it2 = Bullets.begin(); it2 != Bullets.end(); it2++)//���������� �� ��-��� ������ 
			{ 
				for (it = enemies.begin(); it != enemies.end(); it++){ 
					if ((*it)->getRect().intersects((*it2)->getRect()))//���� ������������� ������� ������� ������������ � ������� 
						{ (*it2)->life=0; 
						if ((*it)->name == "EasyEnemy"){//� ��� ���� ��� ������� EasyEnemy,��.. 
								(*it)->health -= 50; //����� ���� ������� � ��� ����� � ����� ���� 
							} 
						} 
					} 
				} 

//�������� ����������� ���� ����� � ����� ������ 

		for (it2 = Bullets.begin(); it2 != Bullets.end(); it2++)//���������� �� ��-��� ������ 
			{ 
				for (it = Bulletsenemy.begin(); it != Bulletsenemy.end(); it++){ 
					if ((*it)->getRect().intersects((*it2)->getRect()))//���� ������������� ������� ������� ������������ � ������� 
						{ (*it2)->life=0; 
						(*it)->life=0;
						} 
					} 
				} 
	//�������� ����������� ������ � ����� 
	//���� ����������� ���������, �� "health = -50" 

			if (p.life == true){//���� ����� ��� 
				for (it = Bulletsenemy.begin(); it != Bulletsenemy.end(); it++){ 
					//����� �� ������ ���� 
					if (p.getRect().intersects((*it)->getRect())){ 
						(*it)->life=0; 
						if(((*it)->name == "Bullet")){ 
						p.health -= 50; 
						hit.play();
							} 
						} 
					} 
				} 

//�������� ������ 
	for (it = enemies.begin(); it != enemies.end(); it++) { 
		(*it)->update(time); //��������� ����� update() 
	} 


//�������� ���� 
	for (it = Bullets.begin(); it != Bullets.end(); it++) { 
		(*it)->update(time); //��������� ����� update() 
	} 
//�������� ���� ����� 
	for (it = Bulletsenemy.begin(); it != Bulletsenemy.end(); it++) { 
		(*it)->update(time); //��������� ����� update() 
	} 


//��������� ������ �� ������� "�������" ���� � ������� �� 
		for (it = Bullets.begin(); it != Bullets.end(); )//������� ��� ���������� �� ������ �� ����� 
			{ 
			// ���� ���� ������ �����, �� ������� ��� 
			if ((*it)-> life == false) { it = Bullets.erase(it);} 
			else it++;//� ���� �������� (����������) � ���� �������. 
			} 
//��������� ������ �� ������� ������� ������ 
		for (it = enemies.begin(); it != enemies.end(); )//������� ��� ���������� �� ������ �� ����� 
			{ 
			// ���� ���� ������ �����, �� ������� ���
			if ((*it)-> life == false) { it = enemies.erase(it); DeadEnemyGame++;}
			else it++;//� ���� �������� (����������) � ���� �������. 
			} 
//��������� ������ �� ������� "�������" ���� ����� � ������� �� 
		for (it = Bulletsenemy.begin(); it != Bulletsenemy.end();)//������� ��� ���������� �� ������ �� ����� 
			{ 
			// ���� ���� ������ �����, �� ������� ��� 
			if ((*it)-> life == false) { it = Bulletsenemy.erase(it);} 
			else it++;//� ���� �������� (����������) � ���� �������. 
			} 

//�������� ����������� ������ � ������� 
//���� ����������� ���������, �� "health = 0", ����� ��������������� � 
//��������� ��������� "you are lose" 
		if (p.life == true){//���� ����� ��� 
		for (it = enemies.begin(); it != enemies.end(); it++){ 
		//����� �� ������ ������ 
		if ((p.getRect().intersects((*it)->getRect())) && ((*it)->name == "EasyEnemy")){ 
			p.health = 0; 
			hit.play();
		} 
	} 
} 

window.clear(); //������� ����� 

/////////////////////////////������ �����///////////////////// 
	for (int i = 0; i < HEIGHT_MAP; i++) 
		for (int j = 0; j < WIDTH_MAP; j++) { 
			if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(50, 0, 32, 32)); //���� 
			//��������� ������ ������, �� ������ 1-� ��������� 
			if ((TileMap[i][j] == '0')) s_map.setTextureRect(IntRect(0, 0, 32, 32));//���� 
			//��������� ������ 0, �� ������ 3� ��������� 
			if ((TileMap[i][j] == 'h')) s_map.setTextureRect(IntRect(143, 0, 32, 32));//������ 
			s_map.setPosition(j * 32, i * 32);//������������ ���������� � �����. 

window.draw(s_map);//������ ���������� �� ����� 
} 

	std::ostringstream playerHealthString, gameTimeString,enemyDead,Score;//�������� ���������� �������� � ������� 
	playerHealthString << p.health; gameTimeString << gameTime; enemyDead << DeadEnemyGame;Score<<p.playerScore;//��������� ������ 
	text.setString("��������: " + playerHealthString.str() + "\n����� ����: " + gameTimeString.str()+"\n����� ������:"+enemyDead.str()+"\n������� �������:"+Score.str());//������ ������ ������ 
	text.setPosition(0, 0);//������ ������� ������ 
	window.draw(text);//������ ���� ����� 

	window.draw(p.sprite);//������ ������ 
	//������ ������ 
		for (it = enemies.begin(); it != enemies.end(); it++){ 
			window.draw((*it)->sprite); //������ enemies ������� 
		} 
//������ ���� 
		for (it = Bullets.begin(); it != Bullets.end(); it++) { 
			if ((*it)->life) //���� ���� ���� 
			window.draw((*it)->sprite); //������ ������� 
		} 
//������ ���� 
		for (it = Bulletsenemy.begin(); it != Bulletsenemy.end(); it++) { 
			if ((*it)->life) //���� ���� ���� 
			window.draw((*it)->sprite); //������ ������� 
		} 

window.display(); //���������� ������ �� ������ 
	}
}

void gameRunning(){//�-��� ������������� ���� , ���� ��� ����������
	if (startGame()) { gameRunning(); }////���� startGame() == true, �� �������� ������ �-��� isGameRunning, ������� � ���� ������� ����� �������� startGame() 
}

int main() {
	gameRunning();	 
	return 0; 
}

