#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdbool.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (a) : (b))

/* Window resolution */
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

/* Window title */
#define WINDOW_TITLE "SDL2 Test"

/* The window */
SDL_Window* window = NULL;
	
/* The window surface */
SDL_Surface* screen = NULL;

/* The event structure */
SDL_Event event;

/* The game loop flag */
_Bool running = true;

/* to put the loaded image */
SDL_Surface* image = NULL;

SDL_Renderer* gRenderer = NULL;

void makeArrow( SDL_Renderer* gr, double vx, double vy, double originX, double originY, double length )
{
   //double angle = M_PI / 2.0;
   //if (vx != 0) {angle = atan(abs(vy / vx));}
   //double x = cos(angle) * length;
   //double y = sin(angle) * length;
   //if (vx < 0) {x = x * (-1);}
   //if (vy < 0) {y = y * (-1);}
   //SDL_RenderDrawLine( gRenderer, originX, originY, originX + (vx*10),  originY - (vy*10) );
   //double arrowX = cos(angle + ((3.0 * M_PI) / 4.0)) * (length / 5.0);
   //double arrowY = sin(angle + ((3.0 * M_PI) / 4.0)) * (length / 5.0);
   //if (vx < 0) {arrowX = arrowX * (-1);}
   //if (vy < 0) {arrowY = arrowY * (-1);}
   //SDL_RenderDrawLine( gRenderer, originX + x, originY - y, originX + x + arrowX, originY - y - arrowY );
   //arrowX = cos(angle - ((3.0 * M_PI) / 4.0)) * (length / 5.0);
   //arrowY = sin(angle - ((3.0 * M_PI) / 4.0)) * (length / 5.0);
   //if (vx < 0) {arrowX = arrowX * (-1);}
   //if (vy < 0) {arrowY = arrowY * (-1);}
   //SDL_RenderDrawLine( gRenderer, originX + x, originY - y, originX + x + arrowX, originY - y - arrowY );
   double vectorLength = sqrt((vx * vx) + (vy * vy));
   double vectorRatio = length / vectorLength;
   double x = vx * vectorRatio;
   double y = vy * vectorRatio;
   SDL_RenderDrawLine( gRenderer, originX, originY, originX + x,  originY - y );
   //double vectorGradient = y / x;
   
   /*double vectorAngle = atan(vy / vx);
   double a = sqrt(((length / 10) * (length / 10)) / 2);
   double anglea = atan(a / ((9 * length) / 10));
   double angleb = vectorAngle - anglea;
   double hypotenuse = sqrt((a * a) + (((9 * length) / 10) * ((9 * length) / 10)));
   double arrowX = hypotenuse * cos(angleb);
   double arrowY = hypotenuse * sin(angleb);
   SDL_RenderDrawLine( gRenderer, originX + x, originY - y, originX + arrowX, originY - arrowY );*/

   //SDL_RenderDrawLine( gRenderer, originX + x + (length / 10), originY - y - (length / 10), originX + x - (length / 10), originY - y + (length / 10) );
    //SDL_RenderDrawLine( gRenderer, originX + x + (length / 10), originY - y + (length / 10), originX + x - (length / 10), originY - y - (length / 10) );

   //double arrowLength = length / 10;
   //double arrowGradient = vectorGradient * (-0.25);
   //double arrowX = originX + x + arrowLength / sqrt(1 + (arrowGradient * arrowGradient));
   //double arrowY = originY - y - ((2 * arrowLength) / sqrt(1 + (arrowGradient * arrowGradient)));
   //SDL_RenderDrawLine( gRenderer, originX + x, originY - y, arrowX, arrowY );
   //double arrowX = x / 10;
   //double arrowY = y / 10;
   //SDL_RenderDrawLine( gRenderer, originX + x, originY - y, originX + x - (arrowX / 2), originY - y + (arrowY * 2) );
   
   //double arrowX = X + D/(sqrt(1+m^2));
   //B = Y + M*D/(sqrt(1+m*m))
   //SDL_RenderDrawLine( gRenderer, originX + x, originY - y, originX + x + (length / (10 * sqrt(1 + (vectorGradient * vectorGradient)))), originY - y - ((vectorGradient * vectorGradient) / (10 * (sqrt(1 + (vectorGradient * vectorGradient)))))  );
   if (vx == 0)
   {
      /*double arrowX1 = length / 10;
      double arrowY1 = sqrt(((length / 10) * (length / 10)) + ((length / 10) * (length / 10)));
      double arrowX2 = length / 10;
      double arrowY2 = sqrt(((length / 10) * (length / 10)) + ((length / 10) * (length / 10))) * (-1);*/
      //double arrowX = sqrt(((length / 10) * (length / 10)) + ((length / 10) * (length / 10)));
      double arrowX = length / 20;
      double arrowY = length / 10;
      if (vy > 0)
      {
         filledTrigonRGBA(gRenderer, originX + x, originY - y, originX + x + arrowX, originY - y + arrowY, originX + x - arrowX, originY - y + arrowY, 0, 0, 0, 255);
      }
      else
      {
         filledTrigonRGBA(gRenderer, originX + x, originY - y, originX + x + arrowX, originY - y - arrowY, originX + x - arrowX, originY - y + arrowY, 0, 0, 0, 255);
      }
   }
   else
   {
      double arrowX1 = (length / 10) + sin(vy / vx);
      double arrowX2 = (length / 10) - sin(vy / vx);
      double arrowY1 = (length / 20) + cos(vy / vx);
      double arrowY2 = (length / 20) - cos(vy / vx) * (-1);
      if (vx < 0)
      {
         arrowX1 = arrowX1 + (length / 10);
         arrowX2 = arrowX2 - (length / 10);
      }
      if (vy < 0)
      {
         arrowY1 = arrowY1 * (-1);
         arrowY2 = arrowY2 * (-1);
      }
      filledTrigonRGBA(gRenderer, originX + x, originY - y, originX + x + arrowX1, originY - y + arrowY1, originX + x + arrowX2, originY - y + arrowY2, 0, 0, 0, 255);
   }
}

