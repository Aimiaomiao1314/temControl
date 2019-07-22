#include "mythread.h"
#include "AL808.h"
#include <QThread>

Mythread::Mythread()
{
   QThread *thread= new QThread();
   AL808 *al808= new AL808();

   al808->moveToThread(thread);
   thread->start();

   connect(thread , SIGNAL(started())) , al808 , SLOT(InsertLists());
//   connect(thread , SIGNAL(finished()) , al808 , SLOT());
}
