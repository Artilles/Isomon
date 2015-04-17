#include "include\TileManager.h"

using namespace std;
TileManager::TileManager(void)
{
	//_tileList = new std::vector<std::vector<Tile> >();
	moveX = 0;
	moveZ = 0;
	x = 0; z = 0;
	x = 1, z = 1;
	moving = false;
	tileDist = 0.1f;
	tree = Entity("tree");
	girl = Entity("girl");
}
void TileManager::Reset()
{
	moveX = 0;
	moveZ = 0;
	x = 0; z = 0;
	x = 1, z = 1;
	moving = false;
	tileDist = 0.1f;
}


TileManager::~TileManager(void)
{
}


void TileManager::createTileSet(int rows, int columns)
{
	string line;
	int xx = 0;
	int yy = 0;
  ifstream myfile ("resource/test.txt");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
		istringstream in(line);
		for(int i = 0; i <100; i++)
		{
			int x; int y; int r; int g; int b; int enc; char s[30];
			
			in >> r >> g >> b>> enc>>s;
			
			x = xx++;
			y = yy;
			Tile tl = Tile(x, y, r, g, b, enc, s);
			if (strcmp(s, "none") != 0)
			{
				//tl.e = Entity(s);
			}
			_tileList.push_back(tl);
			

		}
		xx = 0;
		yy++;
    }
    myfile.close();
  }
  else
  {
	cout << "Unable to open file";
  }
}


void TileManager::update(double currentTime)
{
}


void TileManager::draw(int playerX, int playerY)
{


	/*
	for(int i = 0; i < _tileList.size(); i++)
	{
	glTranslatef(_tileList[i]._position.x * 0.1f, 0.0f, _tileList[i]._position.y * 0.1f);

	glBegin(GL_QUADS);

	glColor3d(_tileList[i]._colour.x / 255.0, _tileList[i]._colour.y / 255.0, _tileList[i]._colour.z / 255.0);

	glVertex3d(0.0, 0.0, 0.0);
	glVertex3d(2.5, 0.0, 0.0);
	glVertex3d(2.5, 0.0, 2.5);
	glVertex3d(0.0, 0.0, 2.5);

	glEnd();

	glTranslatef(-_tileList[i]._position.x * 0.1f, 0.0f, -_tileList[i]._position.y * 0.1f);
	}
	*/
	
	glTranslatef(-x, 0, -z);
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_DEPTH_TEST);

	int tile = 0;
	int lastTile = -2;
	for (int i = playerY - 12; i < playerY + 12; i++)
	{
		if (i > 99)
			break;
		//std::cout << "(" << i << ")" << std::endl;
		for (int j = playerX - 12; j < playerX + 12; j++)
		{
			if (i >= 0 && j >= 0)
				tile = i * 100 + j;
			if (tile != -1 && tile != lastTile)
			{
				//std::cout << "(" << tile << ")" << std::endl;
				glTranslatef(_tileList[tile]._position.x * 0.1f, 0.0f, _tileList[tile]._position.y * 0.1f);

				glBegin(GL_QUADS);

				glColor3d(_tileList[tile]._colour.x / 255.0, _tileList[tile]._colour.y / 255.0, _tileList[tile]._colour.z / 255.0);

				glVertex3d(0.0, 0.0, 0.0);
				glVertex3d(2.5, 0.0, 0.0);
				glVertex3d(2.5, 0.0, 2.5);
				glVertex3d(0.0, 0.0, 2.5);

				glEnd();
				if (strcmp(_tileList[tile]._model, "tree") == 0)
					{tree.draw();}
				if (strcmp(_tileList[tile]._model, "girl") == 0)
					{girl.draw();}
				glTranslatef(-_tileList[tile]._position.x * 0.1f, 0.0f, -_tileList[tile]._position.y * 0.1f);
	
			}
			lastTile = tile;
		}
	}
	glPopAttrib();
	

}
