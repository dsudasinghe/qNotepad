#include "notepad.h"
#include "ui_notepad.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>
#include <QDate>
#include <QTime>

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);

    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}




//-----------------Action button triggers-----------------------
//new file method
void Notepad::on_actionNew_triggered()
{
    file_path_ = "";//clear file path
    ui-> textEdit->setText("");//clear text
}

//open file method
void Notepad::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    file_path_ = file_name;
    if(!file.open(QFile::ReadOnly| QFile::Text)){
        QMessageBox::warning(this,"Error","Somthing went wrong!");
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

//save method
void Notepad::on_actionSave_triggered()
{
    QFile file(file_path_);
    if(!file.open(QFile::WriteOnly| QFile::Text)){
        QMessageBox::warning(this,"Error","Somthing went wrong!");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

//save as method
void Notepad::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Open the file");
    QFile file(file_name);
    file_path_=file_name;
    if(!file.open(QFile::WriteOnly| QFile::Text)){
        QMessageBox::warning(this,"Error","Somthing went wrong!");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

//window close method
void Notepad::on_actionExit_triggered()
{
    this->close();
}

//selected text copy method
void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

//selected text cut method
void Notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

//paste text method
void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

//clear text edit method
void Notepad::on_actionDelete_triggered()
{
    ui->textEdit->clear();
}

//undo changes method
void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

//redo changes method
void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

//font properties method
void Notepad::on_actionFont_triggered()
{
    bool ok;
          QFont font = QFontDialog::getFont(
                             &ok,
                             QFont( "Arial", 9,50 ),
                             this,
                             tr("Pick a font") );
             if( ok )
             {
                 ui->textEdit->setFontPointSize(font.pointSize());//set font size

                 ui->textEdit->setFontFamily(font.family());//set font family

                 if (font.style() == 1) {
                      ui->textEdit->setFontItalic(true);//set font style
                 }else {
                     ui->textEdit->setFontItalic(false);
                 }

                 if (font.underline() == true) {
                     ui->textEdit->setFontUnderline(true);//Set text underline
                 }else {
                     ui->textEdit->setFontUnderline(false);
                 }
             }
}

//change font color method
void Notepad::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this );
              if( color.isValid() )
              {
                 ui->textEdit->setTextColor(color.name());
              }
}

//zoom in method
void Notepad::on_actionZoom_In_triggered()
{
    ui->textEdit->zoomIn(4);
}

//zoom out method
void Notepad::on_actionZoom_Out_triggered()
{
    ui->textEdit->zoomOut(3);
}

//about section method
void Notepad::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About"), tr("Notepad v1.0 "
                                               "\nAuthor : Lahiru Dananjaya Sudasinghe\n"
                                               "Date : 01/17/2022\n"
                                               "\nThis is a simple notepad application build for University project using C++ with QT \n"
                                             "\n© 2022 Notepad. Alrights reserved. "));//qMessageBox will popup


}



//text align left method
void Notepad::on_actionAlign_left_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignLeft);
}

//text slign center method
void Notepad::on_actionAlign_Center_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignCenter);
}

//text align right method
void Notepad::on_actionAlign_Right_triggered()
{
    ui->textEdit->setAlignment(Qt::AlignRight);
}

//add date and time method
void Notepad::on_actionAdd_Date_Time_triggered()
{
    QDate cd = QDate::currentDate();//get current system date and assign it into cd
            QTime ct = QTime::currentTime();//get current system time and assign it into ct

            ui->textEdit->setText(cd.toString() +" "+ ct.toString());//set text into date and time
}

