LSQR Windows DLL and LSQR.NET Read-me
=====================================


Software Version
----------------

Version 1.1, July 2008. 


Requirements 
------------

The solution (.sln) and project (.csproj/.vcproj) files provided in this package were created in 
Visual Studio 2005. With some manual work it is possible to compile the software in Visual Studio
2003 as well. The executable in the Bin folder was compiled with VS 2005; .NET Framework 2.0 is
thus required to execute it.


LSQR Windows DLL
----------------

The LSQR DLL binaries are contained in LSqrDll\Bin\x86 and LSqrDll\Bin\x64 (.dll [and .lib for VS 
2005]). The C++ header file is contained in LSqrDll\Src (LSqrDll.h). The VS 2005 solution file is 
contained in LSqrDll\Src (LSqrDll.sln).


LSQR.NET
--------

The LSQR.NET examples are contained in LSqrDllTest\Bin\x86 and LSqrDllTest\Bin\x64 (LSqrDllTest.exe). 
The C# wrapper is contained in LSqrDllTest (LSqrDotNet.cs). To see how LSQR is supposed to be used 
in C#, take a look at LSqrDllTest\Program.cs. The VS 2005 solution file is contained in LSqrDllTest 
(LSqrDllTest.sln).


License
-------

The software is provided under the terms of Common Public License (CPL).


Acknowledgements
----------------

LSQR is originally provided by SOL at Stanford University. The initiators and original authors of 
LSQR are Chris C. Paige and Michael A. Saunders. 
Several people contributed: James Howse, Michael Friedlander, Eric Badel, and John Tomlin.

LSQR Windows DLL and LSQR.NET are based on the C++ version provided by John Tomlin (translated from 
the C version provided by James W. Howse).

Visit http://www.stanford.edu/group/SOL/software/lsqr.html for more info.

See also LSqrDll\Src\lsqr_c.README and LSqrDll\Src\README for the notes on the C/C++ versions of 
LSQR.


Contact
-------

For LSQR issues and comments, contact Michael A. Saunders <saunders@stanford.edu>.
For LSQR DLL and LSQR.NET issues, contact Miha Grcar <miha.grcar@ijs.si>.


(EOF)