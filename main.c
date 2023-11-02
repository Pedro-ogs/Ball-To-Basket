#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GRAVITY 9.8

int width = 120;// eixo x
int height = 27;// eixo y
double basketPositionY = 13;
double basketPositionX = 105; // pra acerta usar 40 e 29 | 35 e 55 | 36 e 60 | 35 e 42
char quadra[27][120];

int game()
{
    double posiBola = 0;
    double angle, velInit;
    int positionX, positionY;
    int attempt = 0;
    int hits = 0;

    while(attempt <= 5)
    {
        system("cls");
        printf("Jogadas restantes: %d\n", 5 - attempt);
        printf("Acertos: %d\n", hits);

        //Desenhar
        desenhar(basketPositionX,basketPositionY);

        printf("\nDigite o valor do velocidade(m/s): ");
        scanf("%lf", &velInit);

        printf("Digite o valor do angulo: ");
        scanf("%lf", &angle);

        //Converter para radianos
        double angleRadians = angle *  (M_PI / 180.0);

        //tempo de voo
        double timeFlight = (2 * velInit * sin(angleRadians)) / GRAVITY;

        //calcular a posição da bola
        for(float t = 0; t < timeFlight; t += 0.25)
        {
            positionX = (velInit * cos(angleRadians) * t);
            positionY = (velInit * sin(angleRadians) * t - ((GRAVITY * t * t) / 2 ));

            //Desenha a projeção da bola
            desenharProj(positionY, positionX);

            //Verifica se acertou a cesta
            if( positionX <= basketPositionX + 1 && positionX >= basketPositionX - 1 )
            {
                if( positionY >= basketPositionY && positionY <= basketPositionY + 2 )
                {
                    hits++;
                    break;
                }
            }

        }

        int val = 0;
        while(val == 0)
        {
            printf("\n1- Aperte ESC para sair!");
            printf("\n2- Degite qualquer valor diferente de zero para continuar: ");
            scanf("%d", &val);
        }
        attempt++;
    }

    return hits;
}

void desenharProj(int positionY,int positionX)
{
    if(positionY < 26 && positionY > 0)
    {
        if(positionX <= 120 && positionX > 0)
        {
            usleep(200000);
            system("cls");
            printf("\ry:%d x:%d\n", positionY, positionX);
            quadra[26 - positionY][positionX] = '*';
            print();
        }
    }
}

void desenhar(double basketPositionX, double basketPositionY)
{
    for(int y = 0; y < height; y++)//Eixo Y
    {
        for(int x = 0; x < width; x++)//Eixo X
        {

            if(y == 0 || y == 26)
            {
                quadra[y][x]= '-';
            }
            else if(x == basketPositionX-2 && y == basketPositionY-1)
            {
                quadra[y][x]= '|';
            }
            else if(x == basketPositionX+2 && y == basketPositionY-1)
            {
                quadra[y][x]= '|';
            }
            else
            {
                quadra[y][x]= ' ';
            }
        }
    }
    int tamY,tamX;
    tamY = (int)basketPositionY;
    tamX = (int)basketPositionX;


    quadra[tamY][tamX -2] = '-';
    quadra[tamY][tamX -1] = '-';
    quadra[tamY][tamX] = '-';
    quadra[tamY][tamX +1] = '-';
    quadra[tamY][tamX +2] = '-';

    quadra[25][0] = 'J';

    print();
}

void print()
{
    for(int y = 0; y < height; y++)//Eixo Y
    {
        for(int x = 0; x < width; x++)//Eixo X
        {
            printf("%c", quadra[y][x]);
        }
    }
}

int main()
{
    int hits = game();
    printf("Numero de acertos: %d\n", hits);
    return 0;
}


