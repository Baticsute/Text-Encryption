#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void clear_code();
    void set_code(QVector<QString> c);
    void display_code();
    QVector<QString> get_code();

    ~MainWindow();

private slots:


    void on_btn_randomkey_clicked();

    void on_btn_encrypted_clicked();

    void on_bt_viewCodeBlock_clicked();

    void on_bt_decrypted_clicked();

    void on_btn_clean_up_clicked();

    void on_bt_reset_clicked();

    void on_bt_browse_clicked();

    void on_btn_Load_clicked();

    void on_bt_writetofile_clicked();

    void on_bt_loadfile_clicked();

private:
    Ui::MainWindow *ui;
    QVector<QString> code;

};

#endif // MAINWINDOW_H
