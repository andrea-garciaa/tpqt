#include "mafenetre.h"
#include "charger_csv.h"

MaFenetre::MaFenetre(QWidget* parent) : QMainWindow(parent)
{
    this->setWindowTitle("CLASSIFICATION DES PATIENTS - PREDICTION");
    setFixedSize(800, 600);

    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(500, 300, 80, 40);

    m_pred = new QPushButton("Prédire", this);
    m_pred->setGeometry(200, 300, 80, 40);

    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(m_pred, SIGNAL(clicked()), this, SLOT(setPredire()));

    m_nom = new QLineEdit(this);
    m_nom->setGeometry(600, 50, 150, 30);

    m_prenom = new QLineEdit(this);
    m_prenom->setGeometry(600, 100, 150, 30);

    m_labnom = new QLabel("Nom : ", this);
    m_labnom->setGeometry(500, 50, 150, 30);

    m_labprenom = new QLabel("Prénom : ", this);
    m_labprenom->setGeometry(500, 100, 150, 30);

    m_lab = new QLabel("Valeur des attributs :", this);
    m_lab->setGeometry(20, 180, 150, 30);

    m_lab1 = new QLabel("Fièvre", this);
    m_lab1->setGeometry(230, 150, 100, 30);

    m_lab2 = new QLabel("Douleur", this);
    m_lab2->setGeometry(350, 150, 100, 30);

    m_lab3 = new QLabel("Toux", this);
    m_lab3->setGeometry(470, 150, 100, 30);

    m_com = new QComboBox(this);
    m_com->setGeometry(230,180,100,30);

    m_com1 = new QComboBox(this);
    m_com1->setGeometry(350,180,100,30);

    m_com2 = new QComboBox(this);
    m_com2->setGeometry(470,180,100,30);

    read_csv(m_mat, m_vet, "data.csv");

    for (int i=0; i < m_mat.size(); ++i)
        m_com->addItem(m_mat[i][0].c_str());

    for (int i=0; i < m_mat.size(); ++i)
        m_com1->addItem(m_mat[i][1].c_str());

    for (int i=0; i < m_mat.size(); ++i)
        m_com2->addItem(m_mat[i][2].c_str());

    m_tab = new QTableWidget(this);
    m_tab->move(300, 400);
    m_tab->setRowCount(m_mat.size());
    m_tab->setColumnCount(m_vet.size());

    for (unsigned i=0; i < m_mat.size(); ++i)
        for (unsigned j=0; j < m_vet.size(); ++j)
        {
            m_tab->setItem(i, j, new QTableWidgetItem(m_mat[i][j].c_str()));
            if (j == m_vet.size() - 1)
            {

            }
        }

    /*m_tra = new QLabel("this");
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->move(320, 300);*/

    connect(m_com, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(setCouleur()));
}

void MaFenetre::setQuitter()
{
    exit(0);
}


void MaFenetre::setPredire()
{
    string maladieResult;
        double score;

         for(string maladie:m_maladies){
             unsigned conf1(0);
             unsigned conf2(0);
             unsigned conf3(0);
             for(int i(0);i<m_mat.size();++i){
                 if(m_mat[i][3] == maladie){
                     if(m_mat[i][0]==m_com->currentText().toStdString()){
                        ++conf1;
                     }
                     if(m_mat[i][1]==m_com1->currentText().toStdString()){
                        ++conf2;
                     }
                     if(m_mat[i][2]==m_com2->currentText().toStdString()){
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

             if(m_com2->currentText()=="None Provided")
                 conf2=1;
             else
                 conf3=conf3/m_freqMaladie[maladie]*m_mat.size();
            if(m_freqMaladie[maladie]*conf1*conf2*conf3>score){
                maladieResult = maladie;
                score = m_freqMaladie[maladie]*conf1*conf2*conf3;
            }
         }

         if(score == 0 || (m_com1->currentText()=="None Provided" && m_com2->currentText()=="None Provided" && m_com2->currentText()=="None Provided"))
            maladieResult = "Impossible de determiner la maladie";
         else
            maladieResult = maladieResult;

         m_tra->setText(maladieResult.c_str());
         m_tra->adjustSize();
}
