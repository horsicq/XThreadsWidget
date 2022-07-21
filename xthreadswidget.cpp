/* Copyright (c) 2021-2022 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "xthreadswidget.h"
#include "ui_xthreadswidget.h"

XThreadsWidget::XThreadsWidget(QWidget *pParent) :
    XShortcutsWidget(pParent),
    ui(new Ui::XThreadsWidget)
{
    ui->setupUi(this);

    g_pXInfoDB=nullptr;
    g_pModel=nullptr;
    g_pOldModel=nullptr;
}

XThreadsWidget::~XThreadsWidget()
{
    delete ui;
}

void XThreadsWidget::setXInfoDB(XInfoDB *pXInfoDB,bool bReload)
{
    g_pXInfoDB=pXInfoDB;

    if(bReload)
    {
        reload();
    }
}

void XThreadsWidget::reload()
{
    if(g_pXInfoDB)
    {
        g_pOldModel=g_pModel;

//        XBinary::MODE modeAddress=XBinary::getModeOS();

        QList<XInfoDB::THREAD_INFO> *pListThreads=g_pXInfoDB->getThreadInfos();

        qint32 nNumberOfRecords=pListThreads->count();

        g_pModel=new QStandardItemModel(nNumberOfRecords,__HEADER_COLUMN_size);

        g_pModel->setHeaderData(HEADER_COLUMN_NUMBER,Qt::Horizontal,tr("Number"));
        g_pModel->setHeaderData(HEADER_COLUMN_ID,Qt::Horizontal,QString("ID"));
        g_pModel->setHeaderData(HEADER_COLUMN_LOCALBASE,Qt::Horizontal,QString("Base"));
        g_pModel->setHeaderData(HEADER_COLUMN_STARTADDRESS,Qt::Horizontal,QString("Start"));
        g_pModel->setHeaderData(HEADER_COLUMN_NAME,Qt::Horizontal,QString("Name"));

        for(qint32 i=0;i<nNumberOfRecords;i++)
        {
            QStandardItem *pItemNumber=new QStandardItem;
            pItemNumber->setText(QString::number(i));
            pItemNumber->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            g_pModel->setItem(i,HEADER_COLUMN_NUMBER,pItemNumber);

            QStandardItem *pItemID=new QStandardItem;
            pItemID->setText(XBinary::valueToHex((quint32)(pListThreads->at(i).nThreadID)));
            pItemID->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            g_pModel->setItem(i,HEADER_COLUMN_ID,pItemID);

            QStandardItem *pItemLocalBase=new QStandardItem;
            pItemLocalBase->setText(XBinary::valueToHexOS((quint32)(pListThreads->at(i).nThreadLocalBase)));
            pItemLocalBase->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            g_pModel->setItem(i,HEADER_COLUMN_LOCALBASE,pItemLocalBase);

            QStandardItem *pItemStartAddress=new QStandardItem;
            pItemStartAddress->setText(XBinary::valueToHexOS((quint32)(pListThreads->at(i).nStartAddress)));
            pItemStartAddress->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
            g_pModel->setItem(i,HEADER_COLUMN_STARTADDRESS,pItemStartAddress);

            QStandardItem *pItemName=new QStandardItem;
            pItemName->setText(""); // TODO !!!
            pItemName->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            g_pModel->setItem(i,HEADER_COLUMN_NAME,pItemName);
        }

        ui->tableViewThreads->setModel(g_pModel);

        deleteOldModel(&g_pOldModel);
    }
}

void XThreadsWidget::registerShortcuts(bool bState)
{
    Q_UNUSED(bState)
}
