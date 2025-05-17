#pragma warning(push, 0) // Sinon Qt fait des avertissements à /W4.
#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QList> 
#include <QPointF> 
#include <QPixmap>
#include <QString>
#include <QPushButton>
#include <QMouseEvent>
#include <QMessageBox>
#include <cppitertools/range.hpp>
#include <cppitertools/zip.hpp>
#include <cppitertools/enumerate.hpp>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QBrush>
#include <QColor>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

#include "Tuile.h"
#include "Bouton.h"


#pragma warning(pop)



namespace FrontEnd {
	class Jeu : public QGraphicsView {
		Q_OBJECT
	public:
		void tuilePressee();
		QGraphicsView* vue;
		QGraphicsScene* scene;
		QGraphicsTextItem* mat[8][8];
		Bouton* boutons[8][8];
		Tuile temp;
		Tuile derniereClickee;

	/*	QColor getColor() const;*/
		Jeu(QWidget* parent = nullptr);
		~Jeu() override = default;
		void initialiserJeu();
		void afficherPieces();
		void configurerEquipe(QColor couleur);
		void deplacerPiece(Tuile pos1, Tuile pos2);
		void echangerPieces(Tuile pos1, Tuile pos2);
		void dessinerPlateau();
		QGraphicsTextItem* creerPiece(const QString& str, int file, int rank, QColor color);
		int clicsValides;
	};

		
	};
