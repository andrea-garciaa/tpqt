#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QComboBox>
#include <QTableWidget>
#include <charger_csv.h>
#include <vector>
#include <set>


class MaFenetre : public QMainWindow
{
    Q_OBJECT
public:
    explicit MaFenetre(QWidget *parent = 0);

private:
    QLabel *m_lab, *m_tra;
    QPushButton *m_bou;
    QComboBox *m_com1,*m_com2,*m_com3;
    QString couleur;
    CVString m_vet;
    CMatString m_mat;
    QTableWidget *m_tab;
    map<string,double> m_freqMaladie;
    set<string> m_maladies;

    void initComboBox(int column, QComboBox *m_box);

    string getPrediction();
signals:

public slots:
    void setPredire();
};

#endif // MAFENETRE_H
