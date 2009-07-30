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

#ifndef SANEDIALOG_H
#define SANEDIALOG_H

#include <kscan.h>
#include <libksane/ksane.h>


class SaneDialog : public KScanDialog
{
   Q_OBJECT

    public:
        explicit SaneDialog( QWidget *parent = 0, const QVariantList &args = QVariantList() );
        ~SaneDialog();

        virtual bool setup();

    protected slots:
        void imageReady(QByteArray &, int, int, int, int);

    private:
        KSaneIface::KSaneWidget *ksanew;
        QString                 openDev;
};


#endif // SCAN_H
