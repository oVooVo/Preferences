#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QDialog>

class Preferences;
class Preference;

namespace Ui {
class PreferenceDialog;
}

class PreferenceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenceDialog(Preferences *preferences, QWidget *parent = 0);
    ~PreferenceDialog();

public slots:
    void reject();
    void accept();

private:
    Ui::PreferenceDialog *ui;
    Preferences* m_preferences;

    static QWidget* createPreferenceWidget(Preference* preference, QWidget *parent);
    static QWidget* createPreferenceEditor(Preference* preference, QWidget *parent);
    static QWidget* createCategoryPage(QList<Preference*> preferences, QWidget* parent);
};

#endif // PREFERENCEDIALOG_H
