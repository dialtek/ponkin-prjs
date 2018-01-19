**********************************************************
******** Welcome to the Tango Binding for LabVIEW ********
**********************************************************

1. About this distribution
--------------------------
The present binary distribution comes with all required runtime libraries.
In other words, you get everything you need to run the Tango binding under windows.

2. Installing
-------------
No special installation process. Just copy the distribution directory somewhere on your disk.

3. Using the binding
--------------------
Make sure that the Tango database env. variable (i.e. TANG0_HOST) is properly defined is the 
context in which LabVIEW is launched. The easiest way to do that is to create a system wide 
TANG0_HOST env. variable pointing to your local Tango database. The syntax is the following:
TANG0_HOST=<dns-name or ip-address of the machine hosting the tango-db>:<tango-db-port>

Open one of the Tango binding example Vi. If the Vi "execute arrow" isn't broken, it means 
that everything is fine and you can start to play with the binding. In case LabVIEW can't 
locate one the binding Vis or the binding dll itself, it will popup a dialog asking you to 
locate the missing component. In such a case, just browse the vi/201x/tango_vi.llb library 
and select the missing Vi (or the tango_binding.dll itself).

4. Tutorials
------------
There's certainly an example covering your needs in the examples directory.
The binding is so simple to use that everything should be straightforward (as far as you're 
confortable with the Tango concepts of Command and Attribute).

5. Feedback & Bug report
------------------------
Send your comments to tango@esrf.fr (i.e. the Tango mailing list)

Have fun with Tango for LabVIEW.
Nicolas Leclercq - Synchrotron SOLEIL


