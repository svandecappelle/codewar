/* This file is part of cwasm.                        
 *									 
 * cwasm is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by	 
 * the Free Software Foundation, either version 3 of the License, or	 
 * (at your option) any later version.					 
 * 									 
 * cwasm is distributed in the hope that it will be useful,		 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of	 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	 
 * GNU General Public License for more details.				 
 * 									 
 * You should have received a copy of the GNU General Public License	 
 * along with cwasm.  If not, see <http://www.gnu.org/licenses/>.	 
 */
#include "label.h"
#include <QtDebug>
#include "config.h"


CLabelHandler::CLabelHandler() : _currentAddr(FIRST_ADDRESS)
{
   
}


CLabelHandler &CLabelHandler::get()
{
   static CLabelHandler lh;
   return lh;
}


bool CLabelHandler::absolute(const QString &label, unsigned short &addr) const
{
   qDebug() << QString("CLabelHandler::absolute(): %1").arg(label);
   LabelList::const_iterator it = _labels.find(label);
   if (it == _labels.end())
      return false;
   qDebug() << "found !";
   addr = it->second;
   return true; 
}

bool CLabelHandler::relative(const QString &label, unsigned short PC, short &addr) const
{
   qDebug() << QString("CLabelHandler::relative(): %1 %2").arg(label).arg(PC, 16);
   unsigned short abs_addr;
   if (!absolute(label,abs_addr))
      return false;
   addr = abs_addr - PC;
   return true;
}

bool CLabelHandler::registerLabel(const QString &label)
{
   qDebug() << QString("CLabelHandler::registerLabel(): %1").arg(label);
   LabelList::iterator it = _labels.find(label);
   if (it != _labels.end())
      return false;
   _labels.insert(std::make_pair(label, _currentAddr));
   return true;
}

void CLabelHandler::advanceAddr(int byteCount)
{
   _currentAddr += byteCount;
}
