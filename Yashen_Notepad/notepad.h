#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QMessageBox>
#include<QDebug>
#include <QCloseEvent>
#include<QFileDialog>
#include <QFontDialog>
#include <QSaveFile>
#include <QPrinter>
#include <QPrintDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT  //base object

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

   void closeEvent(QCloseEvent *event);
   bool getIsBold() const;
   void setIsBold(bool value);

   bool getIsUnderline() const;
   void setIsUnderline(bool value);

private slots:
   void on_actionOpen_triggered();

   void on_textEdit_textChanged();

    void documentModified(bool x);

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionCut_triggered();


    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionExit_triggered();



    void setFontUnderline(bool underline);
    void setFontBold(bool bold);
    void on_actionBold_triggered();

    void on_actionUnderline_triggered();

    void on_actionFont_triggered();

    void on_actionNew_triggered();

    void on_actionPrint_triggered();

    void on_actionAbout_triggered();

private:
    Ui::Notepad *ui;
    QString currentFile;

    bool isBold = false;
    bool isUnderline = false;
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);

};
#endif // NOTEPAD_H
