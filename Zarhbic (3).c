#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum Bool{
    false,
    true
}Bool;

void affichageErreur(int erreurExpression)
{
    if(erreurExpression == 1)
    {
        printf("le calcul doit finir par un opérateur.\n");
    }

    if(erreurExpression == 2)
    {
        printf("le calcul doit comporter n-1 opérateur; n désignant le nombre de nombres.\n");
    }

    if(erreurExpression == 3)
    {
        printf("le calcul ne doit pas comporter de caractères autres que des chiffres, espaces et opérateurs(+ - * /).\n");
    }   
}

void affichageResultat(float resultat)
{
    printf("Le résultat de l'expression est %f", resultat);
}

void affichageZarhbic(int expressionValide, float resultat)
{
    if(expressionValide == 0)
    {
        affichageResultat(resultat);
    }
    else
    {
        affichageErreur(expressionValide);
    }
}

Bool verifDivisionParZero(int operande)
{
    Bool valide = true;

    if(operande == 0)
    {
        valide = false;
    }

    return valide;
}

Bool estUnEspace(char caractere)
{
    Bool OkEspace = false;

    if(caractere == ' ' || caractere == '\n' || caractere == '\t')
    {
        OkEspace = true;
    }

    return OkEspace;
}

Bool estUnNombre(char caractere)
{
    Bool okNombre = false;

    if(caractere >= '0' && caractere <= '9')
    {
        okNombre = true;
    }

    return okNombre;
}

Bool estUnOperateur(char caractere)
{
    Bool okOperateur = false;

    if(caractere == '+' || caractere == '-' || caractere == '/' || caractere == '*')
    {
        okOperateur = true;
    }

    return okOperateur;
}

Bool verifFinCalcul(char* expression)
{
    long tailleExpression = strlen(expression) - 1;
    Bool okFinCalcul = false;

    if(estUnOperateur(expression[tailleExpression]))
    {
        okFinCalcul = true;
    }

    return okFinCalcul;
}

Bool verifExpressionCalcul(char* calcul)
{
    int nombreOperateur= 0;
    int nombreDeNombre = 0;
    long indice;
    long tailleCalcul = strlen(calcul);
    Bool expressionOk = false;

    for(indice = 0; indice < tailleCalcul; indice++)
    {
        if(estUnOperateur(calcul[indice]))
        {
            nombreOperateur++;
        }
        else
        {
            if(!estUnEspace(calcul[indice]))
            {
                nombreDeNombre++;
            }
        }
    }

    if(nombreOperateur == nombreDeNombre-1)
    {
        expressionOk = true;
    }

    return expressionOk;
}


Bool verifPasAlpha(char* expression)
{
    long indice;
    long tailleExpression = strlen(expression);
    Bool alphaOK = true;

    for(indice = 0; indice < tailleExpression; indice++)
    {
        if(!estUnNombre(expression[indice]) && !estUnEspace(expression[indice]) && !estUnOperateur(expression[indice]))
        {
            alphaOK = false;
        }
    }
    
    return alphaOK;
}

int postVerification(char* calcul)
{
    int expressionValide = 0;
    
    if(!verifFinCalcul(calcul)){
        expressionValide = 1; //si en fin de calcul il y a autre chose qu'un opérateur 
    }
    
    if(!verifExpressionCalcul(calcul)){
        expressionValide = 2; //si le nombre d'opérateur et d'opérande est invalide
    }
    
    if(!verifPasAlpha(calcul)){
        expressionValide = 3; //si l'expression contient autre chose que des opérateurs, opérandes ou espaces
    }

    return expressionValide;
}

void saisie(char* expression)
{
    char* positionDeEntre = NULL;
    printf("saisir un calcul\n");
    fgets(expression, 99, stdin);

    positionDeEntre = strchr(expression, '\n');
    
    if(positionDeEntre != NULL)
    {
        *positionDeEntre = '\0';
    }
}

int saisieExpression(char* expression)
{
    int expressionValide;
    saisie(expression);
    expressionValide = postVerification(expression);

    return expressionValide;
}

float traitementOperateur(char operateur, float operande1, float operande2)
{
    float resultat = 0;

    switch (operateur) 
    {
        case '+':
            resultat = operande1 + operande2;
        break;

        case '-':
            resultat = operande1 - operande2;
        break;

        case '*':
            resultat = operande1 * operande2;
        break;

        case '/':
            if(verifDivisionParZero(operande2))
            {
                resultat = operande1 / operande2;
            }
            else
            {
                printf("l'opération annulée car une division par 0 est effectuée.\n");
                exit(-1);
            }
        break;

        default : printf("opérateur invalide");
    }

    return resultat;
}

float calculZarhbic(char* leCalcul) {
    float pile[100];
    int haut = -1;
    char *expressionCalcul = leCalcul;
    float nombre;

    while(*expressionCalcul)
    {
        if(estUnEspace(*expressionCalcul))
        {
            expressionCalcul++;
        }

        if (estUnNombre(*expressionCalcul)) 
        {
            //soustrait le code ASCII du caractère 0 au code ASCII du nombre qui aussi est un caractère
            //permet de "caster" plus facilement les nombres de l'expression
            nombre = *expressionCalcul - '0';

            while (estUnNombre(*++expressionCalcul)) 
            {
                nombre = nombre * 10 + (*expressionCalcul - '0');
            }

            pile[++haut] = nombre;
        } 
        else 
        {
            float operande2 = pile[haut--];
            float operande1 = pile[haut--];
            pile[++haut] = traitementOperateur(*expressionCalcul, operande1, operande2);
            expressionCalcul++;
        }
    }

    return pile[haut];
}

int main() 
{
    //system("chcp 65001");
    int expressionValide;
    float resultatCalcul;
    char leCalcul[100];
    expressionValide = saisieExpression(leCalcul);
    resultatCalcul = calculZarhbic(leCalcul);
    affichageZarhbic(expressionValide, resultatCalcul);
    return 0;
}