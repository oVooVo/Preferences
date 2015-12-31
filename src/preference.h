#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QVariant>
#include "interfaceoptions.h"
#include <QFileDialog>

class QSettings;
class Preference : public QObject
{
    Q_OBJECT
public:
    enum Type { Invalid, Unknown, Double, String, Options, Bool };

    // invalid preference
    Preference();

    // user preferences
    Preference(InterfaceOptions interfaceOptions, double defaultValue, double lowerBound, double upperBound, double stepSize, const QString& suffix = "", const QString& specialValueText = "");
    Preference(InterfaceOptions interfaceOptions, double defaultValue, double lowerBound, double upperBound, const QString& suffix = "", const QString& specialValueText = "");
    Preference(InterfaceOptions interfaceOptions, double defaultValue, double stepSize, const QString& suffix = "", const QString& specialValueText = "");
    Preference(InterfaceOptions interfaceOptions, const QString& defaultValue, const QString& placeHolderText = "");
    Preference(InterfaceOptions interfaceOptions, const QString& defaultValue, QFileDialog::AcceptMode acceptMode, QFileDialog::FileMode fileMode,
               QFileDialog::Options options, const QString& placeHolderText = "");
    Preference(InterfaceOptions interfaceOptions, const QStringList& options, int defaultIndex = -1);
    Preference(InterfaceOptions interfaceOptions, bool defaultValue);

    // hidden preference
    Preference(const QVariant& defaultValue);


    Type type() const { return m_type; }
    bool isHidden() const { return interfaceOptions().interface() == InterfaceOptions::Hidden; }
    bool isValid() const { return type() != Invalid; }

    QVariant value() const { return m_value; }
    QVariant defaultValue() const { return m_default; }
    void setValue(const QVariant& value);

    double lowerBound() const { return m_lowerBound; }
    double upperBound() const { return m_upperBound; }
    double stepSize() const { return m_stepSize; }
    QString placeHolderText() const { return m_placeHolderText; }
    QString label() const { return m_label; }
    QStringList options() const { return m_options; }
    InterfaceOptions interfaceOptions() const { return m_interfaceOptions; }
    QString suffix() const { return m_suffix; }
    QString specialValueText() const { return m_specialValueText; }

    QFileDialog::AcceptMode acceptMode() const { return m_acceptMode; }
    QFileDialog::FileMode fileMode() const { return m_fileMode; }
    QFileDialog::Options fileDialogOptions() const { return m_FileDialogOptions; }


public slots:
    void reset();
signals:
    void valueChanged(QVariant);

private:
    Type m_type;
    InterfaceOptions m_interfaceOptions;
    QVariant m_default;
    QVariant m_value;

    QFileDialog::AcceptMode m_acceptMode;
    QFileDialog::FileMode m_fileMode;
    QFileDialog::Options m_FileDialogOptions;

    double m_lowerBound;
    double m_upperBound;
    double m_stepSize;
    QString m_placeHolderText;
    QString m_label;
    QString m_suffix;
    QString m_specialValueText;
    QStringList m_options;

};

#endif // PREFERENCE_H
