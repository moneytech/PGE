/*
 * This file is part of "Phoenix Game Engine".
 *
 * Copyright (C) 2008 Phoenix Game Engine
 * Copyright (C) 2008 InsertWittyName <tias_dp@hotmail.com>
 * Copyright (C) 2008 MK2k <pge@mk2k.net>
 *
 * Phoenix Game Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 
 * Phoenix Game Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 
 * You should have received a copy of the GNU General Public License
 * along with Phoenix Game Engine.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <pge/pge.h>

int main(int argc, char*argv[])
{
	// Init graphics
	pgeGfxInit(PGE_PIXEL_FORMAT_8888);
	
	pgeControlsInit();
	
	pgeUtilsOskInit("Enter name", NULL);
	
	// Allocate 512 bytes for our text
	char *osktext = (char *)malloc(512);
	
	if(!osktext)
		pgeExit();
		
	// OSK result
	int result = -1;

	// Save
	while(pgeRunning())
	{
		pgeControlsUpdate();
		
		// Start drawing
		pgeGfxStartDrawing();

		// Clear screen (black)
		pgeGfxClearScreen(0);
		
		// End drawing
		pgeGfxEndDrawing();
		
		// We always update the dailog after pgeGfxEndDrawing()
		result = pgeUtilsOskUpdate(osktext);
		
		// If the return value > -1, user has ended the dialog.
		if(result > -1)
			break;

		// Swap buffer (wait for vysnc)
		pgeGfxSwapBuffers(PGE_WAIT_VSYNC);
	}
	
	if(result == 1)
		printf("User cancelled input\n");
	else
		printf("User entered: %s\n", osktext);
		
	if(osktext)
		free(osktext);
	
	// Shutdown graphics
	pgeGfxShutdown();
	
	pgeControlsShutdown();
	
	pgeExit();
	
	return 0;
}
