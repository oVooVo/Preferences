#ifndef INTERFACEOPTIONS_H
#define INTERFACEOPTIONS_H

#include <QString>
#include "preferences_global.h"

class PREFERENCESSHARED_EXPORT InterfaceOptions
{
public:
    enum Interface { Hidden, SpinBox, LineEdit, TextEdit, FileDialog, ComboBox, CheckBox, CheckButton };

    InterfaceOptions();
    InterfaceOptions(Interface interface, const QString& category, const QString& caption);

    QString caption() const { return m_caption; }
    QString category() const { return m_category; }
    Interface interface() const { return m_interface; }

private:
    Interface m_interface;
    QString m_category;
    QString m_caption;
};

#endif // INTERFACEOPTIONS_H
