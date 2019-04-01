#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>


#include <map>
#include <vector>
#include <set>


#include "charger_csv.h"

class MaFenetre : public QMainWindow
{
    Q_OBJECT

public:
    MaFenetre(QWidget* parent);

public slots:
    void setQuitter();
    void setPredire();

private:
    QPushButton* m_bou;
    QPushButton* m_pred;

    QLineEdit* m_nom;
    QLineEdit* m_prenom;
    QLabel* m_labnom;
    QLabel* m_labprenom;

    QLabel* m_lab;
    QLabel* m_lab1;
    QLabel* m_lab2;
    QLabel* m_lab3;
    QLabel* m_maladie;

    QLabel* m_tra;
    QComboBox* m_com;
    QComboBox* m_com1;
    QComboBox* m_com2;

    QTableWidget* m_tab;

    CVString m_vet;
    CMatString m_mat;

    std::map<std::string, double> m_freqMaladie;
    std::set<std::string> m_valeursMaladies; // noms possibles de maladies

};

#endif // MAFENETRE_H
