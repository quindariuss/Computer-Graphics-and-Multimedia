//
// Created by Ben on 12/11/2020.
//

#pragma once

#include <glad/gl.h>


namespace cs4722 {

    GLuint load_shaders(const char* vertex_shader_path, const char* fragment_shader_path,
                        bool exit_on_error = true);


//    GLuint load_shaders(ShaderInfo *, bool exit_on_error = true);
}
