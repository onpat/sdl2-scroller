#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <math.h>

const int WIDTH = 640, HEIGHT = 480;

int main(int argc, char *argv[])
{
	SDL_Surface *imageSurface = NULL;
	SDL_Surface *windowSurface = NULL;
	SDL_Surface *fontSurface = NULL;
	SDL_Surface *strSurface = NULL;
	SDL_Surface *buffSurface = NULL;
	SDL_PixelFormat *fmt;
	SDL_PixelFormat *fmts;
	SDL_Rect fontrect;
	SDL_Rect strrect;
	SDL_Rect destrect;
	SDL_Rect srcrect;
	SDL_Rect scrlrect;
	SDL_Rect scrlnrect;
	SDL_Rect destlrect;
	SDL_Rect srclrect;
	double i = 0;
	int n = 0;
	double m = 0;
	double l = 0;
	double k = 0;
	int strs[57] = {6, 7, 8, 2, 5, 4, 0, 0, 0, 0, 13, 23, 0, 8, 23, 20, 0, 2, 0, 5, 4, 14, 7, 0, 4, 0, 14, 7, 5, 23, 3, 3, 3, 0, 0, 0, 9, 23, 23, 25, 2, 24, 0, 2, 5, 0, 12, 2, 18, 7, 14, 3, 3, 3, 0, 0, 0};//zenima    so now i made a demo...   200413 im tired...
	int strnum = sizeof strs / sizeof strs[0];
	fontrect.w = 40;
	fontrect.h = 40;
	fontrect.x = 0;
	fontrect.y = 0;
	strrect.w = 40;
	strrect.h = 40;
	strrect.x = 640;
	strrect.y = 0;
	destrect.w = 1;
	destrect.h = 40;
	destrect.x = 0;
	destrect.y = 0;
	srcrect.w = 1;
	srcrect.h = 40;
	srcrect.x = 0;
	srcrect.y = 0;
	scrlrect.w = 681;
	scrlrect.h = 40;
	scrlrect.x = 1;
	scrlrect.y = 0;
	scrlnrect.w = 681;
	scrlnrect.h = 40;
	scrlnrect.x = 0;
	scrlnrect.y = 0;
	destlrect.w = 1;
	destlrect.h = 80;
	destlrect.x = 0;
	destlrect.y = 0;
	srclrect.w = 1;
	srclrect.h = 80;
	srclrect.x = 0;
	srclrect.y = 0;

	strSurface = SDL_CreateRGBSurface(0, 681, 40, 32, 0, 0, 0, 0); // 640 + 40 + 1 (17文字)

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
	}

	int flags = MIX_INIT_MOD;
	int initted = Mix_Init(flags);
	if (initted&flags != flags) {
		printf("Mix_Init: 要求したOGGとMOD形式のローダーの初期化に失敗した!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
		// ここでエラーを処理する
	}
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}

	Mix_Music *music;
	music = Mix_LoadMUS("song0.mod");
	if (!music) {
		printf("Mix_LoadMUS(\"music.mp3\"): %s\n", Mix_GetError());
		// これは恐らく致命的なエラーである
	}

	SDL_Window *window = SDL_CreateWindow("scroller", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	windowSurface = SDL_GetWindowSurface(window);

	if (NULL == window)
	{
		printf("Could not create window: %s\n", SDL_GetError());

		return EXIT_FAILURE;
	}

	SDL_Event windowEvent;

	imageSurface = SDL_LoadBMP("gris.bmp");
	if (imageSurface == NULL)
	{
		printf("SDL could not load image! SDL Error: %s\n", SDL_GetError());
	}

	fontSurface = SDL_LoadBMP("fnt.bmp");
	if (fontSurface == NULL)
	{
		printf("SDL could not load image! SDL Error: %s\n", SDL_GetError());
	}
	
	fmts=strSurface->format;
	if (SDL_SetColorKey(strSurface, SDL_TRUE, SDL_MapRGB(fmts, 0, 0, 0)) < 0) {
		printf("SDL could not set color key! SDL Error: %s\n", SDL_GetError());
	}
	
	printf("What's strSurface's BitsPerPixel? %d\n", strSurface->format->BitsPerPixel);
	
	Mix_FadeInMusic(music, -1, 2000);
	while (1)
	{
	  if (SDL_PollEvent(&windowEvent))
		{
			if (SDL_QUIT == windowEvent.type)
			{
				break;
			}
			if (windowEvent.key.keysym.sym == SDLK_SPACE) {
				break;
			}
		}

		SDL_SetColorKey(strSurface, SDL_TRUE, SDL_MapRGB(fmts, 0, 0, 0));

		if (fmod(i, 40) == 0) {
			if (n >= strnum) {
				n = 0;
			}
			fontrect.x = strs[n] * 40;
			/*if (i%680 == 0) {
				strrect.x = 0;
			} else {
				strrect.x = strrect.x + 40;
			}
			*/
			n++;
			SDL_BlitSurface(fontSurface, &fontrect, strSurface, &strrect);
		}
		SDL_BlitSurface(strSurface, &scrlrect, strSurface, &scrlnrect);

		SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);

		SDL_SetColorKey(strSurface, SDL_TRUE, SDL_MapRGB(fmts, 0, 255, 0));

		for (m = 0; m <= 640; m++) {
			srcrect.x = m;
			destrect.x = m;
			l = m / 60 + i/40;
			//if (fmod(m, 40) == 0) {
				destrect.y = sin(l) * 90 + 240;
				//if (sin(l) > 0) {
				//	destrect.y = -sin(l) * 90 + 240;
				//}
			//}
			SDL_BlitSurface(strSurface, &srcrect, windowSurface, &destrect);
		}

		/*for (m = 0; m <= 240; m++) {
			destlrect.y = sin(i/60) * 10 + 90;
			destlrect.x = m + 120;
			srclrect.x = m;
			SDL_BlitSurface(logoSurface, &srclrect, windowSurface, &destlrect);
		}*/

		i++;
		SDL_UpdateWindowSurface(window);
		SDL_Delay(10);
	}

	SDL_FreeSurface(imageSurface);
	SDL_FreeSurface(windowSurface);

	imageSurface = NULL;
	windowSurface = NULL;

	Mix_FadeOutMusic(3000);
	//SDL_Delay(3000);
	Mix_CloseAudio();
	Mix_Quit();

	SDL_DestroyWindow(window);
	SDL_Quit();

	return EXIT_SUCCESS;
}