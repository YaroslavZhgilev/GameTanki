#include <SFML\Graphics.hpp> 
const int HEIGHT_MAP = 15;//������ ����� ������ const 
int WIDTH_MAP = 20;//������ ����� ������  
 
std::string TileMap[HEIGHT_MAP] = { 
	"00000000000000000000", 
	"0                  0", 
	"0   s  s       f   0", 
	"0                  0", 
	"0     s            0",
	"0             h    0",
	"0  h               0", 
	"0       f          0",
	"0 s                0",
	"0          h       0", 
	"0      s           0",
	"0                  0", 
	"0  h           f   0", 
	"0                  0", 
	"00000000000000000000",
};

void randomMapGenerate(){//�������� ����������� ����� 
 
	int randomElementX = 0;//���������� ��� �������� ���������� �������� �� ����������� 
	int randomElementY = 0;//���������� ��� �������� ���������� �������� �� ��������� 
	srand(time(0));//������������� ���������� ��������� �����  
	int countStone = 3;//���������� ������ 
	 while (countStone>0){  
		randomElementX = 1 + rand() % (WIDTH_MAP - 1);//��������������� �������� �� �x� �� 1 ��  //������ �����-1. ����������� ������� ����� �� �������� ����� ������� �����  
		randomElementY = 1 + rand() % (HEIGHT_MAP - 1);//�� �y� 
 
 if (TileMap[randomElementY][randomElementX] == ' ')   {
	 //���� ��������� ������ ������,    
	 TileMap[randomElementY][randomElementX] = 's';  //�� ������ ���� ������.    
	 countStone--;   
		}  
	} 
};