//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015

#include <QWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QPushButton>

#include "ChessPieceWidget.hpp"

ChessPieceWidget::ChessPieceWidget(QWidget* parent = nullptr)
        : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QListWidget* listWidget = new QListWidget(this);
        QPushButton* addButton = new QPushButton("Add Piece", this);
        QPushButton* removeButton = new QPushButton("Remove Piece", this);


        listWidget->addItem("Pawn");
        listWidget->addItem("Rook");
        listWidget->addItem("Knight");
        listWidget->addItem("Bishop");
        listWidget->addItem("Queen");
        listWidget->addItem("King");

        layout->addWidget(listWidget);
        layout->addWidget(addButton);
        layout->addWidget(removeButton);

        connect(addButton, &QPushButton::clicked, this, &ChessPieceWidget::addPiece);
        connect(removeButton, &QPushButton::clicked, this, &ChessPieceWidget::removePiece);
    }


    void ChessPieceWidget::addPiece()
    {

    }

    void ChessPieceWidget::removePiece()
    {
    }
};