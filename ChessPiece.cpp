//Lucas Guevremont et William Faraoni
//2300275 et 2301401
//INF1015
//École Polytechnique de Montréal
//Projet Final de INF1015


#pragma once

#include "ChessPiece.hpp"

ChessPiece::ChessPiece(QObject* parent) : QObject(parent)
{
}

QPixmap ChessPiece::pixmap() const
{
    return m_pixmap;
}

void ChessPiece::setPixmap(const QPixmap& pixmap)
{
    m_pixmap = pixmap;
}

void ChessPiece::setPosition(const QPoint& position)
{
    m_position = position;
}

QPoint ChessPiece::position() const
{
    return m_position;
}