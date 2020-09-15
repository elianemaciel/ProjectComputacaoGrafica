#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <stack>
#include <sstream>
#include <unistd.h>
#include <time.h>

using namespace std;

// Estrutura para representar pontos
typedef struct {int x, y;} Point;

// Variáveis necessárias para o SDL
unsigned int * pixels;
int width, height;
SDL_Surface * window_surface;
SDL_Renderer * renderer;

// Título da janela
std::string titulo = "SDL Random Points";

// Valores RGB para a cor de funco da janela
const int VERMELHO = 0;
const int VERDE = 0;
const int AZUL = 0;



// Gera uma estrutura Point a partir de valores para x e y
Point getPoint(int x, int y)
{
    Point p;
    p.x = x;
    p.y = y;
    return p;
}

// Obtém a cor de um pixel de uma determinada posição
Uint32 getPixel(int x, int y)
{
    if((x>=0 && x<=width) && (y>=0 && y<=height))
        return pixels[x + width * y];
    else
        return -1;
}

// Seta um pixel em uma determinada posição,
// através da coordenadas de cor r, g, b, e alpha (transparência)
// r, g, b e a variam de 0 até 255
void setPixel(int x, int y, int r, int g, int b, int a)
{
    pixels[x + y * width] = SDL_MapRGBA(window_surface->format, r, g, b, a);
}

// Seta um pixel em uma determinada posição,
// através da coordenadas de cor r, g e b
// r, g, e b variam de 0 até 255
void setPixel(int x, int y, int r, int g, int b)
{
    setPixel(x, y, r, g, b, 255);
}

// Mostra na barra de título da janela a posição
// corrente do mouse
void showMousePosition(SDL_Window * window, int x, int y)
{
    std::stringstream ss;
    ss << titulo << " X: " << x << " Y: " << y;
    SDL_SetWindowTitle(window, ss.str().c_str());
}

// Imprime na console a posição corrente do mouse
void printMousePosition(int x, int y)
{
    printf("Mouse on x = %d, y = %d\n",x,y);
}

// Seta um pixel em uma determinada posição,
// através de um Uint32 representando
// uma cor RGB
void setPixel(int x, int y, Uint32 color)
{
    if((x<0 || x>=width || y<0 || y>=height)) {
        printf("Coordenada inválida : (%d,%d)\n",x,y);
        return;
    }
    pixels[x + y * width] = color;
}

// Retorna uma cor RGB(UInt32) formada
// pelas componentes r, g, b e a(transparência)
// informadas. r, g, b e a variam de 0 até 255
Uint32 RGB(int r, int g, int b, int a) {
    return SDL_MapRGBA(window_surface->format, r, g, b, a);
}

// Retorna uma cor RGB(UInt32) formada
// pelas componentes r, g, e b
// informadas. r, g e b variam de 0 até 255
// a transparência é sempre 255 (imagem opaca)
Uint32 RGB(int r, int g, int b) {
    return SDL_MapRGBA(window_surface->format, r, g, b, 255);
}

// Retorna um componente de cor de uma cor RGB informada
// aceita os parâmetros 'r', 'R','g', 'G','b' e 'B',
Uint8 getColorComponent( Uint32 pixel, char component ) {

    Uint32 mask;

    switch(component) {
        case 'b' :
        case 'B' :
            mask = RGB(0,0,255);
            pixel = pixel & mask;
            break;
        case 'r' :
        case 'R' :
            mask = RGB(255,0,0);
            pixel = pixel & mask;
            pixel = pixel >> 16;
            break;
        case 'g' :
        case 'G' :
            mask = RGB(0,255,0);
            pixel = pixel & mask;
            pixel = pixel >> 8;
            break;
    }
    return (Uint8) pixel;
}

int rColor(){
return rand() % 256;
}
int rPositionX(){
return rand() % 640;
}

