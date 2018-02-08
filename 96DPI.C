/****************************************************************************

    PROGRAM: 96dpi.c

    VERSION: 1.00
    DATE: 8. Mar. 2002
    LAST UPDATE: 8. Mar. 2002

    PURPOSE: To patch IBM's GRADD-Driver for WinOS/2
	          IFGDI2VM.DRV for Fullscreen and
				 ISGDI2VM.DRV for Seamless 
             The IBM original Drivers switch to 120 dpi for resolutiuons higher than 800 lines.
             This program patches the currently acitve display-driver to 96dpi for all resolutions.

    FUNCTIONS:

        WinMain() 

    COMMENTS:

****************************************************************************/


#include <windows.h>
#include <dir.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>


#define VERSION "1.0.0"
#define PROGRAM "96DPI.EXE"
#define COMMENT "Patches Gradd-based winos/2 drivers"

/* Prototypes */

int		PASCAL WinMain( HANDLE, HANDLE, LPSTR, int);


#pragma argsused
int PASCAL WinMain( HANDLE hInst, HANDLE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{

   HANDLE   hDisplayDriver;
   FILE *fScreen, *fBak;
   int nLength, x, nFound;
   char achDisplayDriverName[MAXPATH];
   BYTE abSearch[4]  = {0x3D, 0x20, 0x03, 0x76 };
   long lPos;            

   hDisplayDriver = GetModuleHandle ("DISPLAY");
   if (hDisplayDriver == NULL) {
      return -1;
   } // endif
   nLength = GetModuleFileName (hDisplayDriver, achDisplayDriverName, MAXPATH);
   if (stricmp (&achDisplayDriverName[nLength - 12], "ifgdi2vm.drv") != 0) {
     if (stricmp (&achDisplayDriverName[nLength - 12], "isgdi2vm.drv") != 0) {
       MessageBox (NULL,&achDisplayDriverName[nLength - 12], "Wrong Display Driver", MB_OK | MB_ICONSTOP);
       return -1;
     } // endif
   } // endif

   fScreen = fopen(achDisplayDriverName,"r+b");
   if (fScreen == 0) {
     // Error
     MessageBox (NULL, "Open of Driver failed", "Error", MB_OK);
   } else {
     nFound = 0;
     do {
       x=getc(fScreen);
       if (LOBYTE(x) == abSearch[0]){
         if (LOBYTE(getc(fScreen)) == abSearch[1]){
			  if (LOBYTE(getc(fScreen)) == abSearch[2]){
             if (LOBYTE(getc(fScreen)) == abSearch[3]){
               // that is it
               nFound++;
               lPos = ftell(fScreen)-1;
             }
           }
         }
       } 
     } while (x != EOF) ; // endwhile
     if (nFound == 1) {
       //O.K. ONE ocurrence
       // First make a copy of the old file
       // Not very fast but easy
       fseek (fScreen, 0, SEEK_SET);
       strcpy (&achDisplayDriverName[nLength-3], "BAK");
       //MessageBox (NULL, achDisplayDriverName, "", MB_OK);
       fBak = fopen (achDisplayDriverName, "wb");
       if (fBak == NULL) {
         MessageBox (NULL, "Unable to create backup", "Error", MB_OK);
       } else {
         x=getc(fScreen);
         while (x!= EOF) {
           putc (LOBYTE(x),fBak);
           x=getc(fScreen);
         } // endwhile
         fclose(fBak);

         fseek (fScreen, lPos, SEEK_SET);
         if (putc(0xEB,fScreen) != EOF){
           MessageBox(NULL, "Driver Patched !\nYou have to restart WinOS/2", "Status",MB_OK);
         } // endif
       } // endif
     }
     fclose (fScreen);
   } // endif
   return 0;
}