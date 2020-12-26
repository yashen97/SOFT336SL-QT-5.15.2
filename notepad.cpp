#include "notepad.h"
#include "ui_notepad.h"


Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    const int size=13;
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);    //set central wiget
    ui->textEdit->setFontPointSize(size);

}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::closeEvent(QCloseEvent *e)
{
    if (maybeSave()) {

        e->accept();
    } else {
        e->ignore();
    }
}

bool Notepad::maybeSave(){

    if (!ui->textEdit->document()->isModified())  //hot edit
        return true;
    const QMessageBox::StandardButton swb
        = QMessageBox::warning(this, tr("Notepad"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (swb) {
    case QMessageBox::Save:
       // return saveFile(currentFile) ;
        Notepad::on_actionSave_as_triggered();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void Notepad::on_actionOpen_triggered()
{
    maybeSave();
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
       QFile file(fileName);
       currentFile = fileName;
       if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
           QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
           return;
       }
       setWindowTitle(fileName);
       QTextStream in(&file);
       QString text = in.readAll();
       ui->textEdit->setText(text);
       file.close();
       setCurrentFile(fileName);
       statusBar()->showMessage(tr("File loaded"), 2000);
}

void Notepad::on_textEdit_textChanged()
{
    if(!ui->textEdit->toPlainText().isEmpty()){
        Notepad::documentModified(true);
    }
    else{
        Notepad::documentModified(false);
    }
}

void Notepad::documentModified(bool x)
{
    QString title = this->windowTitle();
      if(!title.contains('*'))
      this->setWindowTitle(title+tr("[*]"));
      this->setWindowModified(x);
}

void Notepad::on_actionSave_triggered()
{
    if (!currentFile.isEmpty()) {
        saveFile(currentFile);
    } else {

         QMessageBox::StandardButton reply = QMessageBox::warning(this,tr("Notepad Save"),
         tr("The file wasn't saved before,\n do you want to save it?"),
                              QMessageBox::Yes | QMessageBox::Cancel ,QMessageBox::Cancel);
         if(reply==QMessageBox::Yes){

              Notepad::on_actionSave_as_triggered();
             qDebug() << "Yes";
         }
         else{

             qDebug() << "Canceled";
             }


    }
}

bool Notepad::saveFile(const QString &fileName)

{
    QString errorMessage;

    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
    QSaveFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
    QGuiApplication::restoreOverrideCursor();

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr("Application"), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void Notepad::setCurrentFile(const QString &fileName)

{
    currentFile = fileName;
    ui->textEdit->document()->setModified(false);
    setWindowModified(false);
                                                        //not working check the documentation again
    QString shownName = currentFile;
    if (currentFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}



void Notepad::on_actionSave_as_triggered()
{
    QString fileName=QFileDialog::getSaveFileName(this,"Save as");
    QFile file(fileName);
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        setCurrentFile(fileName);
    }
    else
        QMessageBox::warning(this,"Warning","Cannot Save "+file.errorString());

}



void Notepad::on_actionCut_triggered()
{
   ui->textEdit->cut();
}


void Notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
    statusBar()->showMessage(tr("Text copied"),2000);
}

void Notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionExit_triggered()
{
    QApplication::closeAllWindows();
}

void Notepad::setFontUnderline(bool underline)
{
   ui->textEdit->setFontUnderline(underline);

}

void Notepad::setFontItalic(bool italic)
{

    italic ?  ui->textEdit->setFontItalic(QFont::StyleItalic) :
                  ui->textEdit->setFontItalic(QFont::StyleNormal);

}

void Notepad::setFontBold(bool bold)
{
   bold ?  ui->textEdit->setFontWeight(QFont::Bold) :
           ui->textEdit->setFontWeight(QFont::Normal);

}

void Notepad::on_actionBold_triggered()
{
    bool isBold = Notepad::getIsBold();
    if(!isBold){
    Notepad::setFontBold(true);
    Notepad::setIsBold(true);
    }
    else{
      Notepad::setFontBold(false);
      Notepad::setIsBold(false);
    }
}

void Notepad::on_actionUnderline_triggered()
{
   bool isUnderline = Notepad::getIsUnderline();
   if(!isUnderline){
       Notepad::setFontUnderline(true);
       Notepad::setIsUnderline(true);
   }
   else{
       Notepad::setFontUnderline(false);
       Notepad::setIsUnderline(false);
   }
}

bool Notepad::getIsUnderline() const
{
    return isUnderline;
}

void Notepad::setIsUnderline(bool value)
{
    isUnderline = value;
}

bool Notepad::getIsBold() const
{
    return isBold;
}

void Notepad::setIsBold(bool value)
{
    isBold = value;
}

void Notepad::on_actionFont_triggered()
{
    bool ok;
     QFont font = QFontDialog::getFont(&ok,ui->textEdit->font(),this);
     if(ok){
         ui->textEdit->setFont(font);
     }
}

void Notepad::on_actionNew_triggered()
{
    maybeSave();
    currentFile.clear();
    ui->textEdit->setText(QString());
    statusBar()->showMessage(tr("New file"),2000);
}

void Notepad::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog prd(&printer,this);
    if(prd.exec()==QDialog::Rejected){
        QMessageBox::warning(this,"Warning","Cannot Access Printer");
        return;
    }
    ui->textEdit->print(&printer);
}

void Notepad::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About QT Notepad"),
         tr("<b>QT Notepad©</b> Student project<br> "
            "<br>"
            "QT Notepad by <b>Yashen Raveesha Samarasingha</b> of Plymouth University<br> "
            "Student ID <b>10674025</b> Module Code <b>SOFT336SL</b><br> "
            "<br>"
            "github repo: <a href=https://github.com/yashen97/SOFT336SL-QT-5.15.2><br> "
            "github.com/yashen97/SOFT336SL-QT-5.15.2"));
}

void Notepad::on_actionItalic_triggered()
{
    bool isItalic = Notepad::getIsItalic();
    if(!isItalic){
        Notepad::setFontItalic(true);
        Notepad::setIsItalic(true);
    }
    else{
        Notepad::setFontItalic(false);
        Notepad::setIsItalic(false);
    }
}

bool Notepad::getIsItalic() const
{
    return isItalic;
}

void Notepad::setIsItalic(bool value)
{
    isItalic = value;
}
