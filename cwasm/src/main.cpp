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
#include "assembler.h"
#include "instructions.h"
#include "config.h"
#include <QFile>
#include <iostream>


int main(int argc, char * argv[])
{

   if (argc == 2)
   {
      if (strcmp(argv[1], "--list") == 0)
      {
	 CInstruction::listInstructions();
	 return 0;
      }
   }

   if (argc != 3)
   {
      std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << std::endl;
      return 1;
   }
   
   QFile in(argv[1]);

   if (!in.exists())
   {
      std::cerr << argv[1] << ": File does not exists" << std::endl;
      return 1;
   }

   if (!in.open(QIODevice::ReadOnly))
   {
      std::cerr << argv[1] << ": Cannot open file: " << (const char*) in.errorString().toAscii() << std::endl;
      return 1;
   }

   QFile out(argv[2]);
   
   if (!out.open(QIODevice::WriteOnly))
   {
      std::cerr << argv[2] << ": Cannot open file for writing: " << (const char*) out.errorString().toAscii() << std::endl;
      return 1;
   }

   CAssembler assembler;

   if (assembler.assemble(in, out))
      return 0;
   else
      return 1;
}
