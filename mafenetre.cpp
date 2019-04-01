#include "mafenetre.h"
#include "charger_csv.h"

MaFenetre::MaFenetre(QWidget* parent) : QMainWindow(parent)
{
    this->setWindowTitle("CLASSIFICATION DES PATIENTS - PREDICTION");
    setFixedSize(1024, 768);

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

    // les deux seules valeurs possibles pour "fièvre"
    m_com->addItem("Oui");
    m_com->addItem("Non");
    m_com->addItem("NULL");

    // les deux seules valeurs possibles pour "toux"
    m_com2->addItem("Oui");
    m_com2->addItem("Non");
    m_com2->addItem("NULL");

    m_tab = new QTableWidget(this);
    m_tab->setGeometry(400, 500, 500, 320);
    m_tab->move(300, 400);
    m_tab->setRowCount(m_mat.size());
    m_tab->setColumnCount(m_vet.size());

    m_tab->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_tab->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    std::set<std::string> valeursDouleur; // pour la comboBox de douleur

    for (unsigned i=0; i < m_mat.size(); ++i)
    {
        m_tab->setItem(i, 0, new QTableWidgetItem(m_mat[i][0].c_str()));

        m_tab->setItem(i, 1, new QTableWidgetItem(m_mat[i][1].c_str()));
        valeursDouleur.insert(m_mat[i][1]);

        m_tab->setItem(i, 2, new QTableWidgetItem(m_mat[i][2].c_str()));

        m_tab->setItem(i, 3, new QTableWidgetItem(m_mat[i][3].c_str()));
        m_freqMaladie[m_mat[i][3]] += 1;
        m_valeursMaladies.insert(m_mat[i][3]);
    }

    for (const std::string& maladie : m_valeursMaladies)
        m_freqMaladie[maladie] /= m_mat.size();

    for (const std::string& valeur : valeursDouleur) // remplir la comboBox de "douleur" des valeurs possibles
        m_com1->addItem(valeur.c_str());
    m_com1->addItem("NULL");

    for (int i=0; i < m_vet.size(); ++i)
        m_tab->setHorizontalHeaderItem(i, new QTableWidgetItem(m_vet[i].c_str()));

    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->setVisible(false);
    m_tra->move(320, 300);
}

void MaFenetre::setQuitter()
{
    exit(0);
}


void MaFenetre::setPredire()
{
    string maladieResult;
    double score = 0;

    for(const string& maladie : m_valeursMaladies)
    {
        double conf1=0.0, conf2=0.0, conf3=0.0;

        for(int i=0; i < m_mat.size(); ++i)
        {
            if(m_mat[i][3] == maladie)
            {
                if(m_mat[i][0]==m_com->currentText().toStdString())
                    conf1 += 1.0;

                if(m_mat[i][1]==m_com1->currentText().toStdString())
                    conf2 += 1.0;

                if(m_mat[i][2]==m_com2->currentText().toStdString())
                    conf3 += 1.0;
            }
        }

        double freq = m_freqMaladie[maladie] * m_mat.size();

        if (m_com->currentText().toStdString() == "NULL")
            conf1 = 1;
        else
            conf1 /= freq;

        if (m_com1->currentText().toStdString() == "NULL")
            conf2 = 1;
        else
            conf2 /= freq;

        if (m_com2->currentText().toStdString() == "NULL")
            conf3 = 1;
        else
            conf3 /= freq;

        if (m_com->currentText().toStdString() == "NULL" && m_com1->currentText().toStdString() == "NULL" && m_com2->currentText().toStdString() == "NULL")
        {
            maladieResult = "Impossible de trouver la maladie";
            break;
        }

        if(m_freqMaladie[maladie] * conf1 * conf2 * conf3 > score)
        {
            maladieResult = maladie;
            score = m_freqMaladie[maladie] * conf1 * conf2 * conf3;
        }
    }

    m_tra->setText(maladieResult.c_str());
    m_tra->adjustSize();
    m_tra->setVisible(true);

    QMessageBox msgbox;
    msgbox.setText(maladieResult.c_str());
    msgbox.exec();
}
