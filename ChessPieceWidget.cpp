//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include <Qpixmap>
#include "ChessPieceWidget.hpp"

ChessPieceWidget::ChessPieceWidget(QWidget* parent)
        : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    QPushButton* putNewBoard = new QPushButton("Installer jeu", this);
    QPushButton* removeBoard = new QPushButton("Enlever jeu", this);
    QPushButton* undo = new QPushButton("Undo", this);
    layout->addWidget(undo);
    layout->addWidget(putNewBoard);
    layout->addWidget(removeBoard);

    connect(putNewBoard, &QPushButton::clicked, this, &ChessPieceWidget::addPiece);
    connect(removeBoard, &QPushButton::clicked, this, &ChessPieceWidget::removePiece);
}

ChessPieceWidget::~ChessPieceWidget() {
    delete listWidget;
};

void ChessPieceWidget::addPiece()
{
    QString selectedPiece = listWidget->currentItem()->text();
    emit addPieceSignal(selectedPiece);
}

void ChessPieceWidget::removePiece()
{
    QString selectedPiece = listWidget->currentItem()->text();
    emit removePieceFromBoard(selectedPiece);
}
