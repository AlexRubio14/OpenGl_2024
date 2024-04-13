#include "ShaderProgramManager.h"

void ShaderProgramManager::DeletePrograms()
{
	for (int i = 0; i < compiledPrograms.size(); i++) {
		
		glDeleteProgram(compiledPrograms[i]);
	}
}
