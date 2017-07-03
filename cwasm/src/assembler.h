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

#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <QFile>
#include <QCoreApplication>
#include <vector>

class CAssembler
{
      Q_DECLARE_TR_FUNCTIONS(CAssembler);
   public:
      bool assemble(QFile &in, QFile &out);
   protected:
      bool handleLine(QString &line, int lineNumber);

      unsigned short _currentPC;

      QByteArray _assembledProgram;
      bool _firstPass;
};

#endif
