
#include "Bouton.h"
#include <QGraphicsTextItem>
#include <QBrush>

Bouton::Bouton(Tuile position, int tailleX, int tailleY, QColor couleurBase, QColor couleurSurvole, QGraphicsItem* parent) : QGraphicsRectItem(parent) {
    couleur1 = couleurBase;
    couleur2 = couleurSurvole;
    position = position;
    setRect(HORIZONTAL_MARGIN + (position.rank * SQUARE_SIZE), VERTICAL_MARGIN + (position.file * SQUARE_SIZE), tailleX, tailleY);
    QBrush pinceau;
    pinceau.setStyle(Qt::SolidPattern);
    pinceau.setColor(couleur1);
    setBrush(pinceau);
    setAcceptHoverEvents(true);
}

void Bouton::souris(QGraphicsSceneMouseEvent* event)
{
    emit clique();
    QGraphicsRectItem::mousePressEvent(event);
}


void Bouton::survoler(QGraphicsSceneHoverEvent* event) {
    emit survol();
    QBrush pinceau(Qt::SolidPattern);
    pinceau.setColor(couleur2);
    setBrush(pinceau);
    QGraphicsRectItem::hoverEnterEvent(event);
}

Tuile Bouton::getPosition() {
    return position;
}



