//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#include "ChessPieceWidget.hpp"

ChessPieceWidget::ChessPieceWidget(QWidget* parent)
        : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    listWidget = new QListWidget(this);
    QPushButton* addButton = new QPushButton("Add Piece", this);
    QPushButton* removeButton = new QPushButton("Remove Piece", this);


    listWidget->addItem("Pawn-Black");
    listWidget->addItem("Pawn-White");
    listWidget->addItem("Rook-Black");
    listWidget->addItem("Rook-White");
    listWidget->addItem("Knight-Black");
    listWidget->addItem("Knight-White");
    listWidget->addItem("Bishop-Black");
    listWidget->addItem("Bishop-White");
    listWidget->addItem("Queen-Black");
    listWidget->addItem("Queen-White");
    listWidget->addItem("King-Black");
    listWidget->addItem("King-White");

    layout->addWidget(listWidget);
    layout->addWidget(addButton);
    layout->addWidget(removeButton);

    connect(addButton, &QPushButton::clicked, this, &ChessPieceWidget::addPiece);
    connect(removeButton, &QPushButton::clicked, this, &ChessPieceWidget::removePiece);
}

void ChessPieceWidget::addPiece()
{
    QString selectedPiece = listWidget->currentItem()->text();
    emit addPieceToBoard(selectedPiece);
}

void ChessPieceWidget::removePiece()
{
    QString selectedPiece = listWidget->currentItem()->text();
    emit removePieceFromBoard(selectedPiece);
}


QString ChessPieceWidget::getSelectedPieceName() const
{
    // Get the currently selected item from the list widget
    QListWidgetItem* selectedItem = listWidget->currentItem();

    // Return the text of the selected item as the selected piece name
    return  selectedItem->text();
}