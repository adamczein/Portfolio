

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include "Tuile.h"
#include "Const.h"

using namespace Qt;

class Bouton : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    // Constructeurs
    Bouton(Tuile position, int tailleX, int tailleY, QColor couleurBase, QColor couleurSurvole, QGraphicsItem* parent = NULL);

    // Méthodes publiques (événements)
    void souris(QGraphicsSceneMouseEvent* event);
    void survoler(QGraphicsSceneHoverEvent* event);
    Tuile getPosition();

signals:
    void clique();
    void survol();
    void horsSurvol();

private:
    QGraphicsTextItem* texte;
    Tuile position;
    QColor couleur1;
    QColor couleur2;
};

