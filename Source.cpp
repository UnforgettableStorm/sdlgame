
//Подключение библиотек 
#include<SDL.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctime>
#include<locale.h>

#include <iostream>


/////////////////место для функций//////////////

//Массив структур, содержащий информацию о платформе
struct SPlatform
{
	int startX, startY; //начальные координаты платформы
	int x, y;			//изменяющиеся координаты
	int endX;			//координата конца x
	int speed;			//переменная, отвечающая за скорость платформы
	bool back;			//проверяет движется ли платформа вперед или назад
};


void SPlatCalc(SPlatform* platform)
{
	if (platform->back)
	{
		platform->x -= platform->speed;
		if (platform->x < platform->startX)
		{
			platform->x = platform->startX;
			platform->back = false;
		}
	}
	else
	{
		platform->x += platform->speed;
		if (platform->x > platform->endX)
		{
			platform->x = platform->endX;
			platform->back = true;
		}
	}
}
void SPlatCalcY(SPlatform* platform)
{
	if (platform->back)
	{
		platform->y -= platform->speed;
		if (platform->y < platform->startY)
		{
			platform->y = platform->startY;
			platform->back = false;
		}
	}
	else
	{
		platform->y += platform->speed;
		if (platform->y > platform->endX)
		{
			platform->y = platform->endX;
			platform->back = true;
		}
	}
}
//функция получает на вход массив положения героя hero...
void BlockCollision(SDL_Rect hero, int block[2])
{
	if (hero.x < block[0] * 50 + 50 &&
		hero.x + hero.w > block[0] * 50 &&
		hero.y < block[1] * 50 + 50 &&
		hero.y + hero.w > block[1] * 50)
	{
		int min = 50*2;
		int test[4] = {};
	}
}

void Render_box(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Platform(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Pts(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}


void Cloud(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}



void DrawHero(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);

}

void DrawWD(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);

}


void DrawLand(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect rect)
{
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}


/////////////////main//////////////////////


