#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PaperSticher.h"

class PaperSticher : public QMainWindow
{
    Q_OBJECT

public:
    PaperSticher(QWidget *parent = nullptr);
    ~PaperSticher();

private slots:
    void on_stich_btn_clicked();

private:
    Ui::PaperSticherClass ui;
};