int rPositionY(){
return rand() % 480;
}
//---------------ALGORITMO DAS RETAS DE BRESENHAM -------------------------
void bresenham(int x1, int y1, int x2, int y2){

     int slope; // inclinação
     int dx, dy, incE, incNE, d, x, y;
     // Onde inverte a linha x1 > x2
     if (x1 > x2){
        bresenham(x2, y2, x1, y1);
     return;
     }
     dx = x2 - x1;
     dy = y2 - y1;

     if (dy < 0){
        slope = -1;
        dy = -dy;
     }
     else{
        slope = 1;
     }
    // Constante de Bresenham
     incE = 2 * dy; // shift-left
     incNE = 2 * dy - 2 * dx;
     d = 2 * dy - dx;
     y = y1;
     for (x = x1; x <= x2; x++){
        setPixel( x, y, RGB(255,0,0) );
        if (d <= 0){
            d += incE;
        }
        else{
            d += incNE;
            y += slope;
        }
     }
 }
 //----------- XIAOLIN -----------------
 void swap(int* a, int* b){
 int temp = *a;
 *a = *b;
 *b = temp;
 }
int iPartOfNumber(float x){
    return (int)x;
 }

 float fPartOfNumber(float x){
    if(x>0) return x - iPartOfNumber(x);
    else return x - (iPartOfNumber(x)+1);
 }

 float absolute(float x){
    if(x<0) return -x;
    else return x;
 }



 float rfPartOfNumber(float x){
 return 1 - fPartOfNumber(x);
 }