bool trajectory = false;

int main( int argc, char* argv[] )
{
 if ( argc == 2 && !strcmp(argv[1], "-trajectory")){trajectory = true;}
 if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
 {
   printf( "SDL2 could not initialize! SDL2_Error: %s\n", SDL_GetError() );
 }
 else
 {
   int width;
   printf("enter width\n");
   scanf("%d", &width);
   int height;
   printf("enter height\n");
   scanf("%d", &height);
   double vectors[width * height * 4];
   double edges[width * height * 16];
   int i;
   for (i = 0; i < width * height; ++i)
   {
      printf("enter vectors a and b for region %d\n", i + 1);
      scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf", &edges[i*16], &edges[(i*16) + 1], &edges[(i*16) + 2], &edges[(i*16) + 3], &edges[(i*16) + 4], &edges[(i*16) + 5], &edges[(i*16) + 6], &edges[(i*16) + 7], &edges[(i*16) + 8], &edges[(i*16) + 9], &edges[(i*16) + 10], &edges[(i*16) + 11], &edges[(i*16) + 12], &edges[(i*16) + 13], &edges[(i*16) + 14], &edges[(i*16) + 15]);
      scanf("%lf %lf %lf %lf", &vectors[i*4], &vectors[(i*4) + 1], &vectors[(i*4) + 2], &vectors[(i*4) + 3]);
      printf("vectors are (%lf, %lf) and (%lf, %lf)\n", vectors[i*4], vectors[(i*4)+1], vectors[(i*4)+2], vectors[(i*4)+3]);
   }
   double initial[4];
   int numberOfIntervals = 0;
   if (trajectory)
   {
      printf("enter initial\n");
      scanf("%lf %lf %lf %lf", &initial[0], &initial[1], &initial[2], &initial[3]);
      double target[4];
      printf("enter target\n");
      scanf("%lf %lf %lf %lf", &target[0], &target[1], &target[2], &target[3]);
      //int numberOfIntervals;
      printf("enter number of intervals\n");
      scanf("%d", &numberOfIntervals);
      printf("entered %d\n", numberOfIntervals);
   }
   double intervals[numberOfIntervals * 8];
   if (trajectory)
   {
      printf("number of intervals is %d\n", numberOfIntervals);
      for (i = 0; i < numberOfIntervals; ++i)
      {
         printf("enter interval (%d of %d)\n", i + 1, numberOfIntervals);
         scanf("%lf %lf %lf %lf %lf  %lf %lf %lf", &intervals[i * 8], &intervals[(i * 8) + 1], &intervals[(i * 8) + 2],  &intervals[(i * 8) + 3], &intervals[(i * 8) + 4], &intervals[(i * 8) + 5], &intervals[(i * 8) + 6], &intervals[(i * 8) + 7]);
      }
   }
   printf("start at (%f, %f) to (%f, %f), finish at (%f, %f) to (%f, %f)\n", intervals[0], intervals[1], intervals[2], intervals[3], intervals[24], intervals[25], intervals[26], intervals[27]);
   printf("i0 = %f, i1 = %f, i2 = %f, i3 = %f, i4 = %f, i5 = %f, i6 = %f, i7 = %f\n", intervals[8], intervals[8 + 1], intervals[8 + 2], intervals[8 + 3], intervals[8 + 4], intervals[8 + 5], intervals[8 + 6], intervals[8 + 7]);

   window = SDL_CreateWindow(
       WINDOW_TITLE,
       SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED,
       WINDOW_WIDTH,
       WINDOW_HEIGHT,
       SDL_WINDOW_SHOWN);

   gRenderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
   if( gRenderer == NULL ) 
   {
      printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
   }
   
   screen = SDL_GetWindowSurface( window );
   //image = SDL_LoadBMP( "sdl_logo.bmp" );
   while( running )
   {
      while( SDL_PollEvent( &event ) != 0 )
      {
         if( event.type == SDL_QUIT )
         {
            running = false;
         }
         else if( event.type == SDL_KEYDOWN )
         {
            running = false;
         }
      }
      //Clear screen
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear( gRenderer );

      /*SDL_Rect fillRect = { WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };
      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0, 0, 0xFF );
      SDL_RenderFillRect( gRenderer, &fillRect );

      SDL_Rect outlineRect = { WINDOW_WIDTH / 6, WINDOW_HEIGHT / 6, WINDOW_WIDTH * 2 / 3, WINDOW_HEIGHT * 2 / 3 };
      SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );
      SDL_RenderDrawRect( gRenderer, &outlineRect );

      SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
      SDL_RenderDrawLine( gRenderer, 0, WINDOW_HEIGHT / 2, WINDOW_WIDTH, WINDOW_HEIGHT / 2 );

      SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0x00, 0xFF );
      int i;
      for( i = 0; i < WINDOW_HEIGHT; i += 4 )
      {
         SDL_RenderDrawPoint( gRenderer, WINDOW_WIDTH / 2, i );
      }*/

      SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
      for (i = 1; i < width; ++i)
      {
         SDL_RenderDrawLine( gRenderer, (WINDOW_WIDTH * i) / width, 0, (WINDOW_WIDTH * i) / width, WINDOW_HEIGHT );
      }
      for (i = 1; i < height; ++i)
      {
         SDL_RenderDrawLine( gRenderer, 0, (WINDOW_HEIGHT * i) / height, WINDOW_WIDTH, (WINDOW_HEIGHT * i) / height );
      }
      int vectorNumber = 0;
      int j;
      for (i = 0; i < height; ++i)
      {
         for (j = 0; j < width; ++j)
         {
            makeArrow( gRenderer, vectors[vectorNumber], vectors[vectorNumber + 1], (((WINDOW_WIDTH * j) / width) + ((WINDOW_WIDTH * (j + 1)) / width)) / 2, (((WINDOW_HEIGHT * (height - i)) / height) + ((WINDOW_HEIGHT * (height - i - 1)) / height)) / 2, MIN((3 * WINDOW_WIDTH) / (8 * width), (3 * WINDOW_HEIGHT) / (8 * height)) );
            makeArrow( gRenderer, vectors[vectorNumber + 2], vectors[vectorNumber + 3], (((WINDOW_WIDTH * j) / width) + ((WINDOW_WIDTH * (j + 1)) / width)) / 2, (((WINDOW_HEIGHT * (height - i)) / height) + ((WINDOW_HEIGHT * (height - i - 1)) / height)) / 2, MIN((3 * WINDOW_WIDTH) / (8 * width), (3 * WINDOW_HEIGHT) / (8 * height)) );
            vectorNumber = vectorNumber + 4;
         }
      }
      if (trajectory)
      {
         SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
         //SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (initial[0] / width), WINDOW_HEIGHT * (WINDOW_HEIGHT - (initial[1] / height)), WINDOW_WIDTH * (initial[2] / width), WINDOW_HEIGHT * (WINDOW_HEIGHT - (initial[3] / height)) );
         //SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (initial[0] / width), 599, WINDOW_WIDTH * (initial[2] / width), 599 );
         /*SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[0] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[1] / height)), WINDOW_WIDTH * (intervals[2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[3] / height)) );
         if (intervals[0] == intervals[2])
         {
            SDL_RenderDrawLine( gRenderer, (WINDOW_WIDTH * (intervals[0] / width)) + 1, WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[1] / height)), (WINDOW_WIDTH * (intervals[2] / width)) + 1, WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[3] / height)) );
            SDL_RenderDrawLine( gRenderer, (WINDOW_WIDTH * (intervals[0] / width)) + 1, WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[1] / height)), (WINDOW_WIDTH * (intervals[2] / width)) + 1, WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[3] / height)) );
         }
         else
         {
            SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[0] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[1] / height)) + 1, WINDOW_WIDTH * (intervals[2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[3] / height)) + 1 );
            SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[0] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[1] / height)) - 1, WINDOW_WIDTH * (intervals[2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[3] / height)) - 1 );
         }*/

         for (i = 0; i < numberOfIntervals; ++i) //lines
         { 
            SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)) );
            if (intervals[0] == intervals[2])
            {
               SDL_RenderDrawLine( gRenderer, (WINDOW_WIDTH * (intervals[i * 8] / width)) + 1, WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), (WINDOW_WIDTH * (intervals[(i * 8) + 2] / width)) + 1, WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)) );
               SDL_RenderDrawLine( gRenderer, (WINDOW_WIDTH * (intervals[i * 8] / width)) + 1, WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), (WINDOW_WIDTH * (intervals[(i * 8) + 2] / width)) + 1, WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)) );
            }
            else
            {
               SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)) + 1, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)) + 1 );
               SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)) - 1, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)) - 1 );
            }
            if (intervals[(i * 8) + 4] != -1)
            {
               if ((intervals[i * 8] == intervals[(i * 8) + 4] && intervals[(i * 8) + 1] == intervals[(i * 8) + 5]) || (intervals[(i * 8) + 2] == intervals[(i * 8) + 6] && intervals[(i * 8) + 3] == intervals[(i * 8) + 7]))
               {
                  SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)) );
                  SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)) );
               }
               else if ((intervals[i * 8] == intervals[(i * 8) + 6] && intervals[(i * 8) + 1] == intervals[(i * 8) + 7]) || (intervals[(i * 8) + 2] == intervals[(i * 8) + 4] && intervals[(i * 8) + 3] == intervals[(i * 8) + 5]))
               {
                  SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)) );
                  SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)) );
               }
               else if ((intervals[(i * 8) + 1] - intervals[(i * 8) + 5]) / (intervals[i * 8] - intervals[(i * 8) + 4]) == (intervals[(i * 8) + 3] - intervals[(i * 8) + 7]) / (intervals[(i * 8) + 2] - intervals[(i * 8) + 6]))
               {
                  SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)) );
                  SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)) );
               }
               else if ((intervals[(i * 8) + 1] - intervals[(i * 8) + 7]) / (intervals[i * 8] - intervals[(i * 8) + 6]) == (intervals[(i * 8) + 3] - intervals[(i * 8) + 5]) / (intervals[(i * 8) + 2] - intervals[(i * 8) + 4]))
               {
                  SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)) );
                  SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)) );

		/*int filledTrigonRGBA(screen,
                     WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)),
                     WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)),
                     WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)),
                     1, 2, 3, 4);*/
               }
               else
               {
                  double A1 = intervals[(i * 8) + 3] - intervals[(i * 8) + 1];
                  double A2 = intervals[(i * 8) + 7] - intervals[(i * 8) + 5];
                  double B1 = intervals[i * 8] - intervals[(i * 8) + 2];
                  double B2 = intervals[(i * 8) + 4] - intervals[(i * 8) + 6];
                  double C1 = (A1 * intervals[i * 8]) + (B1 * intervals[(i * 8) + 1]);
                  double C2 = (A2 * intervals[(i * 8) + 4]) + (B2 * intervals[(i * 8) + 5]);
                  double d = (A1 * B2) - (A2 * B1);
                  double intersectionX = (((B2 * C1) - (B1 * C2)) / d);
                  double intersectionY = (((A1 * C2) - (A2 * C1)) / d);
                  if (intersectionX > MIN(intervals[i * 8], MIN(intervals[(i * 8) + 2], MIN(intervals[(i * 8) + 4], intervals[(i * 8) + 6]))) && intersectionX < MAX(intervals[i * 8], MAX(intervals[(i * 8) + 2], MAX(intervals[(i * 8) + 4], intervals[(i * 8) + 6]))) && intersectionY > MIN(intervals[(i * 8) + 1], MIN(intervals[(i * 8) + 3], MIN(intervals[(i * 8) + 5], intervals[(i * 8) + 7]))) && intersectionY < MAX(intervals[(i * 8) + 1], MAX(intervals[(i * 8) + 3], MAX(intervals[(i * 8) + 5], intervals[(i * 8) + 7]))))
                  {
                     SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)) );
               SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)) );
                  }
                  else
                  {
                     SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)) );
               SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)) );
                  }
               }

               /*SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)) );
               SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)) );*/
            }


            /*SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)) );
            SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)) );*/

            /*SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT * (WINDOW_HEIGHT - (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT * (WINDOW_HEIGHT - (intervals[(i * 8) + 5] / height)) );
            SDL_RenderDrawLine( gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT * (WINDOW_HEIGHT - (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT * (WINDOW_HEIGHT - (intervals[(i * 8) + 7] / height)) );*/
         }
         for (i = 0; i < numberOfIntervals; ++i) //area
         {
            if (intervals[(i * 8) + 4] != -1)
            {
                  filledTrigonRGBA(gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)), 0, 0, 255, 20);
                  filledTrigonRGBA(gRenderer, WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)), 0, 0, 255, 20);
                  filledTrigonRGBA(gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)), WINDOW_WIDTH * (intervals[i * 8] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 1] / height)), 0, 0, 255, 20);
                  filledTrigonRGBA(gRenderer, WINDOW_WIDTH * (intervals[(i * 8) + 4] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 5] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 6] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 7] / height)), WINDOW_WIDTH * (intervals[(i * 8) + 2] / width), WINDOW_HEIGHT - (WINDOW_HEIGHT * (intervals[(i * 8) + 3] / height)), 0, 0, 255, 20);
            }
         }
      }
      SDL_RenderPresent(gRenderer);
      //SDL_BlitSurface( image, NULL, screen, NULL );
      //SDL_UpdateWindowSurface( window );
   }
 }
 SDL_FreeSurface( image );
 SDL_DestroyWindow( window );
 SDL_DestroyRenderer( gRenderer );
 SDL_Quit();
 return 0;
}
