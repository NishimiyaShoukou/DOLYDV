/*<FH+>************************************************************************/
/*                                                                            */
/*                                                                            */
/*                                                                            */
/*File name: 	  keyctl.c                                               */
/*Content summary:	按键处理源文件		*/
/*Other instructions:			*/
/*Current version:				*/
/*Author: 				*/
/*Completion date: 		*/
/*Modification record:	*/
/*Modification date       */
/* ------------------------------------------------------------------------------- */
/*    2024-09-26                V1.00        wangwentao             Create          */
/*<FH->************************************************************************/
#include <keyctl.h>
#include <termio.h>
#include <stdio.h>
#include <unistd.h>

/*<FUNC+>************************************************************************/
/* Function name:        scanKeyboard                             */
/* Function Description:  读取键盘值    */
/* Input parameters:                                                            */
/* Output parameters: None                                                      */
/* Return value: None                                                           */
/* Operation process:                                                           */
/* Other notes: None                                                            */
/* Modification record:                                                         */
/*  Modification Date     Version No.     Modified By      Modification Content */
/* ---------------------------------------------------------------------------- */
/*     2023/12/22           V1.00          wangwentao            Create           */
int scanKeyboard(void)
{

    int ch_in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(STDIN_FILENO,&stored_settings); //获得stdin 输入
    new_settings = stored_settings;           //
    new_settings.c_lflag &= (~ICANON);        //
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(STDIN_FILENO,&stored_settings); //获得stdin 输入
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO,TCSANOW,&new_settings); //

    ch_in = getchar();

    tcsetattr(STDIN_FILENO,TCSANOW,&stored_settings);
    return ch_in;
}



