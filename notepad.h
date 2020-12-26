#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QMessageBox>
#include<QDebug>            //for testing outputs
#include <QCloseEvent>
#include<QFileDialog>
#include <QFontDialog>
#include <QSaveFile>
#include <QPrinter>         //to setup printer function
#include <QPrintDialog>
#include<QFile>
QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT  //base object

public:
    Notepad(QWidget *parent = nullptr); //widget has no parents
    ~Notepad();                         //destructor

   void closeEvent(QCloseEvent *event); //close event to shutdown application

   bool getIsBold() const;
   void setIsBold(bool value);

   bool getIsUnderline() const;                     //Getters and Setters for Bold,Underline,Italic Functions
   void setIsUnderline(bool value);

   bool getIsItalic() const;
   void setIsItalic(bool value);

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_as_triggered();  //File list actions
    void on_actionNew_triggered();
    void on_actionExit_triggered();
    void on_actionPrint_triggered();


    void on_textEdit_textChanged();
    void documentModified(bool x);       //custom made functions





    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();     //Edit list

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();



    void setFontUnderline(bool underline);
    void setFontBold(bool bold);

    void on_actionBold_triggered();

    void on_actionUnderline_triggered();     //Format list

    void on_actionFont_triggered();

    void on_actionItalic_triggered();
    void setFontItalic(bool italic);


    void on_actionAbout_triggered();  //about


private:
    Ui::Notepad *ui;
    QString currentFile;

    bool isBold = false;
    bool isUnderline = false;
    bool isItalic=false;
    bool maybeSave();                     //Function asks to save your unsaved work on exit event if notepad was modified
    bool saveFile(const QString &fileName); //Saves the text file or reminds if ant unsaved chages left
    void setCurrentFile(const QString &fileName);

};
#endif // NOTEPAD_H
