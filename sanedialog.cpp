/* ============================================================
 *
 * Date        : 2008-04-17
 * Description : Sane plugin interface for KDE
 *
 * Copyright (C) 2008 by Kare Sars <kare dot sars at iki dot fi>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ============================================================ */

#include "sanedialog.h"

#include <KLocale>
#include <KDebug>
#include <KPluginLoader>
#include <KMessageBox>
#include <KSharedConfig>

K_PLUGIN_FACTORY(SaneDialogFactory, registerPlugin<SaneDialog>();)
K_EXPORT_PLUGIN(SaneDialogFactory("ksaneplugin"))


///////////////////////////////////////////////////////////////////


SaneDialog::SaneDialog(QWidget *parent, const QVariantList &)
    : KScanDialog(Plain, Close, parent)
{
    ksanew = new KSaneIface::KSaneWidget(this);
    addPage(ksanew, QString());

    connect(ksanew, SIGNAL(imageReady(QByteArray &, int, int, int, int)),
            this, SLOT(imageReady(QByteArray &, int, int, int, int)));

    openDev = QString();
}


bool SaneDialog::setup()
{
    if(!ksanew) {
        // new failed
        return false;
    }
    if (!openDev.isEmpty()) {
        return true;
    }
    // need to select a scanner
    openDev = ksanew->selectDevice(0);
    if (openDev.isEmpty()) {
       // either no scanner was found or then cancel was pressed.
        return false;
    }
    if (ksanew->openDevice(openDev) == false) {
        // could not open the scanner
        KMessageBox::sorry(0, i18n("Opening the selected scanner failed."));
        openDev = QString();
        return false;
    }

    // restore scan dialog size and all options for the selected device if available
    KSharedConfigPtr configPtr = KSharedConfig::openConfig("scannersettings");
    restoreDialogSize(KConfigGroup(configPtr, "ScanDialog"));
    QString groupName = openDev;
    if (configPtr->hasGroup(groupName)) {
        KConfigGroup group(configPtr, groupName);
        QStringList keys = group.keyList();
        for (int i = 0; i < keys.count(); i++)
            ksanew->setOptVal(keys[i], group.readEntry(keys[i]));
    }

   return true;
}

SaneDialog::~SaneDialog()
{
    if (ksanew && !openDev.isEmpty()) {
        // save scan dialog size and all options for the selected device if available
        KSharedConfigPtr configPtr = KSharedConfig::openConfig("scannersettings");
        KConfigGroup group(configPtr, "ScanDialog");
        saveDialogSize(group, KConfigGroup::Persistent);
        group = configPtr->group(openDev);
        QMap<QString, QString> opts;
        ksanew->getOptVals(opts);
        QMap<QString, QString>::const_iterator i = opts.constBegin();
        for (; i != opts.constEnd(); ++i)
            group.writeEntry(i.key(), i.value(), KConfigGroup::Persistent);
    }
}

void SaneDialog::imageReady(QByteArray &data, int w, int h, int bpl, int f)
{
    /* copy the image data into img */
    QImage img = ksanew->toQImage(data, w, h, bpl, (KSaneIface::KSaneWidget::ImageFormat)f);
    emit finalImage(img, nextId());
}


#include "sanedialog.moc"