//--------- ALGORITMO DE DESENHO DE RETAS ----------
// PARAMS (X0 E YO = PONTO INICIAL)
//        (X1 E Y1 = PONTO FINAL)
void drawWuLine(int x0, int y0, int x1, int y1, Uint32 clrLine )
{
    /* Make sure the line runs top to bottom */
    if (y0 > y1)
    {
        int aux = y0; y0 = y1; y1 = aux;
        aux = x0; x0 = x1; x1 = aux;
    }

    /* Draw the initial pixel, which is always exactly intersected by
    the line and so needs no weighting */
    setPixel( x0, y0, clrLine );

    int xDir, deltaX = x1 - x0;
    if( deltaX >= 0 )
    {
        xDir = 1;
    }
    else
    {
        xDir   = -1;
        deltaX = 0 - deltaX; /* make deltaX positive */
    }

    /* Special-case horizontal, vertical, and diagonal lines, which
    require no weighting because they go right through the center of
    every pixel */
    int deltaY = y1 - y0;
    if (deltaY == 0)
    {
        /* Horizontal line */
        while (deltaX-- != 0)
        {
            x0 += xDir;
            setPixel( x0, y0, clrLine );
        }
        return;
    }
    if (deltaX == 0)
    {
        /* Vertical line */
        do
        {
            y0++;
            setPixel( x0, y0, clrLine );
        } while (--deltaY != 0);
        return;
    }

    if (deltaX == deltaY)
    {
        /* Diagonal line */
        do
        {
            x0 += xDir;
            y0++;
            setPixel( x0, y0, clrLine );
        } while (--deltaY != 0);
        return;
    }

    unsigned short errorAdj;
    unsigned short errorAccaux, weighting;

    /* Line is not horizontal, diagonal, or vertical */
    unsigned short errorAcc = 0;  /* initialize the line error accumulator to 0 */

    Uint32 rl = getColorComponent( clrLine, 'r' );
    Uint32 gl = getColorComponent( clrLine, 'g' );
    Uint32 bl = getColorComponent( clrLine, 'b' );
    double grayl = rl * 0.299 + gl * 0.587 + bl * 0.114;

    /* Is this an X-major or Y-major line? */
    if (deltaY > deltaX)
    {
    /* Y-major line; calculate 16-bit fixed-point fractional part of a
    pixel that X advances each time Y advances 1 pixel, truncating the
        result so that we won't overrun the endpoint along the X axis */
        errorAdj = ((unsigned long) deltaX << 16) / (unsigned long) deltaY;
        /* Draw all pixels other than the first and last */
        while (--deltaY) {
            errorAccaux = errorAcc;   /* remember currrent accumulated error */
            errorAcc += errorAdj;      /* calculate error for next pixel */
            if (errorAcc <= errorAccaux) {
                /* The error accumulator turned over, so advance the X coord */
                x0 += xDir;
            }
            y0++; /* Y-major, so always advance Y */
                  /* The IntensityBits most significant bits of errorAcc give us the
                  intensity weighting for this pixel, and the complement of the
            weighting for the paired pixel */
            weighting = errorAcc >> 8;
            /*
            ASSERT( weighting < 256 );
            ASSERT( ( weighting ^ 255 ) < 256 );
            */
            Uint32 clrBackGround = getPixel(x0, y0 );
            Uint8 rb = getColorComponent( clrBackGround, 'r' );
            Uint8 gb = getColorComponent( clrBackGround, 'g' );
            Uint8 bb = getColorComponent( clrBackGround, 'b' );
            double grayb = rb * 0.299 + gb * 0.587 + bb * 0.114;

            Uint8 rr = ( rb > rl ? ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( rb - rl ) + rl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( rl - rb ) + rb ) ) );
            Uint8 gr = ( gb > gl ? ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( gb - gl ) + gl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( gl - gb ) + gb ) ) );
            Uint8 br = ( bb > bl ? ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( bb - bl ) + bl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( bl - bb ) + bb ) ) );
            setPixel( x0, y0, RGB( rr, gr, br ) );

            clrBackGround = getPixel(x0 + xDir, y0 );
            rb = getColorComponent( clrBackGround, 'r' );
            gb = getColorComponent( clrBackGround, 'g' );
            bb = getColorComponent( clrBackGround, 'b' );
            grayb = rb * 0.299 + gb * 0.587 + bb * 0.114;

            rr = ( rb > rl ? ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( rb - rl ) + rl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( rl - rb ) + rb ) ) );
            gr = ( gb > gl ? ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( gb - gl ) + gl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( gl - gb ) + gb ) ) );
            br = ( bb > bl ? ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( bb - bl ) + bl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( bl - bb ) + bb ) ) );
            setPixel( x0 + xDir, y0, RGB( rr, gr, br ) );
        }
        /* Draw the final pixel, which is always exactly intersected by the line
        and so needs no weighting */
        setPixel( x1, y1, clrLine );
        return;
    }
    /* It's an X-major line; calculate 16-bit fixed-point fractional part of a
    pixel that Y advances each time X advances 1 pixel, truncating the
    result to avoid overrunning the endpoint along the X axis */
    errorAdj = ((unsigned long) deltaY << 16) / (unsigned long) deltaX;
    /* Draw all pixels other than the first and last */
    while (--deltaX) {
        errorAccaux = errorAcc;   /* remember currrent accumulated error */
        errorAcc += errorAdj;      /* calculate error for next pixel */
        if (errorAcc <= errorAccaux) {
            /* The error accumulator turned over, so advance the Y coord */
            y0++;
        }
        x0 += xDir; /* X-major, so always advance X */
                    /* The IntensityBits most significant bits of errorAcc give us the
                    intensity weighting for this pixel, and the complement of the
        weighting for the paired pixel */
        weighting = errorAcc >> 8;
        /*
        ASSERT( weighting < 256 );
        ASSERT( ( weighting ^ 255 ) < 256 );
        */
        Uint32 clrBackGround = getPixel(x0, y0 );
        Uint8 rb = getColorComponent( clrBackGround, 'r' );
        Uint8 gb = getColorComponent( clrBackGround, 'g' );
        Uint8 bb = getColorComponent( clrBackGround, 'b' );
        double grayb = rb * 0.299 + gb * 0.587 + bb * 0.114;

        Uint8 rr = ( rb > rl ? ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( rb - rl ) + rl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( rl - rb ) + rb ) ) );
        Uint8 gr = ( gb > gl ? ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( gb - gl ) + gl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( gl - gb ) + gb ) ) );
        Uint8 br = ( bb > bl ? ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( bb - bl ) + bl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?weighting:(weighting ^ 255)) ) / 255.0 * ( bl - bb ) + bb ) ) );

        setPixel( x0, y0, RGB( rr, gr, br ) );

        clrBackGround = getPixel(x0, y0 + 1 );
        rb = getColorComponent( clrBackGround, 'r' );
        gb = getColorComponent( clrBackGround, 'g' );
        bb = getColorComponent( clrBackGround, 'b' );
        grayb = rb * 0.299 + gb * 0.587 + bb * 0.114;

        rr = ( rb > rl ? ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( rb - rl ) + rl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( rl - rb ) + rb ) ) );
        gr = ( gb > gl ? ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( gb - gl ) + gl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( gl - gb ) + gb ) ) );
        br = ( bb > bl ? ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( bb - bl ) + bl ) ) : ( ( Uint8 )( ( ( double )( grayl<grayb?(weighting ^ 255):weighting) ) / 255.0 * ( bl - bb ) + bb ) ) );

        setPixel( x0, y0 + 1, RGB( rr, gr, br ) );
    }

    /* Draw the final pixel, which is always exactly intersected by the line
    and so needs no weighting */
    setPixel( x1, y1, clrLine );
}
//--------- ALGORITMO DE Liang-Barsky ----------
void drawClippedLine(int xmin, int ymin, int xmax, int ymax,
    int x1, int y1, int x2, int y2, Uint32 color){

    int xx1,xx2,yy1,yy2,dx,dy;
	float t1,t2,p[4],q[4],temp;

	dx=x2-x1;
	dy=y2-y1;

	p[0]=-dx;
	p[1]=dx;
	p[2]=-dy;
	p[3]=dy;

	q[0]=x1-xmin;
	q[1]=xmax-x1;
	q[2]=y1-ymin;
	q[3]=ymax-y1;

	for(int i=0;i<4;i++)
	{
		if(p[i]==0)
		{
			//  line is parallel to one of the clipping boundary
			if(q[i]>=0)
			{
				if(i<2)
				{
					if(y1<ymin)
					{
						y1=ymin;
					}

					if(y2>ymax)
					{
						y2=ymax;
					}

					drawWuLine(x1,y1,x2,y2, color);
				}

				if(i>1)
				{
					if(x1<xmin)
					{
						x1=xmin;
					}

					if(x2>xmax)
					{
						x2=xmax;
					}

					drawWuLine(x1,y1,x2,y2, color);
				}
			}
		}
	}

	t1=0;
	t2=1;

	for(int i=0;i<4;i++)
	{
		temp=q[i]/p[i];

		if(p[i]<0)
		{
			if(t1<=temp)
				t1=temp;
		}
		else
		{
			if(t2>temp)
				t2=temp;
		}
	}

	if(t1<t2)
	{
		xx1 = x1 + t1 * p[1];
		xx2 = x1 + t2 * p[1];
		yy1 = y1 + t1 * p[3];
		yy2 = y1 + t2 * p[3];
		drawWuLine(xx1,yy1,xx2,yy2, color);
	}

}

