#ifndef FILEDIALOGWIDGET_H
#define FILEDIALOGWIDGET_H

#include <QWidget>
#include <QFileDialog>

namespace Ui {
class FileDialogWidget;
}

class FileDialogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileDialogWidget(QFileDialog::AcceptMode acceptMode, QFileDialog::FileMode fileMode, QFileDialog::Options options, QWidget *parent = 0);
    ~FileDialogWidget();

public slots:
    void setPath(const QString& path);
signals:
    void pathChanged(const QString& path);

private slots:
    void spwanFileDialog();

private:
    Ui::FileDialogWidget *ui;
    QFileDialog::AcceptMode m_acceptMode;
    QFileDialog::FileMode m_fileMode;
    QFileDialog::Options m_options;
    QString m_path;
};

#endif // FILEDIALOGWIDGET_H
