#include "MaFenetre.h"
#include <QSet>
#include<QVBoxLayout>
#include<QHeaderView>

MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent)
{
    read_csv (m_mat, m_vet, "/home/p16001500/build-ecbd-Desktop-Debug/data.csv");

    setFixedSize(800,600);  

    m_com1= new QComboBox(this);
    m_com1->move(200,50);
    initComboBox(0,m_com1);

    m_com2= new QComboBox(this);
    m_com2->move(m_com1->x()+140,m_com1->y());
    initComboBox(1,m_com2);

    m_com3= new QComboBox(this);
    m_com3->move(m_com2->x()+140,m_com1->y());
    initComboBox(2,m_com3);

    m_bou = new QPushButton("Predire", this);
    m_bou->move(m_com1->x()-50,m_com1->y()+50);
    m_bou->adjustSize();

    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->move(m_bou->x()+100,m_bou->y());

    m_tab = new QTableWidget(this);
    m_tab->move(10,m_bou->y()+100);
    m_tab->setRowCount(m_mat.size());
    m_tab->setColumnCount(m_vet.size());


    for(unsigned i(0);i<m_mat.size();++i)
        for(unsigned j(0);j<m_vet.size();++j){
            m_tab->setItem(i,j,new QTableWidgetItem(m_mat[i][j].c_str()));
            if(j == m_vet.size()-1){
                m_freqMaladie[m_mat[i][j]]=m_freqMaladie.at(m_mat[i][j])+1;
                m_maladies.insert(m_mat[i][j]);
            }
    }

    for (string x : m_maladies)
        m_freqMaladie[x] = m_freqMaladie[x]/m_mat.size();


    for(unsigned i(0);i<m_vet.size();++i){
        m_tab->setHorizontalHeaderItem(i,new QTableWidgetItem(m_vet[i].c_str()));
        m_tab->horizontalHeader()->setStretchLastSection(true);

    }


    m_tab->setMinimumSize(750,400);


    // Associer signaux et les slots
    connect(m_bou,SIGNAL(clicked(bool)),this,SLOT(setPredire()));
}

string MaFenetre::getPrediction(){
// fréquence maladie * conf de symptome avec sa maladie
    string maladieResult;
    double score;

     for(string maladie:m_maladies){
         unsigned conf1(0);
         unsigned conf2(0);
         unsigned conf3(0);
         for(int i(0);i<m_mat.size();++i){
             if(m_mat[i][3] == maladie){
                 if(m_mat[i][0]==m_com1->currentText().toStdString()){
                    ++conf1;
                 }
                 if(m_mat[i][1]==m_com2->currentText().toStdString()){
                    ++conf2;
                 }
                 if(m_mat[i][2]==m_com3->currentText().toStdString()){
                    ++conf3;
                 }
             }
         }
         if(m_com1->currentText()=="None Provided")
             conf1=1;
         else
             conf1=conf1/m_freqMaladie[maladie]*m_mat.size();

         if(m_com2->currentText()=="None Provided")
             conf2=1;
         else
             conf2=conf2/m_freqMaladie[maladie]*m_mat.size();

         if(m_com3->currentText()=="None Provided")
             conf3=1;
         else
             conf3=conf3/m_freqMaladie[maladie]*m_mat.size();
        if(m_freqMaladie[maladie]*conf1*conf2*conf3>score){
            maladieResult = maladie;
            score = m_freqMaladie[maladie]*conf1*conf2*conf3;
        }
     }
     if(score == 0 || (m_com1->currentText()=="None Provided" && m_com2->currentText()=="None Provided" && m_com3->currentText()=="None Provided"))
         return "Impossible de determiner la maladie";
     return maladieResult;
}

void MaFenetre::setPredire(){
    m_tra->setText(this->getPrediction().c_str());
    m_tra->adjustSize();
}


void MaFenetre::initComboBox(int column,QComboBox* m_box){

    m_lab = new QLabel (m_vet[column].c_str(),this);
    m_lab->setFont(QFont("Verdana",12));
    QStringList list;
    list.append("None Provided");
    for(unsigned i(0); i < m_mat.size();++i){
        list.append(m_mat[i][column].c_str());
    }
    list.removeDuplicates();
    m_box->addItems(list);
    m_box->adjustSize();
    m_lab->move(m_box->x()+5,m_box->y()-20);
    m_lab->adjustSize();
}