//--------- ALGORITMO DE DESENHO DE RETAS ----------
// PARAMS (X0 E YO = PONTO INICIAL)
//        (X1 E Y1 = PONTO FINAL)
void xiaolin(int x0, int y0, int x1, int y1, Uint32 color){

    int steep = absolute(y1 - y0) > absolute(x1 - x0);


    if(steep){
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if(x0 > x1){
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    float dx = x1-x0;
    float dy = y1-y0;
    float gradient = dy/dx;
    if(dx==0.0)
        gradient=1;

    int xpxl1 = x0;
    int xpxl2 = x1;
    float intersectY = y0;

    if(steep){
        int x;
        for(x=xpxl1;x<=xpxl2; x++){
           setPixel(iPartOfNumber(intersectY), x,  RGB(rColor(),rColor(),rColor(),rfPartOfNumber(intersectY)) );
           setPixel(iPartOfNumber(intersectY)-1, x,  RGB(rColor(),rColor(),rColor(),fPartOfNumber(intersectY)) );

           intersectY+= gradient;
        }
    }else{
        int x;
        for(x=xpxl1;x<=xpxl2; x++){
           setPixel( x, iPartOfNumber(intersectY), RGB(rColor(),rColor(),rColor(),rfPartOfNumber(intersectY)) );
           setPixel( x, iPartOfNumber(intersectY)-1, RGB(rColor(),rColor(),rColor(),fPartOfNumber(intersectY)) );

           intersectY+= gradient;
        }

    }

 }
 void xiaolin(int x0, int y0, int x1, int y1){

    int steep = absolute(y1 - y0) > absolute(x1 - x0);


    if(steep){
        swap(&x0, &y0);
        swap(&x1, &y1);
    }
    if(x0 > x1){
        swap(&x0, &x1);
        swap(&y0, &y1);
    }

    float dx = x1-x0;
    float dy = y1-y0;
    float gradient = dy/dx;
    if(dx==0.0)
        gradient=1;

    int xpxl1 = x0;
    int xpxl2 = x1;
    float intersectY = y0;

    if(steep){
        int x;
        for(x=xpxl1;x<=xpxl2; x++){
           setPixel(iPartOfNumber(intersectY), x,  RGB(rColor(),rColor(),rColor(),rfPartOfNumber(intersectY)) );
           setPixel(iPartOfNumber(intersectY)-1, x,  RGB(rColor(),rColor(),rColor(),fPartOfNumber(intersectY)) );

           intersectY+= gradient;
        }
    }else{
        int x;
        for(x=xpxl1;x<=xpxl2; x++){
           setPixel( x, iPartOfNumber(intersectY), RGB(rColor(),rColor(),rColor(),rfPartOfNumber(intersectY)) );
           setPixel( x, iPartOfNumber(intersectY)-1, RGB(rColor(),rColor(),rColor(),fPartOfNumber(intersectY)) );

           intersectY+= gradient;
        }

    }

 }
//--------- DESENHA UMA ELIPSE ----------
// PARAMS (X0 E Y0 = CENTRO)
//        (raioX E raioY = DISTANCIA DO CENTRO ATE AS BORDAS)
void desenhaCirc(int x0, int y0, int raioX, int raioY){
 const float PI = 3.14159265358979323846;
 const float MPI= PI/2;

 const int prec = 27;

 float theta = 0;

 int x = (float)raioX * cos(theta);
 int y = (float)raioY * sin(theta);

 int x1 = x;
 int y1 = y;

 float step = MPI/(float)prec;
 for(theta = step; theta <= MPI; theta+=step){
    x1 = (float)raioX * cosf(theta) + 0.5;
    y1 = (float)raioY * sinf(theta) + 0.5;

    if( (x != x1) || (y != y1)){
       xiaolin(x0 + x, y0 - y, x0 + x1, y0 - y1);
       xiaolin(x0 - x, y0 - y, x0 - x1, y0 - y1);
       xiaolin(x0 - x, y0 + y, x0 - x1, y0 + y1);
       xiaolin(x0 + x, y0 + y, x0 + x1, y0 + y1);

    }
    x = x1;
    y = y1;
 }
 if(x!=0){
        x=0;
        xiaolin(x0 + x, y0 - y, x0 + x1, y0 - y1);
        xiaolin(x0 - x, y0 - y, x0 - x1, y0 - y1);
        xiaolin(x0 - x, y0 + y, x0 - x1, y0 + y1);
        xiaolin(x0 + x, y0 + y, x0 + x1, y0 + y1);
    }
}
//--------- DESENHA UM RETÂGULO ----------
// PARAMS (X1 E Y1 = PONTO INICIAL)
//        (X2 E Y2 = PONTO FINAL)
void desenhaRet(int x1, int y1,int x2, int y2){

    xiaolin(x1,y1,x2,y1);
    xiaolin(x2,y1,x2,y2);
    xiaolin(x2,y2,x1,y2);
    xiaolin(x1,y2,x1,y1);

}
void desenhaRet(int x1, int y1,int x2, int y2, Uint32 color){

    drawWuLine(x1,y1,x2,y1,color);
    drawWuLine(x2,y1,x2,y2,color);
    drawWuLine(x2,y2,x1,y2,color);
    drawWuLine(x1,y2,x1,y1,color);

}
//--------- DESENHA UM POLIGONO ----------

void desenhaPlg(Point p[], int qtd, Uint32 color){

    for(int i=0; i<qtd;i++){
        Point pi = p[i];
        Point pf;

        if(i==qtd-1)
        pf = p[0];
        else
        pf = p[i+1];

        drawWuLine(pi.x,pi.y,pf.x,pf.y,color);

    }

}

void desenhaCoracao(){
    Point p[10];
    p[0]=getPoint(320,136);
    p[1]=getPoint(390,70);
    p[2]=getPoint(496,90);
    p[3]=getPoint(541,180);
    p[4]=getPoint(510,315);
    p[5]=getPoint(320,463);
    p[6]=getPoint(130,315);
    p[7]=getPoint(99,180);
    p[8]=getPoint(143,90);
    p[9]=getPoint(249,70);

    desenhaPlg(p,10,RGB(255,124,100));

}

//--------- DESENHA UM RETÂGULO PERSONALIZADO ----------
void desenhaRet2(int x1,int x2, int x3, int x4,int y1, int y2, int y3){

    xiaolin(x1,y2,x2,y1);
    xiaolin(x2,y1,x4,y2);
    xiaolin(x4,y2,x3,y3);
    xiaolin(x3,y3,x1,y2);

}

void desenhaCasa(){
    //Retangulo de baixo
    desenhaRet(40,200, 280,320);
    //Telhado
    xiaolin(40,200, 160,100);
    xiaolin(160,100,280,200);
    //janelas
    desenhaRet(80,220, 110,250);
    desenhaRet(210,220, 240,250);
    //Porta
    desenhaRet(145,270,175,320);
    //Soleira
    desenhaCirc(160,160,20,20);
    xiaolin(146,175, 174,145);
    xiaolin(146,145, 174,175);

    //Arvore
     xiaolin(440,160, 440,320);
     xiaolin(500,160, 500,320);
     desenhaCirc(470,100,70,70);
     desenhaCirc(400,150,50,50);
     desenhaCirc(540,150,50,50);
     desenhaCirc(410,100,40,40);
     desenhaCirc(530,100,40,40);
}
void desenhaLinhas()
{

        bresenham(200,0,639,280);

        xiaolin(0,200,415,479);
}

// Aqui ocorrem as chamadas das funções a ser exibidas na janela
void display()
{
    //DESENHA RET E LINHA E LINHA LIMITADA POR RET
//    desenhaRet(100,100,400,220,RGB(0,255,0));
//    drawWuLine(120,70,390,230,RGB(0,0,255));
//    drawClippedLine(100,100,400,220,120,70,390,230,RGB(255,0,0));
    desenhaCoracao();


}





void displayRand()
{

        for(int i=0;i<10000;i++){
            setPixel( rPositionX(), rPositionY(), RGB(rColor(),rColor(),rColor()) );
        }


}



// Inicializa o SDL, abre a janela e controla o loop
// principal do controle de eventos
int main()
{
    // Inicializações iniciais obrigatórias
    srand (time(NULL));
    setlocale(LC_ALL, NULL);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window * window = SDL_CreateWindow(titulo.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        640, 480,
        SDL_WINDOW_RESIZABLE);

    window_surface = SDL_GetWindowSurface(window);

    pixels = (unsigned int *) window_surface->pixels;
    width = window_surface->w;
    height = window_surface->h;

    // Fim das inicializações

    printf("Pixel format: %s\n",
        SDL_GetPixelFormatName(window_surface->format->format));

     while (1)
    {

        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                exit(0);
            }

            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    window_surface = SDL_GetWindowSurface(window);
                    pixels = (unsigned int *) window_surface->pixels;
                    width = window_surface->w;
                    height = window_surface->h;
                    printf("Size changed: %d, %d\n", width, height);
                }
            }

            // Se o mouse é movimentado
            if(event.type == SDL_MOUSEMOTION)
            {
                // Mostra as posições x e y do mouse
                showMousePosition(window,event.motion.x,event.motion.y);
            }
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
				/*Se o botão esquerdo do mouse é pressionado */
                if(event.button.button == SDL_BUTTON_LEFT)
				{
					printf("Mouse pressed on (%d,%d)\n",event.motion.x,event.motion.y) ;
				}
            }
        }

        // Seta a cor de fundo da janela para a informada nas
        // constantes VERMELHO, VERDE e AZUL
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                setPixel(x, y, RGB(VERMELHO,VERDE,AZUL));
            }
        }

        display();

        SDL_UpdateWindowSurface(window);
    }
}