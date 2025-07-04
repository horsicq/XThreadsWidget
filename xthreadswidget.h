/* Copyright (c) 2021-2025 hors<horsicq@gmail.com>
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
#ifndef XTHREADSWIDGET_H
#define XTHREADSWIDGET_H

#include <QFuture>
#include <QStandardItemModel>
#include <QWidget>
#include <QtConcurrent>

#include "xinfodb.h"
#include "xshortcutswidget.h"

namespace Ui {
class XThreadsWidget;
}

class XThreadsWidget : public XShortcutsWidget {
    Q_OBJECT

    enum HEADER_COLUMN {
        HEADER_COLUMN_NUMBER = 0,
        HEADER_COLUMN_ID,
        HEADER_COLUMN_LOCALBASE,
        HEADER_COLUMN_STARTADDRESS,
        HEADER_COLUMN_NAME,
        HEADER_COLUMN_STATUS,
        __HEADER_COLUMN_size
    };

    //    enum USERROLE
    //    {
    //        USERROLE_ADDRESS=0
    //    };

public:
    explicit XThreadsWidget(QWidget *pParent = nullptr);
    ~XThreadsWidget();

    virtual void adjustView()
    {
    }

    void setXInfoDB(XInfoDB *pXInfoDB, bool bReload = true);
    void reload();

protected:
    virtual void registerShortcuts(bool bState);

private:
    Ui::XThreadsWidget *ui;
    XInfoDB *g_pXInfoDB;
    QStandardItemModel *g_pModel;
    QStandardItemModel *g_pOldModel;
};

#endif  // XTHREADSWIDGET_H