const int SCR_WIDTH = 800;
const int SCR_HEIGHT = 600;
int main(int argc, char* args[])
{ 
	SDL_Window* window = NULL;
	
	SDL_Surface* screenSurface = NULL;
	setlocale(LC_ALL, "Russian");
	//Условие проверки подключения SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL не смог запуститься! SDL_Error:%s\n", SDL_GetError());
	}
	else
	{ 
		window = SDL_CreateWindow("Test 1", 100,100, SCR_WIDTH, SCR_HEIGHT, SDL_WINDOW_SHOWN);
		//Условие создание окна
		if (window == NULL)
		{
			printf("Окно не может быть создано!SDL_Error: % s\n", SDL_GetError());
		}
		else//big else
		{
			SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
			//Земляные текстуры
			SDL_Surface* land = SDL_LoadBMP("land.bmp");
			SDL_SetColorKey(land, SDL_TRUE, SDL_MapRGB(land->format, 255, 255, 255));
			SDL_Texture* land_texture = SDL_CreateTextureFromSurface(renderer, land);
			
			//Травяные текстуры
			SDL_Surface* grass = SDL_LoadBMP("grass.bmp");
			SDL_SetColorKey(grass, SDL_TRUE, SDL_MapRGB(grass->format, 255, 255, 255));
			SDL_Texture* grass_texture = SDL_CreateTextureFromSurface(renderer, grass);

			//Текстура героя
			SDL_Surface* herog = SDL_LoadBMP("cat.bmp");
			SDL_SetColorKey(herog, SDL_TRUE, SDL_MapRGB(herog->format, 255, 255, 255));
			SDL_Texture* herog_texture = SDL_CreateTextureFromSurface(renderer, herog);

			//Текстура солнца
			SDL_Surface* sun = SDL_LoadBMP("sun.bmp");
			SDL_SetColorKey(sun, SDL_TRUE, SDL_MapRGB(sun->format, 255, 255, 255));
			SDL_Texture* sun_texture = SDL_CreateTextureFromSurface(renderer, sun);
			
			//Tекстура облаков
			SDL_Surface* cloud = SDL_LoadBMP("cloud.bmp");
			SDL_SetColorKey(cloud, SDL_TRUE, SDL_MapRGB(cloud->format, 255, 255, 255));
			SDL_Texture* cloud_texture = SDL_CreateTextureFromSurface(renderer, cloud);

			//Текстура платформы
			SDL_Surface* plat = SDL_LoadBMP("platform.bmp");
			SDL_SetColorKey(plat, SDL_TRUE, SDL_MapRGB(plat->format, 255, 255, 255));
			SDL_Texture* plat_texture = SDL_CreateTextureFromSurface(renderer, plat);

			//Текстура ящика
			SDL_Surface* box = SDL_LoadBMP("box.bmp");
			SDL_SetColorKey(box, SDL_TRUE, SDL_MapRGB(box->format, 255, 255, 255));
			SDL_Texture* box_texture = SDL_CreateTextureFromSurface(renderer, box);

			//Текстура темного дерева
			SDL_Surface* dw = SDL_LoadBMP("dark_wood.bmp");
			SDL_SetColorKey(dw, SDL_TRUE, SDL_MapRGB(dw->format, 255, 255, 255));
			SDL_Texture* dw_texture = SDL_CreateTextureFromSurface(renderer, dw);


			//Массив движения
			int shift[2] = { 0,0 };
			//Заполнение массивово объектов
			SDL_Rect sunrect,cloud1,cloud2,landrect,grassrect,hero,p,p2;
			
			sunrect = { SCR_WIDTH - 100, 0 + 50, 50, 50 };
			cloud1 = { 0 + 200,0 + 50,50,50 };
			cloud2 = { 0 + 500,0 + 50,50,50 };
			hero = { 350,300,100,100 };
			p={ shift[0],shift[1], 100, 30 };
			p2 = { shift[0],shift[1], 300, 30 };
			SDL_Event event;
			bool quit = false;
			SDL_PollEvent(&event);

			const int levelSizeX = 50;//длина уровня
			const int levelSizeY = 20;//высота уровня
			int level[levelSizeX][levelSizeY];

			SPlatform splatform;
			splatform.startX = 500;
			splatform.startY = 400;
			splatform.x = splatform.startX;
			splatform.y = splatform.startY;
			splatform.endX = splatform.startX+250-100;
			splatform.speed = 1;
			splatform.back = false;
			
			SPlatform splatform2;
			splatform2.startX = 1800;
			splatform2.startY = 100;
			splatform2.x = splatform2.startX;
			splatform2.y = splatform2.startY;
			splatform2.endX = splatform2.startY + 730;
			splatform2.speed = 1;
			splatform2.back = false;



			//Генерация уровня
			for (int x = 0; x < levelSizeX; x++)
			{
				for (int y = 0; y < levelSizeY; y++)
				{
					level[x][y] = 0;
				}
			}
			for (int i = 0; i < levelSizeX; i++)
			{
				
				level[i][8] = 2;
				level[i][9] = 1;
				level[i][10] = 1;
				level[i][11] = 1;
			}

			for (int i = 10; i < 15; i++)
			{
				level[i][8] = 0;
				level[i][9] = 0;
				level[i][10] = 0;
				level[i][11] = 0;
				
			}
			for (int i = 25; i < 50; i++)
			{
				for (int j = 12; j < 20; j++)
				{
					level[i][j] = 1;

				}
			}
			for (int i = 19; i < 23; i++)
			{
				
				level[i][5] = 3;
				
			}
			level[24][3] = 3;
			level[26][1] = 3;
			
			for (int i = 36; i < 40; i++)
			{
				level[i][8] = 0;
				for (int j = 9; j < 17; j++)
				{
					level[i][j] = 0;
				}
			}
			for (int i = 32; i < 44; i++)
			{
				for (int j = 13; j < 17; j++)
				{
					level[i][j] = 0;
				}
			}
			for (int j = 5;j < 8; j++)
			{
				level[49][j] = 3;
				level[0][j] = 3;
			}
			for (int i = 33; i < 36; i++)
			{
				level[i][3] = 3;
				
			}
			for (int i = 40; i < 43; i++)
			{
				level[i][3] = 3;

			}
			while (!quit)
			{
				SDL_PollEvent(&event);
				if (event.type == SDL_QUIT)
					
					quit = true; 

				
				SDL_SetRenderDrawColor(renderer, 51, 153, 255, 0);
				SDL_RenderClear(renderer);
				DrawHero(renderer, herog_texture, hero);
				Pts(renderer, sun_texture, sunrect);
				Cloud(renderer, cloud_texture, cloud1);
				Cloud(renderer, cloud_texture, cloud2);

				p = {splatform.x - shift[0],splatform.y- shift[1], 100, 30 };
				p2 = { splatform2.x - shift[0],splatform2.y - shift[1], 200, 30 };
				Platform(renderer, plat_texture, p);
				Platform(renderer, plat_texture, p2);
				for (int x = 0; x < levelSizeX; x++)
				{
					for (int y = 0; y < levelSizeY; y++)
					{
						SDL_Texture* current;
						if (level[x][y] == 0)
						{
							continue;
						}
						else if (level[x][y] == 1)
						{
							current = land_texture;
						}
						else if (level[x][y] == 2)
						{
							current = grass_texture;
						}
						else if (level[x][y] == 3)
						{
							current = box_texture;
						}
						else if (level[x][y] == 4)
						{
							current = dw_texture;
						}
						else
						{
							continue;
						}
						landrect = { x * 50 - shift[0],y * 50 - shift[1],49,49 };
						DrawLand(renderer, current, landrect);
					}
				}

				SPlatCalc(&splatform);
				SPlatCalcY(&splatform2);
				SDL_RenderPresent(renderer);

				if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_w)) { shift[1] -= 10; }
				if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_s)) { shift[1] += 10; }
				if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_d)) { shift[0] += 10; }
				if ((event.type == SDL_KEYDOWN) && (event.key.keysym.sym == SDLK_a)) { shift[0] += -10; }
				SDL_Delay(10);
			}
			

			
			








			SDL_RenderPresent(renderer);



			SDL_Delay(5000);
		}
	}
	
















	SDL_DestroyWindow(window);
	
	SDL_Quit();
	return 0;
}