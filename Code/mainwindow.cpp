#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "BigIntegerLibrary.hh"
#include "BigIntegerAlgorithms.hh"
#include <QString>
#include <QByteArray>
#include <QMessageBox>
#include <vector>
#include <ctime>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    srand(time(NULL));
    ui->setupUi(this);

}

void MainWindow::clear_code()
{
    code.clear();
}

void MainWindow::set_code(QVector<QString> c)
{
    for(int i = 0 ;i<c.size();i++){
        code.push_back(c[i]);
    }
}

void MainWindow::display_code()
{
    QString show="";
    for(int i = 0 ; i<code.size();i++){
        show = show + code[i];
    }
    QMessageBox::information(this,"Code Block Inside",show);
}




QVector<QString> MainWindow::get_code()
{
    return code;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_randomkey_clicked()
{

    ui->tx_plaintext_en->setText("");
    ui->tx_encrypted->setText("");
    ui->tx_encrypted_code->setText("");
    ui->tx_decypted->setText("");

    clear_code();
    int bit,lenght_num;
    BigUnsigned two,one,zero;
    two=2;
    one=1;
    zero=0;
    BigUnsigned p,q,n,phi,e,d,limit;
    bit = ui->ln_bit->text().toInt();
    limit = pow(two,bit); // 2^bit
    lenght_num = bigUnsignedToString(limit).length(); // lấy độ dài của số
    q = BigInt_Random(lenght_num); // lấy ngẫu nhiên số q - bước khởi tạo giá trị
    p = BigInt_Random(lenght_num); // // lấy ngẫu nhiên số p - bước khởi tạo giá trị
    // kiểm tra 30 lần cho thuật toán Miller Rabin
    while( ( Miller_Rabin(p,30) != 1) || (p>limit) || (p ==zero)){ // lặp cho đến khi nào p là số nguyên tố
        p=BigInt_Random(lenght_num);
    }
    while( ( Miller_Rabin(q,30) != 1)||(q>limit) || (q==zero)){  // lặp cho đến khi nào q là số nguyên tố ,
        q=BigInt_Random(lenght_num);
    }
    string temp;
    temp = bigUnsignedToString(p);
    ui->tx_p->setText(QString(temp.data()));
    temp = bigUnsignedToString(q);
    ui->tx_q->setText(QString(temp.data()));
    n = p*q; // tính N
    temp = bigUnsignedToString(n);
    ui->tx_n->setText(QString(temp.data()));
    ui->tx_N_encr->setText(QString(temp.data()));
    ui->tx_N_decr->setText(QString(temp.data()));
    phi = (p-1)*(q-1); // tính phi n
    temp = bigUnsignedToString(phi);
    ui->tx_phin->setText(QString(temp.data()));

    e=BigInt_Random(lenght_num); // tìm e sao cho gcd(e,phin) = 1
    while((gcd(e,phi)!=one || (e == zero))){
        e=BigInt_Random(lenght_num);
    }
    d = Mod_Inverse(e,phi);
    temp = bigUnsignedToString(e);
    ui->tx_E->setText(QString(temp.data()));
    ui->tx_E_encr->setText(QString(temp.data()));
    temp = bigUnsignedToString(d);
    ui->tx_D->setText(QString(temp.data()));
    ui->tx_D_decr->setText(QString(temp.data()));
}

void MainWindow::on_btn_encrypted_clicked()
{
   if(ui->tx_plaintext_en->toPlainText().isEmpty() ||ui->tx_E_encr->toPlainText().isEmpty() || ui->tx_N_encr->toPlainText().isEmpty()){
       QMessageBox::information(this,"False Step","PlainText Is Null ! Please Type it ..");
   }else
   {
       BigUnsigned e,n,c,m;
       QByteArray ba;
       e = stringToBigUnsigned(ui->tx_E_encr->toPlainText().toStdString()); // giá trị e
       n = stringToBigUnsigned(ui->tx_N_encr->toPlainText().toStdString()); // giá trị N
       QString str,cal;
       clear_code(); // đảm bảo code block rỗng trước khi mã hóa .
       QVector<QString> vts;
       str = ui->tx_plaintext_en->toPlainText(); // input

       for(int i =0;i<str.length();i++){
            cal.clear(); // đảm bảo calculator rỗng
            cal.push_back(str[i]); // kí tự tiếp theo đi vào để tính toán
            ba = QByteArray(cal.toUtf8().toHex()); // lấy địa chỉ Hex của kí tự
            m = HextoDec(ba.toStdString()); // chuyển Hex sang Dec
            c = a_powx_modn(m,e,n); // Mã Hóa
            vts.push_back(DectoHex(c).data()); // code_block save
       }
       QString show="";
       set_code(vts); // gán vts vào code_block
       for(int i = 0 ; i<code.size();i++){ // Hiển thị đoạn dữ liệu đã bị mã hóa
           show = show + code[i];
       }
       ui->tx_encrypted->setText(show);
   }
}

void MainWindow::on_bt_viewCodeBlock_clicked()
{
    display_code();
}

void MainWindow::on_bt_decrypted_clicked()
{
    if(code.isEmpty() || ui->tx_N_decr->toPlainText().isEmpty() || ui->tx_D_decr->toPlainText().isEmpty()){
        QMessageBox::information(this,"False Step","PlainText Is Null ! Please Type it ..");
    }else{
        QString temp;
        for(int i = 0 ; i<code.size();i++){
            temp.push_back(code[i]);
        }
        ui->tx_encrypted_code->setText(temp);
        BigUnsigned d,n,c,m;
        QByteArray ba;
        d = stringToBigUnsigned(ui->tx_D_decr->toPlainText().toStdString());
        n = stringToBigUnsigned(ui->tx_N_decr->toPlainText().toStdString());
        QVector<QString> vts;
        QString show;
        vts = get_code(); // input
        for(int i = 0 ;i<vts.size();i++){

           c = HextoDec(vts[i].toStdString()); // Code_block [i] => Dec
           m = a_powx_modn(c,d,n); // giải mã
           ba = QByteArray(DectoHex(m).data()); // trả ngược về Hex để lấy địa chỉ Hex
           ba = QByteArray::fromHex(ba); // lấy địa chỉ đưa về kí tự UTF-8 .
           show.push_back(ba.data()); // ba.data = *char
        }
        ui->tx_decypted->setText(show); // hiển thị
    }

}

void MainWindow::on_btn_clean_up_clicked()
{
    ui->tx_plaintext_en->setText("");
    ui->tx_encrypted->setText("");
    ui->run_encrypted->setValue(0);
}

void MainWindow::on_bt_reset_clicked()
{
    ui->tx_plaintext_en->setText("");
    ui->tx_encrypted->setText("");
    ui->tx_D->setText("");
    ui->tx_E->setText("");
    ui->tx_phin->setText("");
    ui->tx_n->setText("");
    ui->tx_phin->setText("");
    ui->tx_q->setText("");
    ui->tx_p->setText("");
    ui->tx_filename->setText("");
    ui->tx_E_encr->setText("");
    ui->tx_D_decr->setText("");
    ui->tx_N_encr->setText("");
    ui->tx_N_decr->setText("");
    ui->tx_decypted->setText("");
    ui->tx_encrypted_code->setText("");
    ui->run_encrypted->setValue(0);
    ui->run_decrypted->setValue(0);
    ui->run_randomkey->setValue(0);
    clear_code();
}



void MainWindow::on_bt_browse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open File","E:/Data_RSA","*.txt;;*.doc");
    if(filename.isEmpty()){
       // QMessageBox::information(this,"Loi !","File khong ton tai !");
        return;
    }
    ui->tx_filename->setText(filename);


}

