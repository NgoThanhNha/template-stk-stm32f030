/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   13/08/2016
 ******************************************************************************
**/

#include "cmd_line.h"

#include "xprintf.h"
#include "utils.h"

uint8_t cmd_line_parser(cmd_line_t* cmd_table, uint8_t* command) {
    uint8_t     cmd[MAX_CMD_SIZE];
	uint8_t*    p_command = command;
	uint8_t     cmd_index = 0;

	uint8_t     index_check = 0;

    /* indefine the command line table */
    if (cmd_table == (cmd_line_t*)0) {
        return CMD_TABLE_NOT_FOUND;
    }

    /* get commmand with string input */
	while (*p_command) {
		if (*p_command == ' ' || *p_command == '\r' || *p_command == '\n') {
			cmd[cmd_index] = 0;
			break;
		}
		else {
			cmd[cmd_index++] = *(p_command++);
			if (cmd_index >= MAX_CMD_SIZE) {
				return CMD_TOO_LONG;
			}
		}
	}

	/* find respective command in command table */
	while (cmd_table[index_check].cmd){

		if (strcmp((const char*)cmd_table[index_check].cmd, (const char*)cmd) == 0) {

			/* perform respective function */
			cmd_table[index_check].func_exe(command);

			/* return success */
			return CMD_SUCCESS;
		}

		index_check++;
	}

	return CMD_NOT_FOUND;  /* command not found */
}