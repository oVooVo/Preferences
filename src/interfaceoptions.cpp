#include "interfaceoptions.h"

InterfaceOptions::InterfaceOptions() :
    m_interface(Hidden)
{

}

InterfaceOptions::InterfaceOptions(Interface interface, const QString &category, const QString &caption) :
    m_interface(interface),
    m_category(category),
    m_caption(caption)
{

}