void MainWindow::on_btn_Load_clicked()
{
    QFile file(ui->tx_filename->toPlainText());
       if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
           QMessageBox::information(this,"Error!","File is found nothing!");
           return;
       }
       QTextStream in(&file);
       in.setCodec("UTF-8");
       QString s;
       s = in.readAll();
       ui->tx_plaintext_en->setText(s);
       file.close();
}

void MainWindow::on_bt_writetofile_clicked()
{   if(ui->tx_plaintext_en->toPlainText().isEmpty() ||ui->tx_E_encr->toPlainText().isEmpty() || ui->tx_N_encr->toPlainText().isEmpty()){
        QMessageBox::information(this,"Error","Cannot Save! Something is Null");
    }
    else{

        QFile data("E:/Data_RSA");
        QString filenamesave = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath(),"RSA Text (*.rsa.txt)");
        data.setFileName(filenamesave); // Tên File save
        if (!data.open(QIODevice::WriteOnly | QIODevice::Text)) // chỉ ghi dữ liệu từ thiết bị
               return;
        QVector<QString> vts;
        vts=get_code(); // lấy từng phần tử của code_block hiện tại
        QTextStream ts(&data); // Dữ liệu ghi vào biến data
        ts.setCodec("UTF-8"); // chưa dùng đến
        ts << ui->tx_N_encr->toPlainText() <<endl; // Ghi N vào dòng đầu tiên
        ts << ui->tx_D->toPlainText()<<endl; // Ghi D vào dòng tiếp theo
        for(int i =0;i<vts.size();i++){ // Các pt của Code_block lần lược ghi lên các dòng tiếp theo
            ts << vts[i] <<endl;
        }
        QMessageBox::information(this,"Information","Saved RSA File is successful.");
    }
}

void MainWindow::on_bt_loadfile_clicked()
{
        QString filename = QFileDialog::getOpenFileName(this,"Open File","E:/Data_RSA","*.rsa.txt");
        QFile data(filename);
        if (!data.open(QIODevice::ReadOnly | QIODevice::Text))
               return;
        clear_code(); // làm rỗng code_block cũ
        QVector<QString> vts;
        QTextStream ts(&data); // đọc file từ data
        QString line,t=""; // dòng lưu tạm
        line = ts.readLine(); // đọc một 2 line đầu tiên
        ui->tx_N_decr->setText(line);
        line = ts.readLine();
        ui->tx_D_decr->setText(line);
        do{  // đọc tiếp những line kế code_block
            line = ts.readLine();
            vts.push_back(line);
            t=t+line;
        }while(!line.isNull()); // cho đến hết
        ui->tx_encrypted_code->setText(t); // hiển thị
        set_code(vts); // code_block mới
        data.close(); // đóng file
}
