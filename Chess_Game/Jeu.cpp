#include "Jeu.h"
#include "qchar.h"
#include <QApplication>
#include <QGraphicsScene>
#ifdef BIBLIOTHEQUE_COURS_INCLUS
#include <bibliotheque_cours.h>
#endif
#ifdef verification_allocation
#include <verification_allocation.cpp>
#endif

#include <QApplication>

using namespace std;


namespace FrontEnd {
	Jeu::Jeu(QWidget* parent) : QGraphicsView(parent)
					{
						// Initialisation de la scène
						scene = new QGraphicsScene(this);
						// Configuration de la taille de la scène
						scene->setSceneRect(0, 0, 2000, 2000);
				
						// Initialisation de la vue
						setScene(scene);
						setRenderHint(QPainter::Antialiasing);
						setCacheMode(CacheBackground);
						setViewportUpdateMode(BoundingRectViewportUpdate);
						setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
						setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
						setFixedSize(2000, 2000);
				
						// Démarrage du jeu
						initialiserJeu();

						afficherPieces();
				
						// Affichage de la vue
						show();
					}
		
		

	void Jeu::initialiserJeu()
	{
		clicsValides = 0;

		//Réinitialisation de la matrice
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				mat[i][j] = nullptr;
			}
		}

		//Placement des pièces sur la matrice
		configurerEquipe(white);
		configurerEquipe(black);

		//Couleurs des cases
		QColor color1 = QColor(10, 61, 98, 255);   // bleu foncé
		QColor color2 = QColor(64, 112, 147, 255); // bleu pâle

		for (int i = 0; i < NB_BOX; i++)
		{
			for (int j = 0; j < NB_BOX; j++)
			{
				Tuile pos = { i,j };
				QColor color = ((i + j) % 2 == 0) ? color1 : color2;
				Bouton* playButton = new Bouton(pos, SQUARE_SIZE, SQUARE_SIZE, color, color2);
				connect(playButton, SIGNAL(Clicked()), this, SLOT(tilePressed()));
				connect(playButton, SIGNAL(Hovered()), this, SLOT(tileHover()));
				connect(playButton, SIGNAL(OffHovered()), this, SLOT(tileOffHover()));
				scene->addItem(playButton);
				boutons[i][j] = playButton;
			}
		}

		//Dessin du fond après avoir dessiné les cases
		dessinerPlateau();
	}


	void Jeu::dessinerPlateau()
	{
		//creating the sides
		QPen pen(black);
		pen.setWidth(3);

		//left side
		QGraphicsLineItem* line = new QGraphicsLineItem(HORIZONTAL_MARGIN, VERTICAL_MARGIN, HORIZONTAL_MARGIN, VERTICAL_MARGIN + NB_BOX * SQUARE_SIZE);
		line->setPen(pen);
		scene->addItem(line);

		//right side
		line = new QGraphicsLineItem(HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN, HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN + NB_BOX * SQUARE_SIZE);
		line->setPen(pen);
		scene->addItem(line);

		//top side
		line = new QGraphicsLineItem(HORIZONTAL_MARGIN, VERTICAL_MARGIN, HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN);
		line->setPen(pen);
		scene->addItem(line);

		//bottom side
		line = new QGraphicsLineItem(HORIZONTAL_MARGIN, VERTICAL_MARGIN + NB_BOX * SQUARE_SIZE, HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE, VERTICAL_MARGIN + NB_BOX * SQUARE_SIZE);
		line->setPen(pen);
		scene->addItem(line);

		//drawing players elim text
		QGraphicsTextItem* textItem = new QGraphicsTextItem("Player 1's elimination");
		textItem->setDefaultTextColor(white);
		textItem->setPos(0, VERTICAL_MARGIN - 40);
		scene->addItem(textItem);

		textItem = new QGraphicsTextItem("Player 2's elimination");
		textItem->setDefaultTextColor(white);
		textItem->setPos(HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE - 60, VERTICAL_MARGIN - 40);
		scene->addItem(textItem);

		//drawing turns 
		textItem = new QGraphicsTextItem("'s turn to play");
		textItem->setDefaultTextColor(white);
		textItem->setPos((HORIZONTAL_MARGIN + NB_BOX * SQUARE_SIZE) / 2 + 50, VERTICAL_MARGIN / 7);
		textItem->setScale(2);
		scene->addItem(textItem);

		//drawing positions
		//vertical
		for (int rank = 1; rank <= 8; rank++)
		{
			textItem = new QGraphicsTextItem(QString::number(rank));
			textItem->setDefaultTextColor(white);
			textItem->setPos(HORIZONTAL_MARGIN - 25, VERTICAL_MARGIN + SQUARE_SIZE * rank - 60);
			scene->addItem(textItem);
		}

		//horizontal
		vector<QString> tab = { "a","b","c","d","e","f","g","h" };
		for (int file = 0; file < 8; file++)
		{
			textItem = new QGraphicsTextItem(tab[file]);
			textItem->setDefaultTextColor(white);
			textItem->setPos(HORIZONTAL_MARGIN + SQUARE_SIZE * (file + 1) - 60, VERTICAL_MARGIN + NB_BOX * SQUARE_SIZE);
			scene->addItem(textItem);
		}
	}


	QGraphicsTextItem* Jeu::creerPiece(const QString& str, int file, int rank, QColor color)
	{
		QGraphicsTextItem* piece = new QGraphicsTextItem(str);
		piece->setScale(3);
		piece->setDefaultTextColor(color);
		piece->setPos(HORIZONTAL_MARGIN + SQUARE_SIZE * file, VERTICAL_MARGIN + SQUARE_SIZE * rank);
		mat[file][rank] = piece;
		return piece;
	}

	void Jeu::configurerEquipe(QColor color)
	{
		int v = 0;
		int w = 1;
		if (color == white)
		{
			v = 7;
			w = 6;
		}

		creerPiece("♛", 3, v, color);
		creerPiece("♚", 4, v, color);
		creerPiece("♝", 2, v, color);
		creerPiece("♝", 5, v, color);
		creerPiece("♞", 1, v, color);
		creerPiece("♞", 6, v, color);
		creerPiece("♜", 0, v, color);
		creerPiece("♜", 7, v, color);

		for (int i = 0; i < 8; i++)
		{
			creerPiece("♟", i, w, color);
		}
	}


	void Jeu::tuilePressee() //fction call when a button is pressed
	{
		auto obj = sender();

		// Parcourir la grille de boutons pour trouver le bouton cliqué
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (boutons[i][j] == obj)
				{
					clicsValides++;

					if (clicsValides == 1) // premier clic
					{
						if (mat[j][i] != nullptr) // si le bouton cliqué contient une pièce
						{
							derniereClickee = { j, i };
						}
						else // si le bouton cliqué est vide
						{
							clicsValides = 0;
						}
					}
					else if (clicsValides == 2) // deuxième clic
					{
						if (mat[j][i] == nullptr) // si le bouton cliqué est vide
						{
							deplacerPiece(derniereClickee, { j, i });
						}

					}
					else // clicsValides > 2
					{
						clicsValides = 0;
					}
				}
			}
		}

	}

	/*qcolor Jeu::getColor() const {
		if (color == white) {
			return Equipe::WHITE;
		}
		else {
			return Equipe::BLACK;
		}
	}
*/


	void Jeu::deplacerPiece(Tuile pos1, Tuile pos2)
	{
		if (mat[pos1.file][pos1.rank] != nullptr)
		{
			mat[pos2.file][pos2.rank] = mat[pos1.file][pos1.rank];
			mat[pos2.file][pos2.rank]->setPos(HORIZONTAL_MARGIN + SQUARE_SIZE * pos2.file, VERTICAL_MARGIN + SQUARE_SIZE * pos2.rank);
			mat[pos1.file][pos1.rank] = nullptr;
		}
		clicsValides = 0;
	}



	void Jeu::echangerPieces(Tuile pos1, Tuile pos2) //piece à pos1 chage de place avec pos2 (AKA castle)
	{
		auto temp = mat[pos2.file][pos2.rank];
		mat[pos2.file][pos2.rank] = mat[pos1.file][pos1.rank];
		mat[pos1.file][pos1.rank] = temp;
	}



	void Jeu::afficherPieces()
	{
		for (int file = 0; file < 8; file++)
		{
			for (int rank = 0; rank < 8; rank++)
			{
				if (mat[file][rank] != nullptr)
					scene->addItem(mat[file][rank]);
			}
		}
	}
}

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	FrontEnd::Jeu jeu;
	jeu.show();

	return app.exec();
}